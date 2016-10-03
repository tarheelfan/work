#include "heap.h"
struct list{
    int directions[1000];
    int size;
};
typedef struct{
     struct list directions;
     int thePlayer;
     int bigPeople;
     int dragon;
     int other;
     unsigned int characteristics : 4; /*Intel,Telapath,Tunneling,Erratic*/
     int alive;
     int xloc;
     int yloc;
     int modelNumber;
     unsigned int roundVal;
     int speed;
     int patrolMode;
     int searchLocationX;
     int searchLocationY;
     int (* moveUp)();
     int (* moveDown)();
     int (* moveRight)();
     int (* moveLeft)();
     int (* moveTopRight)();
     int (* moveTopLeft)();
     int (* moveBottomLeft)();
     int (* moveBottomRight)();
     int (* isIntelegent)();
     int (* isTelapathic)();
     int (* canTunnle)();
     int (* isErratic)();
     void (* performAction)();
     void (* scanArea)();
     void (* deconstructor)();
}Monster;
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
    
}Map;
typedef struct corridor_path corridor_path_t;
int initMap(int numOfMonster);
void printGrid(void);
int saveGame(void);
int loadGame(void);
void printDistanceGrid(void);
void printDistanceGridPlus();
void playGame();

void initMonsterLib(Map *map, int numOfMax);
Monster MonsterInit(Map *map,int x,int y,int isPlayer);
Monster getMonster(int y,int x);
 int moveUp(Monster *mon);
 int moveDown(Monster *mon);
 int moveRight(Monster *mon);
 int moveLeft(Monster *mon);
 int moveTopRight(Monster *mon);
 int moveTopLeft(Monster *mon);
 int moveBottomLeft(Monster *mon);
 int moveBottomRight(Monster *mon);
 int isIntelegent(Monster *mon);
 int isTelapathic(Monster *mon);
 int canTunnle(Monster *mon);
 int isErratic(Monster *mon);
int hasMonster(int xl, int yl);
void deconstructor(Monster *m);
void performAction(Monster *mon);
void scanArea(Monster *mon);
int getPCX();
int getPCY();
int32_t compare_monster(const void *key,const void *with);
Monster getMonster(int y,int x);
