cmake_minimum_required(VERSION 3.12)
project(maximosStdLib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_SOURCES "src/*.cpp")

add_library(maximosStdLib ${SRC_SOURCES})

add_subdirectory(tests)
