cmake_minimum_required(VERSION 3.5)
project(Basics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp functions.h lab1.cpp lab2.cpp lab3.cpp lab4.cpp lab6.cpp lab8.cpp lab9.cpp lab10.cpp)
add_executable(Basics ${SOURCE_FILES})