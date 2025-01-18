cmake_minimum_required(VERSION 3.30)
project(data_structure)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(data_structure
        src/main.cpp
        include/stack.h
        include/matrix.h
)
