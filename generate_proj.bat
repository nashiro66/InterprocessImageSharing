@echo off

if not exist build_sender (
    mkdir build_sender
)
set SENDER=ON
cmake -S . -B build_sender^
    -G "Visual Studio 16 2019"^
    -A x64^
    -D SENDER=%SENDER%

if not exist build_receiver (
    mkdir build_receiver
)
set SENDER=OFF
cmake -S . -B build_receiver^
    -G "Visual Studio 16 2019"^
    -A x64^
    -D SENDER=%SENDER%