#!/bin/bash
set -e

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <full_log.csv> <system_output.csv>"
    exit 1
fi

input_log="$1"
output_log="$2"

awk -F',' '
BEGIN {
    print "time,rh"
}
NR > 1 && $3 == "indoor_air" && $4 == "out_rh" {
    print $1 "," $5
}
' "$input_log" > "$output_log"
