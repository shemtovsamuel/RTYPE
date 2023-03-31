#!/bin/bash

if [ ! -d "engine" ]; then
    echo "Folder engine not found. Please run the script from the root of the repository."
    exit 1
fi

cd engine
mkdir build
cd build
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

if [ "$(uname)" == "Darwin" ]; then
    cmake -S .. -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc
else
    cmake ..
fi

make -j3