# SSH Client Manager

SSH Client Manager (SMAN) allows you to easily connect to your SSH Servers using a simple user-defined list.

Supports x86 and ARM Windows, Linux, MacOS.

![grafik](https://github.com/user-attachments/assets/10140f46-30c8-45d0-a9ad-515266870dc3)


# Config File
Before running the program for the first time, you must create a config file. Use the example.conf for guidance on how the file is formatted.

## Windows
The config file should be stored under %LOCALAPPDATA$\SMAN\sman.conf

## Linux/MacOS
The config file should be stored under ~/.config/sman.conf

# Compiling

## Prerequisites
- Cmake
- GCC / Clang

## Automated Build
Run the build-MinGW.cmd (Windows) or build-unix.sh (Linux, MacOS) script and the Program will automatically compile to your current machine.

The compiled binary can be found in the build-MinGW or build-Unix folders and is called SMAN.exe (Win) or SMAN (Linux, MacOS).
