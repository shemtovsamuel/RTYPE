#!/bin/bash

run=false
cicd=false

for arg in "$@"
do
    if [ "$arg" == "-run" ]
    then
        run=true
    elif [ "$arg" == "-cicd" ]
    then
        cide=true
    fi
done

if [ ! -d "engine" ]; then
    echo "Folder engine not found. Please run the script from the root of the repository."
    exit 1
fi

cd rtype-server
mkdir build
cd build
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

if [ "$cicd" = true ]; then
    cmake -S .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
else
    cmake ..
fi

make -j3

if [ "$run" = true ]; then
    ./bin/rtype-server
fi