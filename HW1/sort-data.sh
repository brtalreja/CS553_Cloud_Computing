#!/bin/bash

USAGE="Usage: ./sort-data.sh $1 $2"

echo $USAGE

input_filename=$1
output_filename=$2

# TO-DO finish implementation

sort -k 1n $input_filename.txt -o $output_filename.txt
