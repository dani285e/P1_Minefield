cmake_minimum_required(VERSION 3.29)
project(P1_Minefield C)

set(CMAKE_C_STANDARD 11)

add_executable(P1_Minefield main.c
        map/colour/colour.c
        map/colour/colour.h
        movement/movement.c
        movement/movement.h
        map/map.c
        map/map.h
        structs.h
)
