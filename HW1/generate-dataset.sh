#!/bin/bash

USAGE="Usage: ./generate-dataset.sh $1 $2"

echo $USAGE

Filename="$1"
counter="$2"

# TO-DO finish implementation.
> $Filename.txt

for (( c=1;c<=counter;c++))

do

echo $SRANDOM $SRANDOM $(pwgen -0  100) >> $Filename.txt

done
