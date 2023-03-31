@echo off
setlocal enabledelayedexpansion

if not exist "engine" (
    echo "Engine directory not found. Please run this script from the root directory of the repository."
    exit /b 1
)

if not exist "engine\build" (
    echo "Engine build directory not found. Please run the build-engine.bat script first."
    echo "Or do you want to run it now? (y/n)"
    set /p answer=
    if "!answer!" == "y" (
        echo "Running build-engine.bat..."
        call scripts\windows\build-engine.bat
        cd ../..
    ) else (
        echo "Aborting..."
        exit /b 1
    )
)

if not exist "rtype-server" (
    echo "Rtype-server directory not found. Please run this script from the root directory of the repository."
    exit /b 1
)

REM Parameter to force the engine build
if "%1" == "force-engine" (
    echo "Forcing engine build..."
    call scripts\windows\build-engine.bat
    cd ../..
)

REM Copy the .lib files from the engine build directory to the server build directory
if not exist "rtype-server\lib" (
    mkdir rtype-server\lib
)
xcopy /s .\engine\build\lib .\rtype-server\lib /Y

REM Copy the .h and .hpp files from the engine include directory to the server include directory
if not exist "rtype-server\include\engine" (
    mkdir rtype-server\include\engine
)
xcopy /s .\engine\include .\rtype-server\include\engine /Y

cd rtype-server
mkdir build
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release

cd bin

echo "Packing client..."
tar.exe -czf rtype-server.tar.gz rtype-server.exe