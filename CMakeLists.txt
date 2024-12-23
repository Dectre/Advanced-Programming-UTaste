cmake_minimum_required(VERSION 3.29)
project(UTaste)

set(CMAKE_CXX_STANDARD 20)

add_executable(UTaste src/main.cpp
        src/Taste.cpp
        src/Taste.h
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
        src/Manual.h
        src/User.cpp
        src/User.h
        src/Reserve.cpp
        src/Reserve.h
        src/Taste.h
        src/Taste.cpp)
