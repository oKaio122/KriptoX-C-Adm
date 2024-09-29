cmake_minimum_required(VERSION 3.28)
project(KriptoX_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(KriptoX_C
        main.c
        kutils.c
        kutils.h)
