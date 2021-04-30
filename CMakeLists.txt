cmake_minimum_required(VERSION 3.19)
project(software2 C)

set(CMAKE_C_STANDARD 99)

add_executable(software2 main.c linktable.h linktable.c menu.h menu.c)