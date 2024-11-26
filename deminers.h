#define MINES 20
#define HILLS 5

#define PATH_SYMBOL '#'
#define BLANK_SYMBOL 'O'
#define OBSTACLE_SYMBOL 'X'
#define MINE_SYMBOL 'M'
#define HILL_SYMBOL 'B' //B FOR BAKKE
#define LESS_ELEVATION_SYMBOL 'L'

#define DEMINING_TIME 10 //assumption it takes 10 minutes to demine 1 mine
#define BLANK 1 //assumption it takes 1 minutes to walk across empty field
#define OBSTACLE 3 //assumption it takes 3 minutes to walk around field with obstacle

int get_deminers(char* map, int mapSize); //takes map size and amount of mines to calculate deminers needed
int is_mine(char* map, int mapSize, int y, int x); //checks boolean if cell is mine

void create_temproute(int mapSize, char** temp_route); //temp map to compare with

double cell_time(char* map, int mapSize, char* route, char* elevation_map, int y, int x); //checks time for each cell that is on the path
double total_time(char* map, int mapSize, char* route, char* elevation); //checks time of route

int deminer();