# Indoor Humidity Regulation System (DEVS Model)

## Description

This project implements a hierarchical DEVS model of an indoor humidity regulation system using the Cadmium simulation framework.

The system consists of:

- **IndoorAir** - indoor humidity dynamics
- **LeakageEstimator** - environmental humidity effects
- **Humidistat** - hysteresis controller (43%-47%)
- **Humidifier** - moisture actuator

The goal is to regulate indoor humidity around 45%.

## Project Structure

```text
IndoorHumiditySystem-DEVS/
├── src/
├── include/
├── input_data/
├── logs/
├── scripts/
├── docs/
├── cadmium/
├── makefile
└── README.md
```

## Build Instructions

From the project root:

```bash
make simulator
make experiments
```

## Run The Top Model

Run the full system directly:

```bash
./bin/MAIN input_data/outdoor_dry.txt 50
```

Or use the prepared scenario scripts:

```bash
./scripts/run_dry.sh
./scripts/run_humid.sh
./scripts/run_stepchange.sh
```

These scripts generate:

- full execution traces in `logs/outdoor_*.csv`
- filtered system-output trajectories in `logs/outdoor_*_system_rh.csv`

## Run Atomic And Coupled Experiments

The repository includes runnable experiments for incremental testing of the hierarchy:

```bash
./scripts/run_atomic_humistat.sh
./scripts/run_atomic_humidifier.sh
./scripts/run_atomic_leakage.sh
./scripts/run_atomic_indoor_air.sh
./scripts/run_coupled_humidity_plant.sh
```

See `scripts/README.md` for a short explanation of each script.

## Output

Example generated files:

```text
logs/outdoor_dry.csv
logs/outdoor_humid.csv
logs/outdoor_stepchange.csv
logs/outdoor_dry_system_rh.csv
logs/atomic_humistat.csv
logs/atomic_humidifier.csv
logs/atomic_leakage.csv
logs/atomic_indoor_air.csv
logs/coupled_humidity_plant.csv
```

The full Cadmium logs show atomic-model activity. For the top-level scenarios, the filtered `*_system_rh.csv` files make the system humidity trajectory explicit by extracting the `indoor_air/out_rh` rows, which correspond to the top-level `IndoorHumiditySystem/out_rh` coupling.

## Notes

- The project uses a local copy of Cadmium included in the repository.
- No external installation such as CMake, Boost, or vcpkg is required.
- The `logs/` directory is included with a `.gitkeep` file.
- Example CSV logs are included in the repository, and the scripts can regenerate them.
- The repository has been organized to support atomic, coupled, and top-level experimentation.

## Environment Note

This project was tested in a DEVSsim / Linux environment.

Build commands use `make`, so on Windows they should be executed using a Unix-like environment such as:

- Git Bash
- WSL (Windows Subsystem for Linux)

## Reproducibility

The project has been tested from a fresh clone with commands like:

```bash
git clone https://github.com/baharprh/IndoorHumiditySystem-DEVS.git
cd IndoorHumiditySystem-DEVS
make all
./scripts/run_dry.sh
./scripts/run_atomic_humistat.sh
./scripts/run_coupled_humidity_plant.sh
```
