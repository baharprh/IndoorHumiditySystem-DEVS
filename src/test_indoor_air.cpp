#include <core/logger/csv.hpp>
#include <core/simulation/root_coordinator.hpp>

#include <iostream>
#include <memory>
#include <string>

#include "../include/testing/ExperimentModels.hpp"

int main(int argc, char* argv[]) {
    std::string injection_path = (argc > 1) ? std::string(argv[1]) : "input_data/indoor_air_injection.txt";
    std::string leakage_path = (argc > 2) ? std::string(argv[2]) : "input_data/indoor_air_leakage.txt";
    double sim_time = (argc > 3) ? std::stod(argv[3]) : 8.0;
    std::string log_path = (argc > 4) ? std::string(argv[4]) : "logs/atomic_indoor_air.csv";

    auto model = std::make_shared<humidity::testing::IndoorAirExperiment>(
        "IndoorAirExperiment", injection_path.c_str(), leakage_path.c_str()
    );
    cadmium::RootCoordinator root_coordinator(model);

    auto logger = std::make_shared<cadmium::CSVLogger>(log_path, ",");
    root_coordinator.setLogger(logger);

    root_coordinator.start();
    root_coordinator.simulate(sim_time);
    root_coordinator.stop();

    std::cout << "IndoorAir experiment finished." << std::endl;
    std::cout << "Wrote log: " << log_path << std::endl;
    return 0;
}
