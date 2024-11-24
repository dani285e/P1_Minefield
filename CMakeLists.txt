cmake_minimum_required(VERSION 3.29)
project(P1_Minefield C)

set(CMAKE_C_STANDARD 11)

add_library(mining_functions deminers.c blast_radius.c
        deminers.h)
target_include_directories(mining_functions PUBLIC .)

add_executable(P1_Minefield main.c)
target_link_libraries(P1_Minefield mining_functions)