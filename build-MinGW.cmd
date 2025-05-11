@echo off

echo Configuring...
cmake -S. -Bbuild-MinGW -G "MinGW Makefiles"

echo Building...
cmake --build build-MinGW
