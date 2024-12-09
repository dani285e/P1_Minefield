add_library(mining_functions

        blast_radius/blast_radius.c
        blast_radius/blast_radius.h
        deminers/deminers.c
        deminers/deminers.h
        map/map.c
        map/map.h
        map/colour/colour.c
        map/colour/colour.h
        path/start_point/start_point.c
        path/start_point/start_point.h
        path/path.c
        path/path.h
        structs.h
)

target_include_directories(mining_functions PUBLIC ..)


add_executable(P1_Minefield main.c)
target_link_libraries(P1_Minefield mining_functions)
