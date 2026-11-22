cmake_minimum_required(VERSION 3.28...3.31) #La version de CMake que soporta C++20, incluyendo los concepts
project(NexaDiagModule LANGUAGES CXX) #El nombre de mi proyecto

set(CMAKE_CXX_STANDARD 20) #El estandar de C++ que usaré es C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON) #Es obligatorio
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(NexaDiagModule
    src/main.cpp
    src/DiagnosticReading.cpp
)

target_include_directories(NexaDiagModule PUBLIC include) #Los archivos .h, .pp estan en include/