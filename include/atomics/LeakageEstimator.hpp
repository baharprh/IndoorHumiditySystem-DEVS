#pragma once

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>

#include <ostream>

namespace humidity {

struct LeakageEstimator_defs {
    // indoor RH input (%)
    struct in_rh : public cadmium::in_port<double> {};
    // leakage output (arbitrary units)
    struct out_leak : public cadmium::out_port<double> {};
};

template<typename TIME>
class LeakageEstimator {
public:
    using input_ports  = std::tuple<typename LeakageEstimator_defs::in_rh>;
    using output_ports = std::tuple<typename LeakageEstimator_defs::out_leak>;

    struct state_type {
        double last_rh = 50.0;
        double leak    = 0.0;
    };
    state_type state;

    double k_leak = 0.01;
    double rh_ref = 50.0;

    LeakageEstimator() = default;

    void internal_transition() {
        // nothing (updates happen on external input)
    }

    void external_transition(TIME, typename cadmium::make_message_bags<input_ports>::type mbs) {
        const auto& in = cadmium::get_messages<typename LeakageEstimator_defs::in_rh>(mbs);
        if (!in.empty()) {
            state.last_rh = in.back();
            state.leak = k_leak * (state.last_rh - rh_ref);
        }
    }

    void confluence_transition(TIME e, typename cadmium::make_message_bags<input_ports>::type mbs) {
        internal_transition();
        external_transition(e, std::move(mbs));
    }

    typename cadmium::make_message_bags<output_ports>::type output() const {
        typename cadmium::make_message_bags<output_ports>::type out;
        cadmium::get_messages<typename LeakageEstimator_defs::out_leak>(out).push_back(state.leak);
        return out;
    }

    TIME time_advance() const {
        return TIME(1.0);
    }

    friend std::ostream& operator<<(std::ostream& os, const state_type& s) {
        os << "{last_rh=" << s.last_rh << ", leak=" << s.leak << "}";
        return os;
    }
};

} // namespace humidity