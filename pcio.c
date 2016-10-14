
#include <ncurses.h>
#include "gameMap.h"

#define ESCAPE 27

#define UP_LEFT (ch == 7 || ch == 'y') ? 1 : 0
#define UP (ch == 8 || ch == 'k') ? 1 : 0
#define UP_RIGHT (ch == 9 || ch == 'u') ? 1 : 0
#define RIGHT (ch == 6 || ch == 'l') ? 1 : 0
#define BOTTOM_RIGHT (ch == 3 || ch == 'n' ) ? 1 : 0
#define BOTTOM (ch == 2 || ch =='j') ? 1 : 0
#define BOTTOM_LEFT (ch == 1 || ch =='b') ? 1 : 0
#define LEFT (ch == 4 || ch == 'h') ? 1 : 0
#define UP_STAIRS (ch == '<') ? 1 : 0
#define DOWN_STAIRS (ch == '>') ? 1 : 0
#define REST (ch == 5 || ch == ' ') ? 1 : 0
#define LIST (ch == 'm') ? 1 : 0
#define SCROLL_UP (ch == KEY_UP) ? 1 : 0
#define SCROLL_DOWN (ch == KEY_DOWN) ? 1 : 0
#define RETURN_TO_MAP (ch == ESCAPE)
#define QUIT ( ch == 'Q') ? 1 : 0

static int upLeft(void);
static int up(void);
static int left(void);
static int bottomLeft(void);
static int bottom(void);
static int bottomRight(void);
static int right(void);
static int upRight(void);
static int upStairs(void);
static int downStairs(void);

/*Global Data*/
Monster* pc;
int ch; /*command*/
/*******************/
void ioInit(Monster *pcm){
    pc = pcm;
}

void performPCMove(void){    
    int done = 0;
    while(!done){
        ch = getch();
        switch(ch){
            case UP_LEFT :
                done=upLeft();
                break;
            case UP :
                done=up();
                break;
            case UP_RIGHT :
                done = upRight();
                break;
            case RIGHT :
                done = right();
                break;
            case BOTTOM_RIGHT :
                done = bottomRight();
                break;
            case BOTTOM:
                done = bottom();
                break;
            case BOTTOM_LEFT:
                done = bottomLeft();
                break;
            case LEFT :
                done = left();
                break;
            case UP_STAIRS :
                done = upStairs();
                break;
            case DOWN_STAIRS:
                done =downStairs();
                break;
            case REST:
                /*Do Nothing*/
                break;
            case LIST:
                 
        }
    }
}

static int upLeft(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y-1][x-1] == '#' || m->grid[y-1][x-1] == '.' ){
        return moveTopLeft(pc);
    }
}
static int up(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y-1][x] == '#' || m->grid[y-1][x] == '.' ){
       return moveUp(pc);
    }
}
static int upRight(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y-1][x+1] == '#' || m->grid[y-1][x+1] == '.' ){
        return moveTopRight(pc);         
    }
}
static int right(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y][x+1] == '#' || m->grid[y][x+1] == '.' ){
        return moveRight(pc);         
    }
}
static int bottomRight(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y+1][x+1] == '#' || m->grid[y+1][x+1] == '.' ){
        return moveBottomRight(pc);         
    }
}
static int bottom(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y+1][x] == '#' || m->grid[y+1][x] == '.' ){
        return moveDown(pc);         
    }
}
static int bottomLeft(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y+1][x-1] == '#' || m->grid[y+1][x-1] == '.' ){
        return moveBottomLeft(pc);         
    }
}
static int left(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y][x-1] == '#' || m->grid[y][x-1] == '.' ){
        return moveLeft(pc);         
    }
}
static int upStairs(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y][x-1] == '<' ){
        reInitMap(NUMBER_OF_MONSTERS);
        playGame();
        return 1;
    }
    return 0;
}
static int downStairs(void){
    int x = pc->xloc;
    int y = pc->yloc;
    if(m->grid[y][x-1] == '>' ){
        reInitMap(NUMBER_OF_MONSTERS);
        playGame();
        return 1;
    }
    return 0;
}
