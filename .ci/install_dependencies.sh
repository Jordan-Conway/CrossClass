#!/bin/bash
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev

if [ $? -ne 0 ]; then
    echo "Failed to install dependencies"
    exit 1
fi

echo "Dependencies installed"