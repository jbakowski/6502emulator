cmake_minimum_required(VERSION 3.17)

project(6502emulator
        VERSION 0.1
        DESCRIPTION "A simple 6502 processor emulator."
        LANGUAGES CXX)

include_directories(
                ${PROJECT_SOURCE_DIR}/include
                ${PROJECT_SOURCE_DIR}/src
        )

file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/include/*.h"
        "${PROJECT_SOURCE_DIR}/include/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(main ${all_SRCS})