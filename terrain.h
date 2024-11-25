
#define TERRAIN_COUNT 5


typedef struct Point_s {
    int x;
    int y;
    int PointID;
} Point;

typedef struct Area_s {
    int x;
    int y;
    int AreaID;
} Area;


Area terrain_coordinate(int y, int x, int id);
Area terrain_radius(int terrain_count, Area* terrain);


