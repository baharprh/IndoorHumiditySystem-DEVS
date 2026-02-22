#pragma once

#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>

#include "../atomics/Humistat.hpp"
#include "../atomics/Humidifier.hpp"

namespace humidity {

template<typename TIME>
std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> make_HumidityPlant() {
    using namespace cadmium;

    auto humistat   = dynamic::translate::make_dynamic_atomic_model<Humistat, TIME>("humistat");
    auto humidifier = dynamic::translate::make_dynamic_atomic_model<Humidifier, TIME>("humidifier");

    dynamic::modeling::Models submodels = {humistat, humidifier};

    dynamic::modeling::Ports iports = {};
    dynamic::modeling::Ports oports = {};

    dynamic::modeling::EICs eics = {};
    dynamic::modeling::EOCs eocs = {};

    dynamic::modeling::ICs ics = {
        dynamic::translate::make_IC<typename Humistat_defs::out_cmd,
                                    typename Humidifier_defs::in_cmd>("humistat", "humidifier")
    };

    return std::make_shared<dynamic::modeling::coupled<TIME>>(
        "HumidityPlant", submodels, iports, oports, eics, eocs, ics
    );
}

} // namespace humidity