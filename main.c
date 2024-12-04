

#include "src//deminers/deminers.h"
#include "src/map/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MINES 20




mapPoint* get_cell(mapPoint* map, int mapSize, int y, int x);
void check_a_point(int mapSize, mapPoint* map);
int unit_counter(int y_1, int y_2, int x_1, int x_2, mapPoint* map, int mapSize, int unit);
int compare_lines(int counter1, int counter2, int counter3, int counter4);
int find_shortest_path_distance_sorter(const void *ep1, const void *ep2);
void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);
void move_deminer(mapPoint* map, int mapSize, int x, int y);
void print_map_info(int mapSize, mapPoint* map);
void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers);
int function_find_start_line_v2 (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers);


void find_shortest_path_v2(int map_size, mapPoint* map, int amount_of_deminers, Deminer* deminer, int start_line);

int main(void) {

    //deminer();
    srand(time(NULL));

    mapPoint* map = NULL;
    //int mapSize = (rand()% 20) + 10;
    int mapSize = 13;
    int amount_of_mines = 0;
    int amount_of_deminers = 3; // SKAL VÆRE GIVET FRA EN ANDEN FUNKTION
    map = (mapPoint*)malloc(sizeof(mapPoint)*mapSize*mapSize);
    Deminer* deminers = NULL;
    deminers = (Deminer*)malloc(sizeof(Deminer)*amount_of_deminers);

    create_map(mapSize, map, &amount_of_mines);
    print_map(mapSize, map, deminers, amount_of_deminers);
    function_find_start_line(mapSize, map, deminers, amount_of_deminers);
    int start_line = function_find_start_line_v2(mapSize, map, deminers, amount_of_deminers);
    print_map(mapSize, map, deminers, amount_of_deminers);
    print_map_info(mapSize, map);
    //check_a_point(mapSize, map);
    //find_shortest_path(mapSize, map, amount_of_mines);
    //print_map(mapSize, map);
    //find_shortest_path(mapSize, map, amount_of_deminers, deminers);
    find_shortest_path_v2(mapSize, map, amount_of_deminers, deminers, start_line);

    int total_distance = 0;
    for (int i = 0; i < amount_of_deminers; i++) {
        printf("Total distance walked for deminer %d is %d\n", i+1,  deminers[i].distance);
        total_distance += deminers[i].distance;
    }
    printf("Total distance walked all deminers is %d\n", total_distance);


    free(map);
    free(deminers);

    return 0;
}


void move_deminer(mapPoint* map, int mapSize, int x, int y) {
    mapPoint* cell;
    cell = get_cell(map, mapSize, y, x);
    cell->point_value = DEMINER_ENUM;
}



void print_map_info(int mapSize, mapPoint* map) {
    int mineCounter = unit_counter(0, mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    printf("\033[0m");
    printf("\n\n\n");
    printf("There is a total of %d mines there needs to be cleared\n\n", mineCounter);
    printf("They are located at the following points\n");
    int counter = 0;
    for(int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            if (get_cell(map, mapSize, y, x)->point_value == MINE_ENUM) {
                counter = counter + 1;
                printf("Mine %-2d is located at point X = %-2d, Y = %d\n", counter, x, y);
            }
        }
    }
}

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
int function_find_start_line_v2 (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers) {
    printf("\033[0m");
    double size = mapSize;
    int top_counter = unit_counter(0, ceil(size/2)-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    int left_counter = unit_counter(0, mapSize-1, 0, ceil(size/2)-1, map, mapSize, MINE_ENUM);
    int right_counter = unit_counter(0, mapSize-1, floor(size/2), mapSize-1, map, mapSize, MINE_ENUM);
    int bottom_counter = unit_counter(floor(size/2), mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);

    printf("Top map is %d\n", top_counter);
    printf("Left map is %d\n", left_counter);
    printf("Right map is %d\n", right_counter);
    printf("Bottom map is %d\n", bottom_counter);

    int start_line = compare_lines(top_counter, left_counter, right_counter, bottom_counter); // Får værdien 1, 2, 3 eller 4 tilbage fra compare_lines
    printf("\nThe start line is: Line %d\n\n", start_line);

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
        deminers[i].status = 0;
        deminers[i].distance = 0;

        printf("Start point for deminer %d is X:%d, Y:%d\n", i+1, pointList[i].start_point_x, pointList[i].start_point_y);
    }
    return start_line;
}

