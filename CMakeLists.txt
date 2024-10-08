cmake_minimum_required(VERSION 3.28)
project(Contest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftrapv -D_GLIBCXX_DEBUG")

include_directories("include")

get_filename_component(STANDALONE_SCRIPT "bin/standalone.py" ABSOLUTE)

file(GLOB_RECURSE tasks "src/*.cpp")
foreach(TASK ${tasks})
    get_filename_component(TARGET_NAME ${TASK} NAME_WE)
    add_executable(${TARGET_NAME} ${TASK})
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD COMMAND "python" ${STANDALONE_SCRIPT} ${CMAKE_SOURCE_DIR} ${TARGET_NAME} COMMENT "Building standalone file")
endforeach()
