#!/bin/bash

run=false
cicd=false
engine=false
pack=false

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
    elif [ "$arg" == "-pack" ]
    then
        pack=true
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
        if [ ! -d "rtype-client" ]; then
            current_dir=$PWD
            while [ ! -d "rtype-client" ]; do
                cd ..
                if [ "$PWD" == "/" ]; then
                    echo "The rtype-client folder was not found in the file system tree."
                    exit 1
                fi
            done
        fi
    else
        echo "Aborting."
        exit 1
    fi
fi

if [ ! -d "rtype-client" ]; then
    echo "The rtype-client folder was not found in the file system tree. Please run the script from the root of the repository."
    exit 1
fi

if [ "$engine" = true ]; then
    echo "Running build-engine.sh..."
    bash scripts/linux/build-engine.sh
    if [ ! -d "rtype-client" ]; then
        current_dir=$PWD
        while [ ! -d "rtype-client" ]; do
            cd ..
            if [ "$PWD" == "/" ]; then
                echo "The rtype-client folder was not found in the file system tree."
                exit 1
            fi
        done
    fi
fi

if [ ! -d "rtype-client/lib" ]; then
    mkdir rtype-client/lib
fi

cp -R engine/build/lib rtype-client

if [ ! -d "rtype-client/include/engine" ]; then
    mkdir rtype-client/include/engine
fi

cp -R engine/include/ecs rtype-client/include/engine
cp -R engine/include/graphical rtype-client/include/engine

cd rtype-client
mkdir build
cd build
conan install .. --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True

if [ "$cicd" = true ]; then
    cmake -S .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1
else
    if [ "$(uname)" == "Darwin" ]; then
        cmake -S .. -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc
    else
        cmake ..
    fi
fi

make -j3

if [ "$run" = true ]; then
  if [ "$(uname)" == "Darwin" ]; then
      export DYLD_LIBRARY_PATH=./bin
      ./bin/rtype-client
  else
      ./bin/rtype-client
  fi
fi

if [ "$pack" = true ]; then
    echo "Packing the client..."
    cpack
fi