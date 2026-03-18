#pragma once

#include <memory>
#include <string>

#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>

#include "../atomics/IndoorAir.hpp"
#include "../atomics/LeakageEstimator.hpp"
#include "HumidityPlant.hpp"

namespace humidity {

struct IndoorHumiditySystem_defs {
    struct out_rh : public cadmium::out_port<double> {};
};

template<typename TIME>
std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> make_IndoorHumiditySystem(const std::string&) {
    auto indoor_air =
        cadmium::dynamic::translate::make_dynamic_atomic_model<IndoorAir, TIME>("indoor_air");

    auto leakage =
        cadmium::dynamic::translate::make_dynamic_atomic_model<LeakageEstimator, TIME>("leakage");

    auto plant = make_HumidityPlant<TIME>();

    cadmium::dynamic::modeling::Ports iports = {};
    cadmium::dynamic::modeling::Ports oports = {typeid(IndoorHumiditySystem_defs::out_rh)};
    cadmium::dynamic::modeling::Models submodels = {indoor_air, leakage, plant};

    cadmium::dynamic::modeling::EICs eics = {};

    cadmium::dynamic::modeling::EOCs eocs = {
        cadmium::dynamic::translate::make_EOC<
            IndoorAir_defs::out_rh,
            IndoorHumiditySystem_defs::out_rh
        >("indoor_air")
    };

    cadmium::dynamic::modeling::ICs ics = {
        cadmium::dynamic::translate::make_IC<
            IndoorAir_defs::out_rh,
            LeakageEstimator_defs::in_rh
        >("indoor_air", "leakage"),

        cadmium::dynamic::translate::make_IC<
            IndoorAir_defs::out_rh,
            HumidityPlant_defs::in_rh
        >("indoor_air", "HumidityPlant"),

        cadmium::dynamic::translate::make_IC<
            LeakageEstimator_defs::out_leak,
            IndoorAir_defs::in_leak
        >("leakage", "indoor_air"),

        cadmium::dynamic::translate::make_IC<
            HumidityPlant_defs::out_inj,
            IndoorAir_defs::in_inj
        >("HumidityPlant", "indoor_air")
    };

    return std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
        "IndoorHumiditySystem", submodels, iports, oports, eics, eocs, ics
    );
}

} // namespace humidity