# !bin/bash

# for 1 largenode
touch /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-3GB
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-3GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-3GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-3GB

touch /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-6GB
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-6GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-6GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-6GB

touch /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-12GB
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-12GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-12GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-12GB

touch /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-24GB
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-24GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-24GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-24GB

# for 1 smallnode
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-3GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-3GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-3GB
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-6GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-6GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-6GB
time sort -k 1 /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/data-12GB -o /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-12GB --parallel=16
rm -rf /exports/projects/cs553-fall2022-hw6-yz-msq-bt/data/sort-12GB