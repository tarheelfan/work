#ifndef HEADER_H
#define HEADER_H


#ifdef __cplusplus
extern "C"{

#else

#endif

#include "normMonsS.h"
#include <ncurses.h>
#include "heap.h"

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
    distanceCell distanceGrid[21][80];
    distanceCell nonTunnelingDistanceGrid[21][80];
    unsigned char hardness[21][80];
    Monster *thePlayer;
    Room rooms[100];
    int numOfRooms;
    int pcX;
    int pcY;
}Map;
typedef struct corridor_path corridor_path_t;
int initMap(int numOfMonster);
void printGrid(void);
void printDistanceGrid(void);
void printDistanceGridPlus();
void playGame();
void initMonsterLib(Map *map, int numOfMax);
Monster* MonsterInit(Map *map,int x,int y,int isPlayer);
int moveUp(Monster *mon);
void moveNearestNonTunneling(Monster *npc);
void moveNearestTunneling(Monster *npc);
int moveDown(Monster *mon);
int moveRight(Monster *mon);
void getDirections(Monster *npc);
int moveLeft(Monster *mon);
void getDirectionsTunneling(Monster *npc);
int moveTopRight(Monster *mon);
void performWander(Monster *npc);
int moveTopLeft(Monster *mon);
int moveBottomLeft(Monster *mon);
int moveBottomRight(Monster *mon);
int isIntelegent(Monster *mon);
int isTelapathic(Monster *mon);
int canTunnle(Monster *mon);
void readDirections(Monster *mon);
void reInitMap(int num_of_mon);
int isErratic(Monster *mon);
int hasMonster(int xl, int yl);
void performAction(Monster *mon);
int scanArea(Monster *mon);
void deconstructor(Monster *mon);
int getPCX();
int getPCY();
int32_t compare_monster(const void *key,const void *with);
void analyzeDistances(void);
Room* pointContains(int y,int x);
int performPCMove(Monster *pci);
extern void* monsterArray[21][80];
extern Map *m;
extern int NUMBER_OF_MONSTERS;
//extern WINDOW *window;
extern binheap_t heap;
#ifdef __cpluspluc

}

#endif

#endif

