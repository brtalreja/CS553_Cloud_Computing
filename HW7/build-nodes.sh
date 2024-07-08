#!/bin/bash

sudo apt update -y && sudo apt upgrade -y

for i in {1..8}
do
    lxc launch images:ubuntu/22.04 smallnode${i} --storage storage-lvm --config limits.cpu=3 --config limits.memory=12GB
    lxc config device set smallnode${i} root size=24GB
done

# Redis
sudo apt install redis-server
sudo service redis restart

# Cassandra
sudo apt install -y python3
sudo apt install python3-pip -y
pip3 install cassandra-driver


# Mongodb
echo "deb http://security.ubuntu.com/ubuntu focal-security main" | sudo tee /etc/apt/sources.list.d/focal-security.list
sudo apt-get update
sudo apt-get install libssl1.1
sudo apt install -y mongodb-org
