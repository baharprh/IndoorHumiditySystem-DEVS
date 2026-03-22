#ifndef __EXPERIMENT_MODELS_HPP__
#define __EXPERIMENT_MODELS_HPP__

#include <core/modeling/coupled.hpp>
#include <lib/iestream.hpp>
#include <string>

#include "../atomics/Humidifier.hpp"
#include "../atomics/Humistat.hpp"
#include "../atomics/IndoorAir.hpp"
#include "../atomics/LeakageEstimator.hpp"
#include "../coupled/HumidityPlant.hpp"

namespace humidity::testing {

class HumistatExperiment : public cadmium::Coupled {
public:
    cadmium::Port<double> out_cmd;

    HumistatExperiment(const std::string& id, const char* rh_input_file)
        : cadmium::Coupled(id) {
        out_cmd = addOutPort<double>("out_cmd");

        auto rh_input = addComponent<cadmium::lib::IEStream<double>>("rh_input", rh_input_file);
        auto humistat = addComponent<Humistat>("humistat");

        addCoupling(rh_input->out, humistat->in_rh);
        addCoupling(humistat->out_cmd, out_cmd);
    }
};

class HumidifierExperiment : public cadmium::Coupled {
public:
    cadmium::Port<double> out_inj;

    HumidifierExperiment(const std::string& id, const char* cmd_input_file)
        : cadmium::Coupled(id) {
        out_inj = addOutPort<double>("out_inj");

        auto cmd_input = addComponent<cadmium::lib::IEStream<double>>("cmd_input", cmd_input_file);
        auto humidifier = addComponent<Humidifier>("humidifier");

        addCoupling(cmd_input->out, humidifier->in_cmd);
        addCoupling(humidifier->out_inj, out_inj);
    }
};

class LeakageExperiment : public cadmium::Coupled {
public:
    cadmium::Port<double> out_leak;

    LeakageExperiment(const std::string& id, const char* rh_input_file)
        : cadmium::Coupled(id) {
        out_leak = addOutPort<double>("out_leak");

        auto rh_input = addComponent<cadmium::lib::IEStream<double>>("rh_input", rh_input_file);
        auto leakage = addComponent<LeakageEstimator>("leakage");

        addCoupling(rh_input->out, leakage->in_rh);
        addCoupling(leakage->out_leak, out_leak);
    }
};

class IndoorAirExperiment : public cadmium::Coupled {
public:
    cadmium::Port<double> out_rh;

    IndoorAirExperiment(const std::string& id, const char* injection_input_file, const char* leakage_input_file)
        : cadmium::Coupled(id) {
        out_rh = addOutPort<double>("out_rh");

        auto injection_input = addComponent<cadmium::lib::IEStream<double>>("injection_input", injection_input_file);
        auto leakage_input = addComponent<cadmium::lib::IEStream<double>>("leakage_input", leakage_input_file);
        auto indoor_air = addComponent<IndoorAir>("indoor_air");

        addCoupling(injection_input->out, indoor_air->in_inj);
        addCoupling(leakage_input->out, indoor_air->in_leak);
        addCoupling(indoor_air->out_rh, out_rh);
    }
};

class HumidityPlantExperiment : public cadmium::Coupled {
public:
    cadmium::Port<double> out_inj;

    HumidityPlantExperiment(const std::string& id, const char* rh_input_file)
        : cadmium::Coupled(id) {
        out_inj = addOutPort<double>("out_inj");

        auto rh_input = addComponent<cadmium::lib::IEStream<double>>("rh_input", rh_input_file);
        auto plant = addComponent<HumidityPlant>("HumidityPlant");

        addCoupling(rh_input->out, plant->in_rh);
        addCoupling(plant->out_inj, out_inj);
    }
};

}  // namespace humidity::testing

#endif
