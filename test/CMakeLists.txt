# We create a test driver executable
add_executable(test_main test_main.c
)

# We link the library to the test driver
target_link_libraries(test_main PRIVATE mining_functions)

# Add the internal test library
add_library(test_main_internal
        tests/path/test_path.c
        tests/path/test_path.h
        tests/map/test_map.c
        tests/map/test_map.h
        tests/deminers/test_deminers.c
        tests/deminers/test_deminers.h
)


# We add the test executable to CTest
add_test(NAME test_blast_radius
        COMMAND test_blast_radius)
add_test(NAME test_deminers
        COMMAND test_deminers)
add_test(NAME test_map
        COMMAND test_map)
add_test(NAME test_path
        COMMAND test_path)
