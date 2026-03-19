#ifndef __LEAKAGE_ESTIMATOR_HPP__
#define __LEAKAGE_ESTIMATOR_HPP__

#include <core/modeling/atomic.hpp>
#include <iostream>
#include <string>

namespace humidity {

struct LeakageEstimatorState {
    double sigma;
    double last_rh;
    double leak;

    LeakageEstimatorState() : sigma(1.0), last_rh(50.0), leak(0.0) {}
};

inline std::ostream& operator<<(std::ostream& os, const LeakageEstimatorState& state) {
    os << "last_rh=" << state.last_rh << ";leak=" << state.leak;
    return os;
}

class LeakageEstimator : public cadmium::Atomic<LeakageEstimatorState> {
public:
    cadmium::Port<double> in_rh;
    cadmium::Port<double> out_leak;

    double k_leak = 0.01;
    double rh_ref = 50.0;

    explicit LeakageEstimator(const std::string& id)
        : cadmium::Atomic<LeakageEstimatorState>(id, LeakageEstimatorState()) {
        in_rh = addInPort<double>("in_rh");
        out_leak = addOutPort<double>("out_leak");
    }

    void internalTransition(LeakageEstimatorState& state) const override {
        state.sigma = 1.0;
    }

    void externalTransition(LeakageEstimatorState& state, double e) const override {
        (void)e;
        if (!in_rh->empty()) {
            for (const auto x : in_rh->getBag()) {
                state.last_rh = x;
                state.leak = k_leak * (state.last_rh - rh_ref);
            }
        }
    }

    void output(const LeakageEstimatorState& state) const override {
        out_leak->addMessage(state.leak);
    }

    [[nodiscard]] double timeAdvance(const LeakageEstimatorState& state) const override {
        return state.sigma;
    }
};

} // namespace humidity

#endif