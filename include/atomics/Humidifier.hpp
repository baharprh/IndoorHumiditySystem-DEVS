#ifndef __HUMIDIFIER_HPP__
#define __HUMIDIFIER_HPP__

#include <core/modeling/atomic.hpp>
#include <iostream>
#include <string>

namespace humidity {

struct HumidifierState {
    double sigma;
    double cmd;
    double inj;

    HumidifierState() : sigma(1.0), cmd(0.0), inj(0.0) {}
};

inline std::ostream& operator<<(std::ostream& os, const HumidifierState& state) {
    os << "cmd=" << state.cmd << ";inj=" << state.inj;
    return os;
}

class Humidifier : public cadmium::Atomic<HumidifierState> {
public:
    cadmium::Port<double> in_cmd;
    cadmium::Port<double> out_inj;

    double inj_on = 2.0;

    explicit Humidifier(const std::string& id)
        : cadmium::Atomic<HumidifierState>(id, HumidifierState()) {
        in_cmd = addInPort<double>("in_cmd");
        out_inj = addOutPort<double>("out_inj");
    }

    void internalTransition(HumidifierState& state) const override {
        state.sigma = 1.0;
    }

    void externalTransition(HumidifierState& state, double e) const override {
        (void)e;
        if (!in_cmd->empty()) {
            for (const auto x : in_cmd->getBag()) {
                state.cmd = x;
                state.inj = (state.cmd > 0.5) ? inj_on : 0.0;
            }
        }
    }

    void output(const HumidifierState& state) const override {
        out_inj->addMessage(state.inj);
    }

    [[nodiscard]] double timeAdvance(const HumidifierState& state) const override {
        return state.sigma;
    }
};

} // namespace humidity

#endif