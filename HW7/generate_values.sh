#!/bin/bash

#Printing the input arguments
echo "Welcome to the dataset generation tool!";
echo "Number of records to generate: $1"
Output_file='values.txt'

cat /dev/urandom | tr -dc '0-9a-zA-Z' | fold -w 90 | head -n $1 > $Output_file;