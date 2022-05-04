cmake_minimum_required(VERSION 3.22)
project(connect_four)

set(CMAKE_CXX_STANDARD 14)

add_executable(connect_four src/main.cpp src/board.cpp src/board.h src/util.h src/search.cpp src/search.h)
