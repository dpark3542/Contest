cmake_minimum_required(VERSION 3.28)
project(Contest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftrapv -D_GLIBCXX_DEBUG")

file(GLOB_RECURSE library "library/*.cpp" "library/*.h")

add_executable(output output/main.cpp)
add_executable(testrunner testrunner/main.cpp)
add_executable(test test.cpp ${library})