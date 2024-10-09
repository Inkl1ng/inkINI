cmake_minimum_required(VERSION 3.22)

project(inkINI CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

add_library(inkINI
    src/ini_file.cpp)
target_include_directories(inkINI PUBLIC include)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE inkINI)
