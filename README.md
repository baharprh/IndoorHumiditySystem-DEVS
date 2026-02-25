# Indoor Humidity Regulation System (DEVS Model)

## Description

This project implements a hierarchical DEVS model of an indoor humidity
regulation system using the Cadmium simulation framework.

The system consists of the following components:

- **IndoorAir** – Maintains and updates indoor relative humidity (RH)
- **LeakageEstimator** – Models environmental humidity drift
- **Humistat** – Hysteresis-based ON/OFF controller
- **Humidifier** – Moisture injection actuator

The objective is to regulate indoor humidity around a 45% reference value
using discrete-event control with hysteresis (43%–47%).

---

## Requirements

- C++17 compatible compiler
- CMake (>= 3.10)
- Git
- Cadmium DEVS framework (included as submodule)

---

## Build Instructions (Manual Build)

From the project root directory:

```bash
cmake -S . -B build
cmake --build build -j
