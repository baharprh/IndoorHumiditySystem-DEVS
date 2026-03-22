# Experiment Scripts

This directory contains runnable experiments for the indoor humidity model at multiple levels of the hierarchy.

## Top-Level Scenario Scripts

- `run_dry.sh`: runs the complete `IndoorHumiditySystem` with dry outdoor conditions from `input_data/outdoor_dry.txt`.
- `run_humid.sh`: runs the complete `IndoorHumiditySystem` with humid outdoor conditions from `input_data/outdoor_humid.txt`.
- `run_stepchange.sh`: runs the complete `IndoorHumiditySystem` with an outdoor humidity step change from `input_data/outdoor_stepchange.txt`.

Each top-level script produces:

- a full Cadmium execution trace in `logs/`
- a filtered system trajectory file named `*_system_rh.csv` containing the humidity trajectory extracted from `indoor_air/out_rh`

## Atomic Experiment Scripts

- `run_atomic_humistat.sh`: tests hysteresis control decisions in the `Humistat` atomic model.
- `run_atomic_humidifier.sh`: tests moisture injection outputs in the `Humidifier` atomic model.
- `run_atomic_leakage.sh`: tests leakage computation in the `LeakageEstimator` atomic model.
- `run_atomic_indoor_air.sh`: tests humidity accumulation and loss in the `IndoorAir` atomic model.

## Coupled Experiment Script

- `run_coupled_humidity_plant.sh`: tests the `HumidityPlant` coupled model by driving indoor relative humidity into the coupled controller and actuator chain.

## Utility Script

- `extract_system_rh.sh <full_log.csv> <system_output.csv>`: extracts the system humidity trajectory from a full execution trace.
