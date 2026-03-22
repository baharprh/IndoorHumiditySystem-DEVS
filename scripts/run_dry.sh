#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make simulator

./bin/MAIN input_data/outdoor_dry.txt 200
./scripts/extract_system_rh.sh logs/outdoor_dry.csv logs/outdoor_dry_system_rh.csv
