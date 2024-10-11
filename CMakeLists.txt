cmake_minimum_required(VERSION 3.22)

project(inkINI C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(inkINI
    src/inkINI.c)
target_include_directories(inkINI PUBLIC include)
target_compile_features(inkINI PUBLIC c_std_99)

add_executable(test test/test.c)
target_link_libraries(test PRIVATE inkINI)
target_compile_features(inkINI PUBLIC c_std_99)
