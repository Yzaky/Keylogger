cmake_minimum_required(VERSION 3.7)
project(MyKeylogger)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Sources/main.cpp Headers/KCsts.h Headers/Helper.h)
add_executable(MyKeylogger ${SOURCE_FILES})