cmake_minimum_required(VERSION 3.17)

project(6502emulator
        VERSION 0.1
        DESCRIPTION "A simple 6502 processor emulator."
        LANGUAGES CXX)

add_executable(main
               src/main.cpp)