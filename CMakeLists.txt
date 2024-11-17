cmake_minimum_required(VERSION 3.18)
project(KriptoX_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(KriptoX_C_User
        kutils.c
        kutils.h
        main.c)

add_executable(KriptoX_C_Admin
        kutils.c
        kutils.h
        kadm.c)