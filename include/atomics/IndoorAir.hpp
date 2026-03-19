#ifndef __INDOOR_AIR_HPP__
#define __INDOOR_AIR_HPP__

#include <core/modeling/atomic.hpp>
#include <iostream>
#include <string>

namespace humidity {

struct IndoorAirState {
    double sigma;
    double rh;
    double inj_last;
    double leak_last;

    IndoorAirState() : sigma(1.0), rh(50.0), inj_last(0.0), leak_last(0.0) {}
};

inline std::ostream& operator<<(std::ostream& os, const IndoorAirState& state) {
    os << "rh=" << state.rh << ";inj=" << state.inj_last << ";leak=" << state.leak_last;
    return os;
}

class IndoorAir : public cadmium::Atomic<IndoorAirState> {
public:
    cadmium::Port<double> in_inj;
    cadmium::Port<double> in_leak;
    cadmium::Port<double> out_rh;

    explicit IndoorAir(const std::string& id)
        : cadmium::Atomic<IndoorAirState>(id, IndoorAirState()) {
        in_inj = addInPort<double>("in_inj");
        in_leak = addInPort<double>("in_leak");
        out_rh = addOutPort<double>("out_rh");
    }

    void internalTransition(IndoorAirState& state) const override {
        state.rh += 0.5 * state.inj_last - 0.5 * state.leak_last;

        if (state.rh < 0.0) state.rh = 0.0;
        if (state.rh > 100.0) state.rh = 100.0;

        state.sigma = 1.0;
    }

    void externalTransition(IndoorAirState& state, double e) const override {
        (void)e;

        if (!in_inj->empty()) {
            for (const auto x : in_inj->getBag()) {
                state.inj_last = x;
            }
        }

        if (!in_leak->empty()) {
            for (const auto x : in_leak->getBag()) {
                state.leak_last = x;
            }
        }
    }

    void output(const IndoorAirState& state) const override {
        out_rh->addMessage(state.rh);
    }

    [[nodiscard]] double timeAdvance(const IndoorAirState& state) const override {
        return state.sigma;
    }
};

} // namespace humidity

#endif