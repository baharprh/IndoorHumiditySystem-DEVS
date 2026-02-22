#pragma once

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <ostream>

namespace humidity {

    struct IndoorAir_defs {
        // moisture injection command (arbitrary units)
        struct in_inj  : public cadmium::in_port<double> {};
        // leakage rate (arbitrary units)
        struct in_leak : public cadmium::in_port<double> {};
        // indoor RH output (%)
        struct out_rh  : public cadmium::out_port<double> {};
    };

    template<typename TIME>
    class IndoorAir {
    public:
        using input_ports  = std::tuple<typename IndoorAir_defs::in_inj, typename IndoorAir_defs::in_leak>;
        using output_ports = std::tuple<typename IndoorAir_defs::out_rh>;

        struct state_type {
            double rh        = 50.0;
            double inj_last  = 0.0;
            double leak_last = 0.0;
        };
        state_type state;

        IndoorAir() = default;

        // REQUIRED
        void internal_transition() {
            // simple discrete update each second:
            // RH increases with injection, decreases with leak
            state.rh += 0.5 * state.inj_last - 0.5 * state.leak_last;

            // clamp to [0,100]
            if (state.rh < 0.0)   state.rh = 0.0;
            if (state.rh > 100.0) state.rh = 100.0;
        }

        void external_transition(TIME, typename cadmium::make_message_bags<input_ports>::type mbs) {
            const auto& inj  = cadmium::get_messages<typename IndoorAir_defs::in_inj>(mbs);
            const auto& leak = cadmium::get_messages<typename IndoorAir_defs::in_leak>(mbs);

            if (!inj.empty())  state.inj_last  = inj.back();
            if (!leak.empty()) state.leak_last = leak.back();
        }

        void confluence_transition(TIME e, typename cadmium::make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(e, std::move(mbs));
        }

        typename cadmium::make_message_bags<output_ports>::type output() const {
            typename cadmium::make_message_bags<output_ports>::type out;
            cadmium::get_messages<typename IndoorAir_defs::out_rh>(out).push_back(state.rh);
            return out;
        }

        TIME time_advance() const { return TIME(1.0); }

        // IMPORTANT: allow Cadmium to print the state
        friend std::ostream& operator<<(std::ostream& os, const state_type& s) {
            os << "{rh=" << s.rh << ", inj=" << s.inj_last << ", leak=" << s.leak_last << "}";
            return os;
        }
    };

} // namespace humidity