#include "heap.h"
#include "monster.h"
typedef struct {
    int topLeft[2];
    int topright[2];
    int bottomLeft[2];
    int bottomRight[2];
}Room;

typedef struct{
    int distance;
    int xloc;
    int yloc;
}distanceCell;

typedef struct {
    char grid[21][80];
    distanceCell distanceGrid[30][100];
    unsigned char hardness[21][80];
    Room rooms[100];
    int numOfRooms;
    int pcX;
    int pcY;
    Monster* monsterArray[21][80]
}Map;
typedef struct corridor_path corridor_path_t;
int initMap(int numOfMonster);
void printGrid(void);
int saveGame(void);
int loadGame(void);
void printDistanceGrid(void);
void printDistanceGridPlus();
void playGame();