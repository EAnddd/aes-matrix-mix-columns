cmake_minimum_required(VERSION 3.15)
project(supercomputers)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_EXE_LINKER_FLAGS "-lntl -lgmpxx -lgmp -lm")
add_executable(supercomputers main.cpp MatrixGenerator.cpp MixColumnsCoherently.cpp MixColumnsCoherently.h)


set(SOURCE_FILES
        MatrixGenerator.h
        MatrixGenerator.cpp)


