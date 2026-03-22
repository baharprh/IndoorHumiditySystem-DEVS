#!/bin/bash
set -e

cd "$(dirname "$0")/.."

make experiments
./bin/TEST_HUMIDIFIER input_data/humidifier_commands.txt 8 logs/atomic_humidifier.csv
