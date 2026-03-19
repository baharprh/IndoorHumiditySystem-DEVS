#ifndef __HUMIDITY_PLANT_HPP__
#define __HUMIDITY_PLANT_HPP__

#include <core/modeling/coupled.hpp>
#include <string>

#include "../atomics/Humistat.hpp"
#include "../atomics/Humidifier.hpp"

namespace humidity {

class HumidityPlant : public cadmium::Coupled {
public:
    cadmium::Port<double> in_rh;
    cadmium::Port<double> out_inj;

    explicit HumidityPlant(const std::string& id) : cadmium::Coupled(id) {
        in_rh = addInPort<double>("in_rh");
        out_inj = addOutPort<double>("out_inj");

        auto humistat = addComponent<Humistat>("humistat");
        auto humidifier = addComponent<Humidifier>("humidifier");

        addCoupling(in_rh, humistat->in_rh);
        addCoupling(humistat->out_cmd, humidifier->in_cmd);
        addCoupling(humidifier->out_inj, out_inj);
    }
};

} // namespace humidity

#endif