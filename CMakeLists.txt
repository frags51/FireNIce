cmake_minimum_required(VERSION 3.8)
project(FireNIce)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        trial/trial.h
        trial/trial.cpp)

add_executable(FireNIce ${SOURCE_FILES})

target_link_libraries(FireNIce
        sfml-window
        sfml-system
        sfml-graphics
        sfml-audio
        sfml-network)
