//
// Created by danie on 09-12-2024.
//

#include "test_main.h"

int main() {
    // Run all tests
    printf("Test test_blast_radius.c:\n");
    test_blast_radius_func();
    printf("\n\n");

    printf("Test test_deminers.c:\n");
    printf("This is not the deminers your looking for\n\n");

    printf("Test test_map.c:\n");
    printf("test_get_cell\n");
    test_get_cell();
    printf("test_create_map\n");
    test_create_map();
    printf("\n\n");

    printf("Test test_path.c:\n");
    test_find_start_line();




    printf("All tests passed!\n");
    return 0;
}