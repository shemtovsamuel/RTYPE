@echo off

if not exist "rtype-server" (
    echo "Rtype-server directory not found. Please run this script from the root directory of the repository."
    exit /b 1
)

cd rtype-server
mkdir build
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release