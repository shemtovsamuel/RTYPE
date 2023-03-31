#!/bin/bash

run=false
cicd=false
engine=false

for arg in "$@"
do
    if [ "$arg" == "-run" ]
    then
        run=true
    elif [ "$arg" == "-cicd" ]
    then
        cide=true
    elif [ "$arg" == "-engine" ]
    then
        engine=true
    fi
done

if [ ! -d "engine" ]; then
    echo "Folder engine not found. Please run the script from the root of the repository."
    exit 1
fi

if [ ! -d "engine/build" ]; then
    echo "The engine/build folder does not exist. Please run the build-engine.sh script first."
    read -p "Do you want to run the build-engine.sh script? (y/n) " answer
    if [ "$answer" == "y" ]; then
        echo "Running build-engine.sh..."
        bash scripts/linux/build-engine.sh
        if [ ! -d "factorio" ]; then
            current_dir=$PWD
            while [ ! -d "factorio" ]; do
                cd ..
                if [ "$PWD" == "/" ]; then
                    echo "The factorio folder was not found in the file system tree."
                    exit 1
                fi
            done
        fi
    else
        echo "Aborting."
        exit 1
    fi
fi

if [ ! -d "factorio" ]; then
    echo "The factorio folder was not found in the file system tree. Please run the script from the root of the repository."
    exit 1
fi

if [ "$engine" = true ]; then
    echo "Running build-engine.sh..."
    bash scripts/linux/build-engine.sh
    if [ ! -d "factorio" ]; then
        current_dir=$PWD
        while [ ! -d "factorio" ]; do
            cd ..
            if [ "$PWD" == "/" ]; then
                echo "The factorio folder was not found in the file system tree."
                exit 1
            fi
        done
    fi
fi

if [ ! -d "factorio/lib" ]; then
    mkdir factorio/lib
fi

cp -R engine/build/lib factorio

if [ ! -d "factorio/include/engine" ]; then
    mkdir factorio/include/engine
fi

cp -R engine/include/ecs factorio/include/engine
cp -R engine/include/graphical factorio/include/engine

cd factorio
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
    ./bin/factorio
fi