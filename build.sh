#!/bin/bash

rm -rf build
mkdir build
cd build

cmake ..
make 
cd ..
rm output/cryp
cp build/cryp output/
# chmod +x output/cryp
