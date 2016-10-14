
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

/*
KEY_UP
KEY_DOWN
KEY_LEFT
KEY_RIGHT
*/

/*Global Data*/
Monster* pc;
int ch; /*command*/
/*******************/
void ioInit(Monster *pcm){
    pc = pcm;
}

void performPCMove(void){    
    
    ch = getch();

}
