#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make clean
make simulator

./bin/MAIN input_data/outdoor_stepchange.txt 200