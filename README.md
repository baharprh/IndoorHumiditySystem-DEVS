# Indoor Humidity Regulation System (DEVS Model)

## Description

This project implements a hierarchical DEVS model of an indoor humidity regulation system using the Cadmium simulation framework.

The system consists of the following components:

* **IndoorAir** – Maintains and updates indoor relative humidity (RH)
* **LeakageEstimator** – Models environmental humidity drift
* **Humidistat** – Hysteresis-based ON/OFF controller
* **Humidifier** – Moisture injection actuator

The objective is to regulate indoor humidity around a 45% reference value using discrete-event control with hysteresis (43%–47%).

---

## Requirements

* C++17 compatible compiler
* CMake (>= 3.16)
* Git
* Visual Studio with Desktop development with C++ workload (Windows)
* Cadmium DEVS framework (included as submodule)
* Boost C++ Libraries (required by Cadmium, installed via vcpkg)

---

## Repository Structure

* `src/` – source files
* `include/` – header files
* `input_data/` – input files
* `logs/` – output folder for logs
* `external/cadmium/` – Cadmium framework submodule
* `CMakeLists.txt` – build configuration
* `simulation_messages.log` – generated simulation output log after running the program

---

## Build and Run Instructions (Windows)

```bash
git clone https://github.com/baharprh/IndoorHumiditySystem-DEVS.git
cd IndoorHumiditySystem-DEVS
git submodule update --init --recursive

mkdir build
cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/YOUR_USERNAME/Desktop/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Debug

.\Debug\main.exe
```

**Note:** Replace `YOUR_USERNAME` with your Windows username and ensure that `vcpkg` is installed on your system.

---

## Output

```
Simulation finished.
Wrote log: ../logs/simulation_messages.log
```

---

## Notes

* Run the commands from a normal directory (not inside another build folder).
* On Windows, the executable is located in the `Debug/` folder after building.
* The project has been tested using a fresh clone to ensure reproducibility.
