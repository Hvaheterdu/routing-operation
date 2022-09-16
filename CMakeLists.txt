cmake_minimum_required(VERSION 3.23)
project(routing-operation C)

set(CMAKE_C_STANDARD 17)

include_directories(include)
include_directories(libs)

add_executable(routing-operation ./src/router_main.c)