
#include <ncurses.h>
#include "gameMap.h"
#include <stdint.h>
#include <stdlib.h>
#define ESCAPE 27

#define UP_STAIRS '<'
#define DOWN_STAIRS '>'
#define SCROLL_UP KEY_UP
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
static WINDOW* displayEnemyStatus(void);
/*Global Data*/
int ch; /*command*/
Monster *pc;
WINDOW *temppoint;
/*******************/


int performPCMove(Monster *pci){    
    int done = 1;
    pc = pci;
    while(done){
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
            case '>' :
                done = upStairs();
                break;
            case '<':
                done =downStairs();
                break;
            case 5 : /*Rest*/
            case ' ':
                /*Do Nothing*/
                break;
            case 'm':
                temppoint = displayEnemyStatus();
                char userCommand = getch();
                if(userCommand == ESCAPE){
                    free(temppoint);
                    wrefresh(window);
                    //clear();
                }
                break;
            case QUIT :
                return 1;
        }
    }
    return 0;
}

static int upLeft(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y-1][x-1] == '#' || m->grid[y-1][x-1] == '.' || m->grid[y-1][x-1] == '<' || m->grid[y-1][x-1] == '>'){
        return moveTopLeft(pc);
    }
    return 1;
}
static int up(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y-1][x] == '#' || m->grid[y-1][x] == '.' || m->grid[y-1][x] == '<' || m->grid[y-1][x] == '>'){
       return moveUp(pc);
    }
    return 1;
}
static int upRight(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y-1][x+1] == '#' || m->grid[y-1][x+1] == '.' || m->grid[y-1][x+1] == '<' || m->grid[y-1][x+1] == '>'){
        return moveTopRight(pc);         
    }
    return 1;
}
static int right(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y][x+1] == '#' || m->grid[y][x+1] == '.' || m->grid[y][x+1] == '<' || m->grid[y][x+1] == '>'){
        return moveRight(pc);        
    }
    return 1;
}
static int bottomRight(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y+1][x+1] == '#' || m->grid[y+1][x+1] == '.' || m->grid[y+1][x+1] == '<' || m->grid[y+1][x+1] == '>'){
        return moveBottomRight(pc);         
    }
    return 1;
}
static int bottom(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y+1][x] == '#' || m->grid[y+1][x] == '.' || m->grid[y+1][x] == '<' || m->grid[y+1][x] == '>'){
        return moveDown(pc);         
    }
    return 1;
}
static int bottomLeft(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y+1][x-1] == '#' || m->grid[y+1][x-1] == '.' || m->grid[y+1][x-1] == '<' || m->grid[y+1][x-1] == '>'){
        return moveBottomLeft(pc);         
    }
    return 1;
}
static int left(void){
   int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y][x-1] == '#' || m->grid[y][x-1] == '.' || m->grid[y][x-1] == '<' || m->grid[y][x-1] == '>' ){
        return moveLeft(pc);         
    }
    return 1;
}
static int upStairs(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y][x] == '>' ){
        clearData();
        reInitMap(NUMBER_OF_MONSTERS);
        playGame();
        return 0;
    }
    return 1;
}
static int downStairs(void){
    int x = m->thePlayer->xloc;
    int y = m->thePlayer->yloc;
    if(m->grid[y][x] == '<' ){
        clearData();
        reInitMap(NUMBER_OF_MONSTERS);
        playGame();
        return 0;
    }
    return 1;
}
static void clearData(){
    while(!binheap_is_empty(&heap)){
        deconstructor(binheap_remove_min(&heap));
    }
    int x,y;for(x=0;x<21;x++){
        for(y=0;y<80;y++){
            m->distanceGrid[x][y].distance=0;
            m->grid[x][y]='\0';
            monsterArray[x][y]=NULL;        
        }
    }
    
    //free(m);
}

static WINDOW* displayEnemyStatus(void){
    wrefresh(window);
    WINDOW *monsterStats; 
    monsterStats = newwin(21,100,0,0);
    Monster* monsters[NUMBER_OF_MONSTERS];
    Monster *tem;
    int counter=0;
    tem = (Monster*)binheap_remove_min(&heap);
    while(tem){
        monsters[counter]=tem;
        counter++;
    }
    int cou;
    for(cou=0;cou<counter;cou++){
        Monster *mo; 
        mo = monsters[cou];
        binheap_insert(&heap, mo);
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
        
        int xtemppc = m->thePlayer->xloc;
        int ytemppc = m->thePlayer->yloc;
        
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
        mvwprintw(monsterStats,counter,0,string);
        }
    }
wrefresh(monsterStats);
return monsterStats;
}
