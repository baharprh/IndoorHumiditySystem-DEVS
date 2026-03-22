#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make simulator

./bin/MAIN input_data/outdoor_humid.txt 200
./scripts/extract_system_rh.sh logs/outdoor_humid.csv logs/outdoor_humid_system_rh.csv
