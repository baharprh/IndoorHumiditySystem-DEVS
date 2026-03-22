#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make experiments
./bin/TEST_INDOOR_AIR input_data/indoor_air_injection.txt input_data/indoor_air_leakage.txt 8 logs/atomic_indoor_air.csv
