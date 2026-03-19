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

```bash
make simulator
```

## Run Simulation

Example:

```bash
./bin/MAIN input_data/outdoor_dry.txt 50
```

## Run All Scenarios

```bash
./scripts/run_dry.sh
./scripts/run_humid.sh
./scripts/run_stepchange.sh
```

## Output

Logs are generated in:

```bash
logs/
```
## Build Instructions

```bash
make simulator
```

## Run Simulation

Example:

```bash
./bin/MAIN input_data/outdoor_dry.txt 50
```

## Run All Scenarios

```bash
./scripts/run_dry.sh
./scripts/run_humid.sh
./scripts/run_stepchange.sh
```

## Output

Logs are generated in:

```bash
logs/
```
