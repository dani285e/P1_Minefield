#include "src/path/start_point/start_point.h"
#include "string.h"

// Funktion search_map der tager 5 ints og en pointer til map paremeter
int unit_counter(int y_1, int y_2, int x_1, int x_2, mapPoint* map, int mapSize, int unit)
{
    mapPoint* cell;
    int counter = 0;
    // For loop der tæller antal mines for side 1
    for (int y = y_1; y <= y_2; y++) {
        for (int x = x_1; x <= x_2; x++) {
            cell = get_cell(map, mapSize, y, x);
            if(cell->point_value == unit) {
                counter++;
            }
        }
    }
    return counter;
}

// compare_lines tager 4 ints som parametre den sammenligner dem og returnerer en værdi til function_find_a_start_line
int compare_lines(int counter1, int counter2, int counter3, int counter4) {
    if(counter1 >= counter2 && counter1 >= counter3 && counter1 >= counter4) {
        return 1; // Hvis counter1 er størst returneres 1
    } else if (counter2 >= counter3 && counter2 >= counter4) {
        return 2; // Hvis counter2 er størst returneres 2
    } else if (counter3 >= counter4) {
        return 3; // Hvis counter3 er størst returneres 3
    } else {
        return 4; // Ellers må counter4 være størst og der returneres 4
    }
}

void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers) {
    double size = mapSize;
    char start_line_name[20];
    int top_counter = unit_counter(0, ceil(size/2)-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    int left_counter = unit_counter(0, mapSize-1, 0, ceil(size/2)-1, map, mapSize, MINE_ENUM);
    int right_counter = unit_counter(0, mapSize-1, floor(size/2), mapSize-1, map, mapSize, MINE_ENUM);
    int bottom_counter = unit_counter(floor(size/2), mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);

    printf("\033[0m");
    printf("Top map is %d\n", top_counter);
    printf("Left map is %d\n", left_counter);
    printf("Right map is %d\n", right_counter);
    printf("Bottom map is %d\n", bottom_counter);

    int start_line = compare_lines(top_counter, left_counter, right_counter, bottom_counter); // Får værdien 1, 2, 3 eller 4 tilbage fra compare_lines

    switch (start_line) {
        case 1: strcpy(start_line_name, "Top line");
        break;
        case 2: strcpy(start_line_name, "Left line");
        break;
        case 3: strcpy(start_line_name, "Right line");
        break;
        case 4: strcpy(start_line_name, "Bottom line");
        break;
    }

    printf("\nThe start line is: %s\n\n", start_line_name);


    startpoint pointList[amount_of_deminers]; // Listen er ligeså lang som mængden af deminers der er

    int pointcounter = 0;
    double interval = mapSize / (amount_of_deminers); // En int værdi der bruges til at sætte de forskellige startpoints

    // Kan også skrives som switch mere effektivt (run time og calculations)
    if (start_line == 1) { // Hvis start_line == 1 er true vælges genereres startpunkterne på linje top
        for (int i = 0; i < amount_of_deminers; i++) { // For loop der laver amount_of_deminers antal start points
            pointList[pointcounter].start_point_x = ceil((interval / 2) + interval * (i)); // Det næste startpoints x-koordinat vil ikke være det samme som den tidligere
            pointList[pointcounter].start_point_y = 0; // Alle start point vil have y-koordinat = 1, da det er linje 1 vi arbejder på
            pointcounter++; // pointcounter tælles op så et nyt point vil blive lavet
        }
    } else if (start_line == 2) { // Hvis start_line == 2 er true genereres startpunkterne på linje venstre
        for (int i = 0; i < amount_of_deminers; i++) {
            pointList[pointcounter].start_point_x = 0;
            pointList[pointcounter].start_point_y = ceil((interval / 2) + interval * (i));
            pointcounter++;
        }
    } else if (start_line == 3) { // Hvis start_line == 3 er true genereres startpunkterne på linje højre
        for (int i = 0; i < amount_of_deminers; i++) {
            pointList[pointcounter].start_point_x = mapSize-1;
            pointList[pointcounter].start_point_y = ceil((interval / 2) + interval * (i));
            pointcounter++;
        }
    } else { // Ellers genereres startpunkterne på linje bund
        for (int i = 0; i < amount_of_deminers; i++) {
            pointList[pointcounter].start_point_x = ceil((interval / 2) + interval * (i));
            pointList[pointcounter].start_point_y = mapSize-1;
            pointcounter++;
        }
    }

    //mapPoint* cell;
    for(int i = 0; i < amount_of_deminers; i++) { // For loop der kører antal size gange
        deminers[i].x = pointList[i].start_point_x;
        deminers[i].y = pointList[i].start_point_y;
        deminers[i].distance = 0;
        deminers[i].time_taken = 0;

        printf("Start point for deminer %d is X:%d, Y:%d\n", i+1, pointList[i].start_point_x, pointList[i].start_point_y);
    }
}
