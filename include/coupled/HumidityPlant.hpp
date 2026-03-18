#pragma once

#include <memory>

#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>

#include "../atomics/Humistat.hpp"
#include "../atomics/Humidifier.hpp"

namespace humidity {

struct HumidityPlant_defs {
    struct in_rh : public cadmium::in_port<double> {};
    struct out_inj : public cadmium::out_port<double> {};
};

template<typename TIME>
std::shared_ptr<cadmium::dynamic::modeling::coupled<TIME>> make_HumidityPlant() {
    auto humistat =
        cadmium::dynamic::translate::make_dynamic_atomic_model<Humistat, TIME>("humistat");

    auto humidifier =
        cadmium::dynamic::translate::make_dynamic_atomic_model<Humidifier, TIME>("humidifier");

    cadmium::dynamic::modeling::Ports iports = {typeid(HumidityPlant_defs::in_rh)};
    cadmium::dynamic::modeling::Ports oports = {typeid(HumidityPlant_defs::out_inj)};
    cadmium::dynamic::modeling::Models submodels = {humistat, humidifier};

    cadmium::dynamic::modeling::EICs eics = {
        cadmium::dynamic::translate::make_EIC<
            HumidityPlant_defs::in_rh,
            Humistat_defs::in_rh
        >("humistat")
    };

    cadmium::dynamic::modeling::EOCs eocs = {
        cadmium::dynamic::translate::make_EOC<
            Humidifier_defs::out_inj,
            HumidityPlant_defs::out_inj
        >("humidifier")
    };

    cadmium::dynamic::modeling::ICs ics = {
        cadmium::dynamic::translate::make_IC<
            Humistat_defs::out_cmd,
            Humidifier_defs::in_cmd
        >("humistat", "humidifier")
    };

    return std::make_shared<cadmium::dynamic::modeling::coupled<TIME>>(
        "HumidityPlant", submodels, iports, oports, eics, eocs, ics
    );
}

} // namespace humidity