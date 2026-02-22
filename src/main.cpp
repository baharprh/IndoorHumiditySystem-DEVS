// src/main.cpp

#include <cadmium/modeling/dynamic_model.hpp>
#include <cadmium/engine/pdevs_dynamic_runner.hpp>
#include <cadmium/logger/common_loggers.hpp>

#include <fstream>
#include <iostream>
#include <string>

#include "coupled/IndoorHumiditySystem.hpp"

using TIME = double;

// --- Log to file (Cadmium expects SINK_PROVIDER::sink()) ---
static std::ofstream out_messages("simulation_messages.log");

struct file_sink_provider {
    static std::ostream& sink() {
        return out_messages;
    }
};

// Log ONLY output/messages (avoids requiring operator<< for your state_type)
using logger_messages_t =
    cadmium::logger::logger<
        cadmium::logger::logger_messages,
        cadmium::dynamic::logger::formatter<TIME>,
        file_sink_provider
    >;

int main(int argc, char** argv) {
    // Optional: accept an input file argument (your current coupled may ignore it,
    // but this keeps the interface consistent with how you run it)
    std::string in_file = (argc > 1) ? argv[1] : "input_data/outdoor_dry.txt";
    (void)in_file; // prevent unused warning if your model ignores argv

    // Build the top coupled model (this is what you already have working)
    auto TOP = humidity::make_IndoorHumiditySystem<TIME>();

    // Run simulation with message logger to file
    cadmium::dynamic::engine::runner<TIME, logger_messages_t> r(TOP, TIME(0));
    r.run_until(TIME(200));

    std::cout << "Simulation finished.\n";
    std::cout << "Wrote log: simulation_messages.log\n";
    return 0;
}