cmake_minimum_required(VERSION 3.29)
project(P1_Minefield C)

set(CMAKE_C_STANDARD 11)

add_library(mining_functions src/deminers/deminers.c "src/blast radius/Blast_Radius.c"
        src/deminers/deminers.h)
target_include_directories(mining_functions PUBLIC .)


add_executable(P1_Minefield main.c
        src/map/colour/colour.c
        src/map/colour/colour.h
        src/movement/movement.c
        src/movement/movement.h
        src/map/map.c
        src/map/map.h
        src/structs.h
)
target_link_libraries(P1_Minefield mining_functions)
add_executable(aPath aPath.c)
