@echo off

if not exist "engine" (
    echo "Engine directory not found. Please run this script from the root directory of the repository."
    exit /b 1
)

cd engine
mkdir build
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release