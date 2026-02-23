#!/bin/bash
set -e

cd "$(dirname "$0")/.."

rm -rf build
cmake -S . -B build
cmake --build build -j

./build/main input_data/outdoor_stepchange.txt
