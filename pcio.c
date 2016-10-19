
#include <ncurses.h>
#include "gameMap.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UP_STAIRS '<'
#define DOWN_STAIRS '>'
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
static void displayEnemyStatus(int scale);
/*Global Data*/
char ch; /*command*/
Monster *pc;
WINDOW *temppoint;
/*******************/


int performPCMove(Monster *pci){    
    int scale=0;
    int done = 1;
    int escape=0;
    pc = pci;
    while(done){
        printGrid();
        wrefresh(window);
        ch = getch();
        switch(ch){
            
            case 7 : case 'y': /*Up Left*/
                done=upLeft();
                break;
             
           case 8 : case 'k': /*Up*/
                done=up();
                break;
            
            case 'u': case 9 :
                done = upRight(); /*Up Right*/
                break;
            case 'l' :  case 6 : /*Right*/
                done = right();
                break;
           case 'n': case 3 : /*Bottom Right*/
           done = bottomRight();
                break;
            case 'j': case 2: /*Bottom*/
                done = bottom();
                break;
           case 'b':  case 1: /*Bottom Left*/
                done = bottomLeft();
                break;
          case 'h':  case 4 : /*Left*/
                done = left();
                break;
            case '>' :
                done = upStairs();
                break;
            case '<':
                done =downStairs();
                break;
           // case 5 : /*Rest*/
           case ' ' : case '5' :
                /*Do Nothing*/
                done =0;
                break;
            case 'm':
                while(!escape){
                clear();
                refresh();
                displayEnemyStatus(scale);
                char userCommand = getch();
                if(userCommand==27){
                getch();
                userCommand = getch();
                escape=1;
                if(userCommand=='B'){ /*Down List*/
                    scale++;
                    escape=0;
                }
                if(userCommand=='A'){ /*Up Arrow*/
                    if(scale>-1){
                        scale--;
                        escape=0;
                    }
                }
                }
                }
                    clear();
                    printGrid();
                    wrefresh(window);
                break;
            case QUIT :
                return 1;
                break;
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
}

static void displayEnemyStatus(int scale){
    wrefresh(window);
    Monster* monsters[NUMBER_OF_MONSTERS];
    Monster *tem;
    int numOfMon = heap.size;
    int x;
    for(x=0;x<numOfMon;x++){
         tem = (Monster*)binheap_remove_min(&heap);
         monsters[x]=tem;
    }
    int ui;
    for(ui=0;ui<numOfMon;ui++){
        binheap_insert(&heap, monsters[ui]);
    }
    int cou;
    for(cou=0+scale;cou<numOfMon && cou<11+scale;cou++){
        Monster *mo; 
        mo = monsters[cou];
        if(mo){
        if(!mo->thePlayer){
        char string[8];
        char string2[6];
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
        int xval = xtempmon - xtemppc;
        if(xval<0){
            xval=xval*-1;
        } 
        int yval = ytempmon-ytemppc;
        if(yval<0){
            yval=yval*-1;
        }

        if(xtemppc<xtempmon){
            string[2]='E';
            string[3]='A';
            string[4]='S';
            string[5]='T';
            string[6]=':';
        }
        if(xtemppc>xtempmon){
            string[2]='W';
            string[3]='E';
            string[4]='S';
            string[5]='T';
            string[6]=':';
           
        
        }
        if(xtemppc==xtempmon){
            string[2]=' ';
            string[3]=' ';
            string[4]=' ';
            string[5]=' ';
            string[6]=' ';
            string[7]=' ';
            string[8]=' ';
        }
        string[7]=' ';
        if(ytemppc<ytempmon){
            string2[0]='N';
            string2[1]='O';
            string2[2]='R';
            string2[3]='T';
            string2[4]='H';
            string2[5]=':';
            
        
        }
        if(ytemppc>ytempmon){
            string2[0]='S';
            string2[1]='O';
            string2[2]='U';
            string2[3]='T';
            string2[4]='H';
            string2[5]=':';
            
           
        }
        printw("%s\n"," ");
        printw("%s",string);
        printw("%i",xval);
        printw("  %s",string2);
        printw("%i\n",yval);
        }
        }
    }
}

