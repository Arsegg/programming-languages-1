cmake_minimum_required(VERSION 3.1)
project(SettingsLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_library(settings SHARED settings.h)