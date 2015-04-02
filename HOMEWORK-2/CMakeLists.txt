cmake_minimum_required(VERSION 3.1)
project(HOMEWORK_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(HOMEWORK_2 ${SOURCE_FILES} Array.h Matrix.h Board.h Cell.h Game.cpp Game.h Util.cpp Util.h)