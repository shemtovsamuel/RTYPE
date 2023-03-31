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

if not exist "factorio" (
    echo "Factorio directory not found. Please run this script from the root directory of the repository."
    exit /b 1
)

REM Parameter to force the engine build
if "%1" == "force-engine" (
    echo "Forcing engine build..."
    call scripts\windows\build-engine.bat
    cd ../..
)

REM Copy the .lib files from the engine build directory to the client build directory
if not exist "factorio\lib" (
    mkdir factorio\lib
)
xcopy /s .\engine\build\lib .\factorio\lib /Y

REM Copy the .h and .hpp files from the engine include directory to the client include directory
if not exist "factorio\include\engine" (
    mkdir factorio\include\engine
)
xcopy /s .\engine\include .\factorio\include\engine /Y

cd factorio
mkdir build
cd build
conan install .. --build=missing
cmake ..
cmake --build . --config Release
cd bin
mkdir scripts
xcopy /s ..\src\scripts scripts /Y
mkdir assets
xcopy /s ..\assets assets /Y

factorio.exe