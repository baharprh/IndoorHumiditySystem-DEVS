#!/bin/bash
set -e

# go to project root (one level above scripts/)
cd "$(dirname "$0")/.."

rm -rf build
cmake -S . -B build
cmake --build build -j

./build/main input_data/outdoor_dry.txt
