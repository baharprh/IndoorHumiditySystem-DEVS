#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make experiments
./bin/TEST_LEAKAGE input_data/leakage_reference.txt 8 logs/atomic_leakage.csv
