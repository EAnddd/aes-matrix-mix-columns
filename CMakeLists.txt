cmake_minimum_required(VERSION 3.15)
project(supercomputers)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(NTL REQUIRED)
find_library(NTL_LIB NTL)
SET(CMAKE_EXE_LINKER_FLAGS "-lntl -lgmpxx -lgmp -lm")
add_executable(supercomputers main.cpp MatrixGenerator.cpp MixColumnsCoherently.cpp MixColumnsCoherently.h)

set(SOURCE_FILES
        MatrixGenerator.h
        MatrixGenerator.cpp)


