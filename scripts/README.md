# Experiment Scripts

These scripts build the project and run the full IndoorHumiditySystem model using the provided input files.

## Scripts
- `run_dry.sh`  
  Runs the dry-outdoor scenario using `input_data/outdoor_dry.txt`  
  Output log: `logs/dry_run.log`

- `run_humid.sh`  
  Runs the humid-outdoor scenario using `input_data/outdoor_humid.txt`  
  Output log: `logs/humid_run.log`

- `run_stepchange.sh`  
  Runs the outdoor step-change scenario using `input_data/outdoor_stepchange.txt`  
  Output log: `logs/stepchange_run.log`

## How to run
```bash
./scripts/run_dry.sh
./scripts/run_humid.sh
./scripts/run_stepchange.sh

