# Indoor Humidity Regulation System (DEVS Model)

## Description
This project implements a hierarchical DEVS model of an indoor humidity regulation system using the Cadmium simulation framework.

The system consists of:
- **IndoorAir** – indoor humidity dynamics  
- **LeakageEstimator** – environmental humidity effects  
- **Humidistat** – hysteresis controller (43%–47%)  
- **Humidifier** – moisture actuator  

The goal is to regulate indoor humidity around 45%.

---

## Project Structure

IndoorHumiditySystem-DEVS/
├── src/
├── include/
├── input_data/
├── logs/
├── scripts/
├── cadmium/
├── makefile
├── README.md


---

## Build Instructions
From the project root:

```bash
make simulator
Run Simulation

Example:

./bin/MAIN input_data/outdoor_dry.txt 50
Run All Scenarios
./scripts/run_dry.sh
./scripts/run_humid.sh
./scripts/run_stepchange.sh
Output

Logs are generated in:

logs/

Example:

logs/outdoor_dry.csv
logs/outdoor_humid.csv
logs/outdoor_stepchange.csv
Notes

The project uses a local copy of Cadmium included in the repository

No external installation (CMake, Boost, vcpkg) is required

Verified to work from a fresh clone

Environment Note

This project was tested in a DEVSsim / Linux environment.

Build commands use make, so on Windows they should be executed using a Unix-like environment such as:

Git Bash

WSL (Windows Subsystem for Linux)

Reproducibility

The project has been tested from a fresh clone:

git clone https://github.com/baharprh/IndoorHumiditySystem-DEVS.git
cd IndoorHumiditySystem-DEVS
make simulator
./bin/MAIN input_data/outdoor_dry.txt 50
