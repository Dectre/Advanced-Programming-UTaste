cmake_minimum_required(VERSION 3.29)
project(UTaste)

set(CMAKE_CXX_STANDARD 20)

add_executable(UTaste src/main.cpp
        src/UTaste.cpp
        src/UTaste.h
        src/System.cpp
        src/System.h
        src/Food.cpp
        src/Food.h
        src/Restaurant.cpp
        src/Restaurant.h
        src/District.cpp
        src/District.h
        src/Table.cpp
        src/Table.h
        src/Manual.h)
