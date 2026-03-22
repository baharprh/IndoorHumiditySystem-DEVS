#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make simulator

./bin/MAIN input_data/outdoor_stepchange.txt 200
./scripts/extract_system_rh.sh logs/outdoor_stepchange.csv logs/outdoor_stepchange_system_rh.csv
