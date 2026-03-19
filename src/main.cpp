#include <core/simulation/root_coordinator.hpp>
#include <core/logger/csv.hpp>

#include <iostream>
#include <memory>
#include <string>

#include "../include/coupled/IndoorHumiditySystem.hpp"

int main(int argc, char* argv[]) {
    std::string scenarioArg = (argc > 1) ? std::string(argv[1]) : "input_data/outdoor_dry.txt";
    double sim_time = (argc > 2) ? std::stod(argv[2]) : 200.0;

    std::string scenarioName = scenarioArg;
    size_t slash = scenarioName.find_last_of("/\\");
    if (slash != std::string::npos) {
        scenarioName = scenarioName.substr(slash + 1);
    }
    size_t dot = scenarioName.find_last_of('.');
    if (dot != std::string::npos) {
        scenarioName = scenarioName.substr(0, dot);
    }

    auto model = std::make_shared<humidity::IndoorHumiditySystem>("IndoorHumiditySystem");
    auto rootCoordinator = cadmium::RootCoordinator(model);

    auto logger = std::make_shared<cadmium::CSVLogger>(
        "logs/" + scenarioName + ".csv", ","
    );
    rootCoordinator.setLogger(logger);

    rootCoordinator.start();
    rootCoordinator.simulate(sim_time);
    rootCoordinator.stop();

    std::cout << "Simulation finished." << std::endl;
    std::cout << "Wrote log: logs/" << scenarioName << ".csv" << std::endl;

    return 0;
}