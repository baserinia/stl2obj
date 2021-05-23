cmake_minimum_required(VERSION 3.1)
project(cadreact CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
file(GLOB SOURCES "src/*.cpp")
 
add_executable(stl2obj ${SOURCES})

