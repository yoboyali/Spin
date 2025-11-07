cmake_minimum_required(VERSION 3.31)
project(Spin C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
add_executable(Spin main.c)
