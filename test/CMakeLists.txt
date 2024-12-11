set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")



# We create a test driver executable
add_executable(test_blast_radius test_blast_radius.c ../src/blast_radius/blast_radius.c)
add_executable(test_map test_map.c ../src/map/map.c)
add_executable(test_path test_path.c ../src/path/path.c)
add_executable(test_start_point test_start_point.c ../src/path/start_point/start_point.c)
add_executable(test_obstacles test_obstacles.c ../src/path/path.c)


# We link the library to the test driver
target_link_libraries(test_blast_radius PRIVATE mining_functions)
target_link_libraries(test_map PRIVATE mining_functions)
target_link_libraries(test_path PRIVATE mining_functions)
target_link_libraries(test_start_point PRIVATE mining_functions)
target_link_libraries(test_obstacles PRIVATE mining_functions)


# We add the test executable to CTest
add_test(NAME test_blast_radius COMMAND test_blast_radius)
add_test(NAME test_map COMMAND test_map)
add_test(NAME test_path COMMAND test_path)
add_test(NAME test_start_point COMMAND test_start_point)
add_test(NAME test_obstacles COMMAND test_obstacles)
