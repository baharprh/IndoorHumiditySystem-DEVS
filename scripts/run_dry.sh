#!/usr/bin/env bash
set -e

mkdir -p build logs

cmake -S . -B build
cmake --build build -j

./build/main input_data/outdoor_dry.txt > logs/dry_run.log
