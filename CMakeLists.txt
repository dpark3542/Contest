cmake_minimum_required(VERSION 3.17)
project(Contest)

add_definitions(-std=c++17)

add_executable(output output/main.cpp)
add_executable(testrunner testrunner/main.cpp)