void function_find_start_line (int mapSize, mapPoint* map, Deminer* deminers, int amount_of_deminers) {
    printf("\033[0m");
    double size = mapSize;
    int top_counter = unit_counter(0, ceil(size/2)-1, 0, mapSize-1, map, mapSize, MINE_ENUM);
    int left_counter = unit_counter(0, mapSize-1, 0, ceil(size/2)-1, map, mapSize, MINE_ENUM);
    int right_counter = unit_counter(0, mapSize-1, floor(size/2), mapSize-1, map, mapSize, MINE_ENUM);
    int bottom_counter = unit_counter(floor(size/2), mapSize-1, 0, mapSize-1, map, mapSize, MINE_ENUM);

    printf("Top map is %d\n", top_counter);
    printf("Left map is %d\n", left_counter);
    printf("Right map is %d\n", right_counter);
    printf("Bottom map is %d\n", bottom_counter);

    int start_line = compare_lines(top_counter, left_counter, right_counter, bottom_counter); // Får værdien 1, 2, 3 eller 4 tilbage fra compare_lines
    printf("\nThe start line is: Line %d\n\n", start_line);

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
        deminers[i].status = 0;
        deminers[i].distance = 0;

        printf("Start point for deminer %d is X:%d, Y:%d\n", i+1, pointList[i].start_point_x, pointList[i].start_point_y);
    }
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

void check_deminer_status(int amount_of_deminers, Deminer* deminers)
{
    // Check if the number of active deminers equals the number of mines
    int active_deminers = 0;
    for (int i = 0; i < amount_of_deminers; i++)
    {
        if (deminers[i].status == 1)
        {
            active_deminers++;
        }
    }

    if (active_deminers == amount_of_deminers)
    {
        // If the number of active deminers equals the number of deminers, set all deminers' status to 0
        for (int k = 0; k < amount_of_deminers; k++)
        {
            deminers[k].status = 0;
        }
    }
}



// Manhattan Distance
int calculate_manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

void assign_deminer(int closest_deminer_1, int x, int y, int shortest_distance_1, Deminer* deminer, mapPoint* cell)
{
    printf("Shortest path assigned to Deminer %d for mine at X:%d, Y:%d with distance %d\n",
       closest_deminer_1, x, y, shortest_distance_1);

    deminer[closest_deminer_1].status = 1; // Mark as handling the mine

    // Update the deminer's position to the mine's location
    deminer[closest_deminer_1].x = x;
    deminer[closest_deminer_1].y = y;

    // Perform any necessary mine clearing actions here
    cell->point_value = 0; // Clear the mine
}

