#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make experiments
./bin/TEST_HUMIDITY_PLANT input_data/humidity_plant_rh_profile.txt 8 logs/coupled_humidity_plant.csv
