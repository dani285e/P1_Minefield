cmake_minimum_required(VERSION 3.29)
project(P1_Minefield C)

set(CMAKE_C_STANDARD 11)

add_library(mining_functions

        src/blast_radius/blast_radius.c
        src/blast_radius/blast_radius.h
        src/map/map.c
        src/map/map.h
        src/map/colour/colour.c
        src/map/colour/colour.h
        src/path/start_point/start_point.c
        src/path/start_point/start_point.h
        src/path/path.c
        src/path/path.h
        src/structs.h
)

target_include_directories(mining_functions PUBLIC .)

add_executable(P1_Minefield main.c)
target_link_libraries(P1_Minefield mining_functions)