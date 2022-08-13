cmake_minimum_required(VERSION 3.0.0)
project(LCompiler VERSION 1.0.0)

set(CMAKE_BUILD_TYPE Debug)

find_package(fmt REQUIRED)

add_executable(LCompiler main.cpp)

target_link_libraries(LCompiler fmt::fmt)