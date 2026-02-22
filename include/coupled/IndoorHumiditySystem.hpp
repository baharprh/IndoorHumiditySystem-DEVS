#pragma once

#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>

#include "atomics/IndoorAir.hpp"
#include "atomics/Humidifier.hpp"
#include "atomics/Humistat.hpp"
#include "atomics/LeakageEstimator.hpp"

namespace humidity {

template<typename TIME>
std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> make_IndoorHumiditySystem() {
    using namespace cadmium;

    dynamic::modeling::Ports iports = {};
    dynamic::modeling::Ports oports = {};
    dynamic::modeling::EICs eics = {};
    dynamic::modeling::EOCs eocs = {};

    auto indoor      = dynamic::translate::make_dynamic_atomic_model<IndoorAir, TIME>("indoor");
    auto humistat    = dynamic::translate::make_dynamic_atomic_model<Humistat, TIME>("humistat");
    auto humidifier  = dynamic::translate::make_dynamic_atomic_model<Humidifier, TIME>("humidifier");
    auto leakage     = dynamic::translate::make_dynamic_atomic_model<LeakageEstimator, TIME>("leakage");

    dynamic::modeling::Models submodels = {indoor, humistat, humidifier, leakage};

    dynamic::modeling::ICs ics = {
        // indoor RH -> leakage & humistat
        dynamic::translate::make_IC<typename IndoorAir_defs::out_rh, typename LeakageEstimator_defs::in_rh>("indoor", "leakage"),
        dynamic::translate::make_IC<typename IndoorAir_defs::out_rh, typename Humistat_defs::in_rh>("indoor", "humistat"),

        // leak -> indoor
        dynamic::translate::make_IC<typename LeakageEstimator_defs::out_leak, typename IndoorAir_defs::in_leak>("leakage", "indoor"),

        // humistat cmd -> humidifier cmd
        dynamic::translate::make_IC<typename Humistat_defs::out_cmd, typename Humidifier_defs::in_cmd>("humistat", "humidifier"),

        // humidifier injection -> indoor
        dynamic::translate::make_IC<typename Humidifier_defs::out_inj, typename IndoorAir_defs::in_inj>("humidifier", "indoor")
    };

    return std::make_shared<dynamic::modeling::coupled<TIME>>(
        "IndoorHumiditySystem", submodels, iports, oports, eics, eocs, ics
    );
}

} // namespace humidity