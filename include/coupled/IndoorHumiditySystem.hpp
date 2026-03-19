#ifndef __INDOOR_HUMIDITY_SYSTEM_HPP__
#define __INDOOR_HUMIDITY_SYSTEM_HPP__

#include <core/modeling/coupled.hpp>
#include <string>

#include "../atomics/IndoorAir.hpp"
#include "../atomics/LeakageEstimator.hpp"
#include "HumidityPlant.hpp"

namespace humidity {

class IndoorHumiditySystem : public cadmium::Coupled {
public:
    cadmium::Port<double> out_rh;

    explicit IndoorHumiditySystem(const std::string& id) : cadmium::Coupled(id) {
        out_rh = addOutPort<double>("out_rh");

        auto indoor_air = addComponent<IndoorAir>("indoor_air");
        auto leakage = addComponent<LeakageEstimator>("leakage");
        auto plant = addComponent<HumidityPlant>("HumidityPlant");

        addCoupling(indoor_air->out_rh, leakage->in_rh);
        addCoupling(indoor_air->out_rh, plant->in_rh);
        addCoupling(leakage->out_leak, indoor_air->in_leak);
        addCoupling(plant->out_inj, indoor_air->in_inj);
        addCoupling(indoor_air->out_rh, out_rh);
    }
};

} // namespace humidity

#endif