## Description

This project implements a hierarchical DEVS model of an indoor humidity
regulation system using the Cadmium simulation framework.

The system includes:
- IndoorAir
- LeakageEstimator
- Humistat
- Humidifier

The goal is to regulate indoor humidity around 45% using discrete-event control.

---

## Requirements

- C++17 compatible compiler
- CMake (>= 3.10)
- Cadmium DEVS framework installed

---

## Build Instructions

From the project root directory:

```bash
cmake -S . -B build
cmake --build build -j
