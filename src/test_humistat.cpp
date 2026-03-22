#include <core/logger/csv.hpp>
#include <core/simulation/root_coordinator.hpp>

#include <iostream>
#include <memory>
#include <string>

#include "../include/testing/ExperimentModels.hpp"

int main(int argc, char* argv[]) {
    std::string input_path = (argc > 1) ? std::string(argv[1]) : "input_data/humistat_ramp.txt";
    double sim_time = (argc > 2) ? std::stod(argv[2]) : 8.0;
    std::string log_path = (argc > 3) ? std::string(argv[3]) : "logs/atomic_humistat.csv";

    auto model = std::make_shared<humidity::testing::HumistatExperiment>("HumistatExperiment", input_path.c_str());
    cadmium::RootCoordinator root_coordinator(model);

    auto logger = std::make_shared<cadmium::CSVLogger>(log_path, ",");
    root_coordinator.setLogger(logger);

    root_coordinator.start();
    root_coordinator.simulate(sim_time);
    root_coordinator.stop();

    std::cout << "Humistat experiment finished." << std::endl;
    std::cout << "Wrote log: " << log_path << std::endl;
    return 0;
}