int find_closes_denminer(Deminer* deminer, int amount_of_deminers, int shortest_distance_1, int closest_deminer_1, int shortest_distance_2, int closest_deminer_2, int x, int y)
{
    // Compare distances for all active deminers
    for (int i = 0; i < amount_of_deminers; i++) {
        if (deminer[i].status == 0) { // Check if deminer is active
            int distance = calculate_manhattan_distance(deminer[i].x, deminer[i].y, x, y);

            printf("Deminer: %d: The distance is %d to mine X:%d, Y:%d\n", i, distance, x, y);
            if (distance < shortest_distance_1) {
                // Update second closest before updating the closest
                shortest_distance_2 = shortest_distance_1;
                closest_deminer_2 = closest_deminer_1;

                // Update closest
                shortest_distance_1 = distance;
                closest_deminer_1 = i;
            } else if (distance < shortest_distance_2) {
                // Update second closest only
                shortest_distance_2 = distance;
                closest_deminer_2 = i;
            }
        }
    }
    return closest_deminer_1;
}
// Funktion der skal kunne genererer en rute med hjælp fra Nearest Neighbor Algoritmen
// Først skal den vidde sit startspunkt
// Så skal den kunne vidde afstanden til alle andre miner
// Så skal den vælge den mine der er tættest på og gå hen til den og punktets værdi sættes til 'E'
// Så skal den gøre det hele igen indtil der ikke er flere miner
void find_shortest_path_v2(int map_size, mapPoint* map, int amount_of_deminers, Deminer* deminer, int start_line) {
    mapPoint* cell;
    int active_deminers = amount_of_deminers;
    int shortest_distance_1, shortest_distance_2;
    int closest_deminer_1, closest_deminer_2;

    // Initialize deminers' positions
    for (int i = 0; i < amount_of_deminers; i++) {
        deminer[i].x = -1;
        deminer[i].y = -1;
    }

    // Define iteration boundaries and directions based on the starting line
    int x_start, x_end, x_step;
    int y_start, y_end, y_step;

    if (start_line == 1) { // Top (horizontal first, vertical after)
        y_start = 0; y_end = map_size; y_step = 1;
        x_start = 0; x_end = map_size; x_step = 1;
    } else if (start_line == 2) { // Left (vertical first, horizontal after)
        x_start = 0; x_end = map_size; x_step = 1;
        y_start = 0; y_end = map_size; y_step = 1;
    } else if (start_line == 3) { // Right (horizontal first, vertical after)
        x_start = map_size - 1; x_end = -1; x_step = -1;
        y_start = 0; y_end = map_size; y_step = 1;
    } else { // Bottom (vertical first, horizontal after)
        y_start = map_size - 1; y_end = -1; y_step = -1;
        x_start = 0; x_end = map_size; x_step = 1;
    }

    while (active_deminers > 0) {
        if (start_line == 1 || start_line == 4)
        {
            for (int y = y_start; y != y_end; y += y_step) {
                for (int x = x_start; x != x_end; x += x_step) {
                    cell = get_cell(map, map_size, y, x);

                    if (cell->point_value == MINE_ENUM) {
                        // Reset distances and indices for this mine
                        shortest_distance_1 = shortest_distance_2 = INT_MAX;
                        closest_deminer_1 = closest_deminer_2 = -1;

                        closest_deminer_1 = find_closes_denminer(deminer, amount_of_deminers, shortest_distance_1, closest_deminer_1, shortest_distance_2, closest_deminer_2, x, y);


                        // Assign the mine to the closest deminer and update status
                        if (closest_deminer_1 != -1) {
                            assign_deminer(closest_deminer_1, x, y, shortest_distance_1, deminer, cell);

                            active_deminers--;

                            print_map(map_size, map, deminer, amount_of_deminers);
                            char choice;
                            scanf(" %c", &choice);
                        }
                    }
                    if (active_deminers == 0 && y != y_end && x != x_end)
                    {
                        check_deminer_status(amount_of_deminers, deminer);
                        active_deminers = amount_of_deminers;
                    }
                }
            }
        }
        if (start_line == 2 || start_line == 3)
        {
            for (int x = x_start; x != x_end; x += x_step) {
                for (int y = y_start; y != x_end; y += y_step) {
                    cell = get_cell(map, map_size, y, x);

                    if (cell->point_value == MINE_ENUM) {
                        // Reset distances and indices for this mine
                        shortest_distance_1 = shortest_distance_2 = INT_MAX;
                        closest_deminer_1 = closest_deminer_2 = -1;

                        closest_deminer_1 = find_closes_denminer(deminer, amount_of_deminers, shortest_distance_1, closest_deminer_1, shortest_distance_2, closest_deminer_2, x, y);


                        // Assign the mine to the closest deminer and update status
                        if (closest_deminer_1 != -1) {
                            assign_deminer(closest_deminer_1, x, y, shortest_distance_1, deminer, cell);

                            active_deminers--;

                            print_map(map_size, map, deminer, amount_of_deminers);
                            char choice;
                            scanf(" %c", &choice);
                        }
                    }
                    if (active_deminers == 0 && y != y_end && x != x_end)
                    {
                        check_deminer_status(amount_of_deminers, deminer);
                        active_deminers = amount_of_deminers;
                    }
                }
            }
        }



        // Iterate over the map to find the closest mine
        for (int y = y_start; y != y_end; y += y_step) {
            for (int x = x_start; x != x_end; x += x_step) {
                cell = get_cell(map, map_size, y, x);

                if (cell->point_value == MINE_ENUM) {
                    // Reset distances and indices for this mine
                    shortest_distance_1 = shortest_distance_2 = INT_MAX;
                    closest_deminer_1 = closest_deminer_2 = -1;

                    closest_deminer_1 = find_closes_denminer(deminer, amount_of_deminers, shortest_distance_1, closest_deminer_1, shortest_distance_2, closest_deminer_2, x, y);


                    // Assign the mine to the closest deminer and update status
                    if (closest_deminer_1 != -1) {
                        assign_deminer(closest_deminer_1, x, y, shortest_distance_1, deminer, cell);

                        active_deminers--;

                        print_map(map_size, map, deminer, amount_of_deminers);
                        char choice;
                        scanf(" %c", &choice);
                    }
                }
                if (active_deminers == 0 && y != y_end && x != x_end)
                {
                    check_deminer_status(amount_of_deminers, deminer);
                    active_deminers = amount_of_deminers;
                }
            }
        }
    }
}




