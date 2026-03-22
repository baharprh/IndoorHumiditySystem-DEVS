#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make experiments
./bin/TEST_HUMISTAT input_data/humistat_ramp.txt 8 logs/atomic_humistat.csv
