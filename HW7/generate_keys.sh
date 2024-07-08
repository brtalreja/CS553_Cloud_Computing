#!/bin/bash

#Printing the input arguments
echo "Welcome to the dataset generation tool!";
echo "Number of records to generate: $1"
output_file='keys.txt';

cat /dev/urandom | tr -dc '0-9a-zA-Z' | fold -w 10 | head -n $1 > $output_file;