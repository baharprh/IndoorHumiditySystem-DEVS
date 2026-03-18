# Indoor Humidity Regulation System (DEVS Model)

## Description

This project implements a hierarchical DEVS model of an indoor humidity regulation system using the Cadmium simulation framework.

The system consists of the following components:

- **IndoorAir** – Maintains and updates indoor relative humidity (RH)
- **LeakageEstimator** – Models environmental humidity drift
- **Humidistat** – Hysteresis-based ON/OFF controller
- **Humidifier** – Moisture injection actuator

The objective is to regulate indoor humidity around a 45% reference value using discrete-event control with hysteresis (43%–47%).

---

## Requirements

- C++17 compatible compiler
- CMake (>= 3.16)
- Git
- Cadmium DEVS framework (included as submodule)
- Visual Studio with Desktop development with C++ workload (Windows)

---

## Repository Structure

- `src/` – source files  
- `include/` – header files  
- `input_data/` – input files  
- `logs/` – output folder for logs  
- `external/cadmium/` – Cadmium framework submodule  
- `CMakeLists.txt` – build configuration  
- `simulation_messages.log` – generated simulation output log after running the program  

---
## Build and Run Instructions (Windows)

git clone https://github.com/baharprh/IndoorHumiditySystem-DEVS.git
cd IndoorHumiditySystem-DEVS
git submodule update --init --recursive

Build the project:

mkdir build
cd build
cmake ..
cmake --build .

Run the simulation:

.\build\Debug\main.exe

Output:

Simulation finished.
Wrote log: simulation_messages.log

Note: On Windows, the executable is generated inside build/Debug/ after compilation.
