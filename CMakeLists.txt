cmake_minimum_required(VERSION 3.16)
project(Contest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftrapv -D_GLIBCXX_DEBUG")

add_executable(output output/main.cpp)
add_executable(testrunner testrunner/main.cpp)

add_executable(test test.cpp run.template run_windows.template submission.template task.template)