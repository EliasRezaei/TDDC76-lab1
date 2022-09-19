cmake_minimum_required(VERSION 3.16)


set(SOURCES
    test_main.cc
    time_test.cc
    time_test_ms.cc
    Time.h
    Time.cpp
    catch.hpp
)

project(lab1)
add_executable(lab1 ${SOURCES})

target_compile_options(lab1 PRIVATE -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast)






