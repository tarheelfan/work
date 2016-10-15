
#include <ncurses.h>
#include "gameMap.h"

#define ESCAPE 27

#define UP_STAIRS '<'
#define DOWN_STAIRS '>'
#define LIST ch == 'm'
#define SCROLL_UP ch == KEY_UP
#define SCROLL_DOWN KEY_DOWN
#define QUIT 'Q'

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
static void clearData();
static void displayEnemyStatus(void);
/*Global Data*/
int ch; /*command*/
/*******************/


int performPCMove(void){    
    int done = 0;
    while(!done){
        ch = getch();
        switch(ch){
            case 7 :
            case 'y': /*Up Left*/
                done=upLeft();
                break;
            case 8 : /*Up*/
            case 'k':
                done=up();
                break;
            case 'u': /*Up Right*/
            case 9 :
                done = upRight();
                break;
            case 'l' : /*Right*/
            case 6 :
                done = right();
                break;
            case 'n':
            case 3 : /*Bottom Right*/
                done = bottomRight();
                break;
            case 'j':
            case 2: /*Bottom*/
                done = bottom();
                break;
            case 'b':
            case 1: /*Bottom Left*/
                done = bottomLeft();
                break;
            case 'h':
            case 4 : /*Left*/
                done = left();
                break;
            case UP_STAIRS :
                done = upStairs();
                break;
            case DOWN_STAIRS:
                done =downStairs();
                break;
            case 5 : /*Rest*/
            case ' ':
                /*Do Nothing*/
                break;
            case LIST:
                displayEnemyStatus();
                char userCommand = getch();
                if(userCommand == ESCAPE){
                    wrefresh(window);
                    clear();
                }
                break;
            case QUIT :
                return 1;
        }
    }
}

static int upLeft(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y-1][x-1] == '#' || m->grid[y-1][x-1] == '.' ){
        return moveTopLeft(pc);
    }
}
static int up(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y-1][x] == '#' || m->grid[y-1][x] == '.' ){
       return moveUp(pc);
    }
}
static int upRight(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y-1][x+1] == '#' || m->grid[y-1][x+1] == '.' ){
        return moveTopRight(pc);         
    }
}
static int right(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y][x+1] == '#' || m->grid[y][x+1] == '.' ){
        return moveRight(pc);        
    }
}
static int bottomRight(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y+1][x+1] == '#' || m->grid[y+1][x+1] == '.' ){
        return moveBottomRight(pc);         
    }
}
static int bottom(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y+1][x] == '#' || m->grid[y+1][x] == '.' ){
        return moveDown(pc);         
    }
}
static int bottomLeft(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y+1][x-1] == '#' || m->grid[y+1][x-1] == '.' ){
        return moveBottomLeft(pc);         
    }
}
static int left(void){
   int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y][x-1] == '#' || m->grid[y][x-1] == '.' ){
        return moveLeft(pc);         
    }
}
static int upStairs(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y][x-1] == '<' ){
        clearData();
        reInitMap(NUMBER_OF_MONSTERS);
        playGame();
        return 1;
    }
    return 0;
}
static int downStairs(void){
    int x = thePlayer->xloc;
    int y = thePlayer->yloc;
    if(m->grid[y][x-1] == '>' ){
        clearData();
        reInitMap(NUMBER_OF_MONSTERS);
        playGame();
        return 1;
    }
    return 0;
}
static void clearData(){
    while(!binheap_is_empty(&heap)){
        deconstructor(binheap_remove_min(&heap));
    }
    free(m);
}

static void displayEnemyStatus(void){
    wrefresh(window);
    WINDOW monsterStats = newwin(21,100,0,0);
    Monster* monsters[NUMBER_OF_MONSTERS];
    Monster *tem;
    int counter=0;
    while(tem = (Monster*)binheap_remove_min(&heap)){
        monsters[counter]=tem;
        counter++;
    }
    int cou;
    for(cou=0;cou<counter;cou++){
        Monster *mo; 
        mo = monsters[cou];
        binheap_insert(heap, mo);
        if(!mo->thePlayer){
        char string[19];
        char temp = 'p';
        if(mo->bigPeople){
            temp = 'P';
        }
        if(mo->dragon){
            temp ='D';
        }
        string[0] = temp;
        string[1] = ' ';
        
        int xtemppc = thePlayer->xloc;
        int ytemppc = thePlayer->yloc;
        
        int xtempmon = mo->xloc;
        int ytempmon = mo->yloc;
        if(xtemppc<xtempmon){
            string[2]='E';
            string[3]='A';
            string[4]='S';
            string[5]='T';
            string[6]=':';
            string[7]=xtempmon-xtemppc;
        }
        if(xtemppc>xtempmon){
            string[2]='W';
            string[3]='E';
            string[4]='S';
            string[5]='T';
            string[6]=':';
            string[7]=xtemppc-xtempmon;
        }
        if(xtemppc==xtempmon){
            string[2]=' ';
            string[3]=' ';
            string[4]=' ';
            string[5]=' ';
            string[6]=' ';
            string[7]=' ';
        }
        string[8]=' ';
        if(ytemppc<ytempmon){
            string[9]='N';
            string[10]='O';
            string[11]='R';
            string[12]='T';
            string[13]='H';
            string[14]=':';
            string[15] = ytempmon-ytemppc;
        }
        if(ytemppc>ytempmon){
            string[9]='S';
            string[10]='O';
            string[11]='U';
            string[12]='T';
            string[13]='H';
            string[14]=':';
            string[15] = ytemppc-ytempmon;
        }
        mvwprintw(monsterStats,counter,0,"P");
        }
    }
wrefresh(monsterStats);
}
