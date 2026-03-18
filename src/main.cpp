#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

#include <fstream>
#include <iostream>
#include <string>

#include "../include/coupled/IndoorHumiditySystem.hpp"

using TIME = double;

static std::ofstream out_messages("../logs/simulation_messages.log");

struct oss_sink_messages {
    static std::ostream& sink() {
        return out_messages;
    }
};

using state_logger = cadmium::logger::logger<
    cadmium::logger::logger_state,
    cadmium::dynamic::logger::formatter<TIME>,
    oss_sink_messages
>;

using messages_logger = cadmium::logger::logger<
    cadmium::logger::logger_messages,
    cadmium::dynamic::logger::formatter<TIME>,
    oss_sink_messages
>;

using global_time_logger = cadmium::logger::logger<
    cadmium::logger::logger_global_time,
    cadmium::dynamic::logger::formatter<TIME>,
    oss_sink_messages
>;

using logger_top = cadmium::logger::multilogger<
    state_logger,
    messages_logger,
    global_time_logger
>;

int main(int argc, char** argv) {
    std::string input_file = (argc > 1) ? argv[1] : "../input_data/outdoor_dry.txt";
    double sim_time = (argc > 2) ? std::stod(argv[2]) : 200.0;

    auto TOP = humidity::make_IndoorHumiditySystem<TIME>(input_file);

    cadmium::dynamic::engine::runner<TIME, logger_top> r(TOP, TIME(0));
    r.run_until(TIME(sim_time));

    std::cout << "Simulation finished." << std::endl;
    std::cout << "Wrote log: ../logs/simulation_messages.log" << std::endl;

    return 0;
}