cmake_minimum_required(VERSION 3.1)
project(cadreact CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
#file(GLOB SOURCES "src/*.cpp")
 
set(COMMON_SOURCES src/exportobj.cpp)
set(STL2OBJ_SOURCES src/stl2obj.cpp src/importstl.cpp)
set(OBJ2STL_SOURCES src/obj2stl.cpp src/importobj.cpp src/exportstl.cpp)

add_executable(stl2obj ${COMMON_SOURCES} ${STL2OBJ_SOURCES})
add_executable(obj2stl ${COMMON_SOURCES} ${OBJ2STL_SOURCES})
