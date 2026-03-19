#ifndef __HUMISTAT_HPP__
#define __HUMISTAT_HPP__

#include <core/modeling/atomic.hpp>
#include <iostream>
#include <string>

namespace humidity {

struct HumistatState {
    double sigma;
    double last_rh;
    double cmd;

    HumistatState() : sigma(1.0), last_rh(50.0), cmd(0.0) {}
};

inline std::ostream& operator<<(std::ostream& os, const HumistatState& state) {
    os << "last_rh=" << state.last_rh << ";cmd=" << state.cmd;
    return os;
}

class Humistat : public cadmium::Atomic<HumistatState> {
public:
    cadmium::Port<double> in_rh;
    cadmium::Port<double> out_cmd;

    double rh_set = 55.0;
    double deadband = 2.0;

    explicit Humistat(const std::string& id)
        : cadmium::Atomic<HumistatState>(id, HumistatState()) {
        in_rh = addInPort<double>("in_rh");
        out_cmd = addOutPort<double>("out_cmd");
    }

    void internalTransition(HumistatState& state) const override {
        state.sigma = 1.0;
    }

    void externalTransition(HumistatState& state, double e) const override {
        (void)e;
        if (!in_rh->empty()) {
            for (const auto x : in_rh->getBag()) {
                state.last_rh = x;

                if (state.last_rh < rh_set - deadband) {
                    state.cmd = 1.0;
                } else if (state.last_rh > rh_set + deadband) {
                    state.cmd = 0.0;
                }
            }
        }
    }

    void output(const HumistatState& state) const override {
        out_cmd->addMessage(state.cmd);
    }

    [[nodiscard]] double timeAdvance(const HumistatState& state) const override {
        return state.sigma;
    }
};

} // namespace humidity

#endif