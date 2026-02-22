#pragma once

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <ostream>

namespace humidity {

    struct Humidifier_defs {
        struct in_cmd  : public cadmium::in_port<double> {};
        struct out_inj : public cadmium::out_port<double> {};
    };

    template<typename TIME>
    class Humidifier {
    public:
        using input_ports  = std::tuple<typename Humidifier_defs::in_cmd>;
        using output_ports = std::tuple<typename Humidifier_defs::out_inj>;

        struct state_type {
            double cmd = 0.0;
            double inj = 0.0;
        };
        state_type state;

        double inj_on = 2.0; // injection when ON

        Humidifier() = default;

        void internal_transition() { /* nothing */ }

        void external_transition(TIME, typename cadmium::make_message_bags<input_ports>::type mbs) {
            const auto& in = cadmium::get_messages<typename Humidifier_defs::in_cmd>(mbs);
            if (!in.empty()) {
                state.cmd = in.back();
                state.inj = (state.cmd > 0.5) ? inj_on : 0.0;
            }
        }

        void confluence_transition(TIME e, typename cadmium::make_message_bags<input_ports>::type mbs) {
            internal_transition();
            external_transition(e, std::move(mbs));
        }

        typename cadmium::make_message_bags<output_ports>::type output() const {
            typename cadmium::make_message_bags<output_ports>::type out;
            cadmium::get_messages<typename Humidifier_defs::out_inj>(out).push_back(state.inj);
            return out;
        }

        TIME time_advance() const { return TIME(1.0); }

        friend std::ostream& operator<<(std::ostream& os, const state_type& s) {
            os << "{cmd=" << s.cmd << ", inj=" << s.inj << "}";
            return os;
        }
    };

} // namespace humidity