void find_shortest_path (int mapSize, mapPoint* map, int amount_of_deminers, Deminer* deminers) {
    int amount_of_mines = -1;
    int distance;
    int shortest_distance = 100;
    int shortest_distance_x = 0;
    int shortest_distance_y = 0;
    int whose_turn = 0;

    int deminer_i = 0;
    mapPoint* cell;
    //deminer* current_deminer = deminers[0];



    while (amount_of_mines != 1) {
        amount_of_mines = 0;
        shortest_distance_x = 0;
        shortest_distance_y = 0;
        shortest_distance = 100;
        for (int y = 0; y < mapSize; y++) {
            for (int x = 0; x < mapSize; x++) {
                cell = get_cell(map, mapSize, y, x);
                check_deminer_status(amount_of_deminers, deminers);
                if (cell->point_value == MINE_ENUM) {
                    amount_of_mines++;
                    int temp = 0;
                    for (int i = 0; i < amount_of_deminers; i++)
                    {
                        if (deminers[i].status != 1)
                        {
                            distance = fabs(deminers[i].x - cell->point_value_x) + fabs(deminers[i].y - cell->point_value_y);
                            if (temp < distance)
                            {
                                temp = distance;
                                deminer_i = i;
                            }
                        }
                    }
                    deminers[deminer_i].status = 1;
                    distance = temp;
                    //distance = fabs(deminers[whose_turn].x - cell->point_value_x) + fabs(deminers[whose_turn].y - cell->point_value_y);
                    printf("The distance is %d to mine X:%d, Y:%d\n", distance, x, y);
                    if (distance < shortest_distance) {
                        shortest_distance = distance;
                        shortest_distance_x = x;
                        shortest_distance_y = y;
                    }
                }
            }
        }
        printf("The shortest distance is %d to mine X:%d, Y:%d\n", shortest_distance, shortest_distance_x, shortest_distance_y);
        deminers[deminer_i].distance += shortest_distance;
        //printf("So far deminer 0 has walked %d\n", deminers[0].distance);
        deminers[whose_turn].x = shortest_distance_x;
        deminers[whose_turn].y = shortest_distance_y;

        if (whose_turn < amount_of_deminers - 1) {
            whose_turn++;
        } else {
            whose_turn = 0;
        }

        print_map(mapSize, map, deminers, amount_of_deminers);
        get_cell(map, mapSize, shortest_distance_y, shortest_distance_x)->point_value = EXPLOSIVE_ENUM;
        char choice;
        scanf(" %c", &choice);
    }
    for (int i = 0; i < amount_of_deminers; i++) {
        deminers[i].x = -1;
        deminers[i].y = -1;
    }
    print_map(mapSize, map, deminers, amount_of_deminers);

}

int find_shortest_path_distance_sorter(const void *ep1, const void *ep2) {
    return (int*) ep1 - (int*) ep2;
}