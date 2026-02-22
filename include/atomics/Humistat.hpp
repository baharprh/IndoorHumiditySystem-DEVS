#pragma once

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <ostream>

namespace humidity {

    struct Humistat_defs {
        struct in_rh   : public cadmium::in_port<double> {};
        struct out_cmd : public cadmium::out_port<double> {};
    };

    template<typename TIME>
    class Humistat {
    public:
        using input_ports  = std::tuple<typename Humistat_defs::in_rh>;
        using output_ports = std::tuple<typename Humistat_defs::out_cmd>;

        struct state_type {
            double last_rh = 50.0;
            double cmd     = 0.0;
        };
        state_type state;

        double rh_set = 55.0;   // target RH
        double deadband = 2.0;

        Humistat() = default;

        void internal_transition() { /* nothing */ }

        void external_transition(TIME, typename cadmium::make_message_bags<input_ports>::type mbs) {
            const auto& in = cadmium::get_messages<typename Humistat_defs::in_rh>(mbs);
            if (!in.empty()) {
                state.last_rh = in.back();

                if (state.last_rh < rh_set - deadband) state.cmd = 1.0;  // ON
                else if (state.last_rh > rh_set + deadband) state.cmd = 0.0; // OFF
            }
        }

        void confluence_transition(TIME e, typename cadmium::make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(e, std::move(mbs));
        }

        typename cadmium::make_message_bags<output_ports>::type output() const {
            typename cadmium::make_message_bags<output_ports>::type out;
            cadmium::get_messages<typename Humistat_defs::out_cmd>(out).push_back(state.cmd);
            return out;
        }

        TIME time_advance() const { return TIME(1.0); }

        friend std::ostream& operator<<(std::ostream& os, const state_type& s) {
            os << "{last_rh=" << s.last_rh << ", cmd=" << s.cmd << "}";
            return os;
        }
    };

} // namespace humidity