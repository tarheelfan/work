#include "monster.h"
#include "mapInit.h"
#include <time.h>
#include <stdlib.h>

#define Intelligent 0x00000001


/*Public Class Monster */
struct Monster{
     int thePlayer=0;
     int bigPeople=0;
     int dragon=0;
     int other=0;
     unsigned int characteristics : 1; /*Intel,Telapath,Tunneling,Erratic*/
     int alive;
     int xloc;
     int yloc;
     int modelNumber;
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
}
/*Fields for Library*/
static int maxMonsters;
static Map *m;
static Monster* monsterArray[21][80] = {NULL};
static int numOfMonsters;

/*Library Static Funcitons*/
void initMonsterLib(Map *map, int numOfMax){
    srand(time(NULL));
    maxMonsters = numOfMax;
    m=map;
}
/*Constructor*/
Monster MonsterInit(Map *map,int x,int y,int isPlayer){
    

    Monster *monster;
    monster = malloc(sizeof(Monster));
   if(isPlayer){
        monster->thePlayer=1;   
        monster->speed=10;
    }else{
    monster->patrolMode=1;
    monster->alive=1;
    monster->characteristics = rand()%16;
    int typeSwitch = rand()%3;
    monster->characteristics = rand();
    monster->moveUp=moveUp;
    monster->moveDown=moveDown;
    monster->moveRight =moveRight;
    monster->moveLeft = moveLeft;
    monster->moveTopRight = moveTopRight;
    monster->moveTopLeft = moveTopLeft;
    monster->moveBottomLeft = moveBottomLeft;
    monster->moveBottomRight = moveBottomRight;
    monster->modelNumber=numOfMonsters;
    monster->isIntelegent = isIntelegent;
    monster->isTelapathic = isTelapathic;
    monster->canTunnle = canTunnle;
    monster->isErratic = isErratic;
    monster->performAction=performAction;
    monster->deconstructor = deconstructor;
    monster->scanArea=scanArea;
    monster->yloc=y;
    monster->searchLocationY=y;
    monster->searchLocationX=x;
    monster->xloc=x;
    if(!isPlayer){
        int spee = rand()%21;
    if(spee<5){
        spee=spee+5;
    }
    monster->speed= spee;
    }
    
    numOfMonsters++;
    }
}
/*Deconstructor*/
void deconstructor(Monster *m){
    free(m);
}
/*Public Functions For Monsters*/

 int moveUp(Monster *mon){
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp-1][xtemp] = mon;
    (*mon).yloc=ytemp-1;
    return 0;
}
 int moveDown(Monster *mon){
    int ytemp = (*mon).yloc;
    if(ytemp==19){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp+1][xtemp] = mon;
    (*mon).yloc=ytemp+1;
    return 0;
}
 int moveRight(Monster *mon){
    int ytemp = (*mon).yloc;
    int xtemp = (*mon).xloc;
    if(xtemp==78){
        return 1;
    }
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp][xtemp+1] = mon;
    (*mon).xloc=xtemp+1;
    return 0;
}
 int moveLeft(Monster *mon){
    int ytemp = (*mon).yloc;
    int xtemp = (*mon).xloc;
    if(xtemp==1){
        return 1;
    }
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp][xtemp-1] = mon;
    (*mon).xloc=xtemp-1;
    return 0;
}
 int moveTopRight(Monster *mon){
    int ytemp = (*mon).yloc;
    int xtemp = (*mon).xloc;
    if(xtemp==78){
        return 1;
    }
    if(ytemp==1){
        return 1;
    }
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp-1][xtemp+1] = mon;
    (*mon).xloc=xtemp+1;
    (*mon).yloc=ytemp-1;
    return 0;
}
 int moveTopLeft(Monster *mon){
    int ytemp = (*mon).yloc;
    int xtemp = (*mon).xloc;
    if(xtemp==1){
        return 1;
    }
    if(ytemp==1){
        return 1;
    }
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp-1][xtemp-1] = mon;
    (*mon).xloc=xtemp-1;
    (*mon).yloc=ytemp-1;
    return 0;
}
 int moveBottomLeft(Monster *mon){
    int ytemp = (*mon).yloc;
    int xtemp = (*mon).xloc;
    if(xtemp==1){
        return 1;
    }
    if(ytemp==19){
        return 1;
    }
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp+1][xtemp-1] = mon;
    (*mon).xloc=xtemp-1;
    (*mon).yloc=ytemp+1;
    return 0;
}
 int moveBottomRight(Monster *mon){
    int ytemp = (*mon).yloc;
    int xtemp = (*mon).xloc;
    if(xtemp==78){
        return 1;
    }
    if(ytemp==19){
        return 1;
    }
    monsterArray[ytemp][xtemp]=NULL;
    monsterArray[ytemp+1][xtemp+1] = mon;
    (*mon).xloc=xtemp+1;
    (*mon).yloc=ytemp+1;
    return 0;
}
 int isIntelegent(Monster *mon){
    int unsigned temp = mon->characteristics;
    return 1 & temp

}
 int isTelapathic(Monster *mon){
    int unsigned temp = mon->characteristics;
    return (2 & temp);
}
 int canTunnle(Monster *mon){
    int unsigned temp = mon->characteristics;
    return 4 & temp;
}
 int isErratic(Monster *mon){
    int unsigned temp = mon->characteristics;
    return (8 & temp);
}
 
void performAction(Monster *mon){
    scanArea(mon);
    if(mon->thePlayer){
        int control = rand();%8;
        switch(control){

            

        }
    }
    
    if(mon->patrolMode){

    }
    
}
void scanArea(Monster *mon){
    int xhere = mon->xloc;
    int yhere = mon->yloc;
    
    /*Monster Looks Forward*/
    int done=0;
    int ytemp = yhere;
    while(!done){
        ytemp++;
        if(m->grid[ytemp][xhere])==('.'||'#'){
            if(hasMonster(ytemp,xhere)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    done=1;
                    mon->searchLocationY=ytemp;
                }
            }
        }else{
            done=1;
        }
    }
    /*Monster Looks Behind*/
    done=0;
    ytemp = yhere;
    while(!done){
        ytemp--;
        if(m->grid[ytemp][xhere])==('.'||'#'){
            if(hasMonster(ytemp,xhere)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    done=1;
                    mon->patrolMode=0;
                    mon->searchLocationY=ytemp;
                }
            }
        }else{
            done=1;
        }
    }
    /*Monster Looks Right*/
    done=0;
    int xtemp = xhere;
    while(!done){
        xtemp++;
        if(m->grid[ytemp][xhere])==('.'||'#'){
            if(hasMonster(ytemp,xhere)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    mon->patrolMode=0;
                    done=1;
                    mon->searchLocationY=xtemp;
                }
            }
        }else{
            done=1;
        }
    }
    /*Monster Looks Left*/
    done=0;
    xtemp = xhere;
    while(!done){
        xtemp--;
        if(m->grid[ytemp][xhere])==('.'||'#'){
            if(hasMonster(ytemp,xhere)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    mon->patrolMode=0;
                    done=1;
                    mon->searchLocationY=xtemp;
                }
            }
        }else{
            done=1;
        }
    }
    /*Check Angles*/
    /*Top Left Angle*/
    short angle;
    done=0;
    for(angle=.5;angle<90;angle=angle+.1){
        short error = -1;
        int y = yhere;
        int x =xhere;
        while(!done){
            x++

            if(m->grid[y][x])==('.'||'#'){
            if(hasMonster(y,x)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    done=1;
                    mon->patrolMode=0;
                    mon->searchLocationY=y;
                    mon->searchLocationX=x;
                }
            }
        }else{
            done=1;
        }
         error = error + angle;
        if(error>0.0){
            y=y+1;
            error=error-1;
        }
        }
        
    }
     for(angle=.5;angle<90;angle=angle+.1){
        while(!done){
            x--

            if(m->grid[y][x])==('.'||'#'){
            if(hasMonster(y,x)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    done=1;
                    mon->patrolMode=0;796f752e6167652b2b3b	
                    mon->searchLocationY=y;
                    mon->searchLocationX=x;
                }
            }
        }else{
            done=1;
        }
         error = error + angle;
        if(error>0.0){
            y=y+1;
            error=error-1;
        }
        }
        
    }
     for(angle=.5;angle<90;angle=angle+.1){
        short error = -1;
        int y = yhere;
        int x =xhere;
        while(!done){
            x--;

            if(m->grid[y][x])==('.'||'#'){
            if(hasMonster(y,x)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    done=1;
                    mon->patrolMode=0;
                    mon->searchLocationY=y;
                    mon->searchLocationX=x;
                }
            }
        }else{
            done=1;
        }
         error = error + angle;
        if(error>0.0){
            y=y-1;
            error=error-1;
        }
        }
        
    }
    for(angle=.5;angle<90;angle=angle+.1){
        short error = -1;
        int y = yhere;
        int x =xhere;
        while(!done){
            x++;

            if(m->grid[y][x])==('.'||'#'){
            if(hasMonster(y,x)){
                Monster temp = getMonster(ytemp,xhere);
                if(temp.thePlayer){
                    done=1;
                    mon->patrolMode=0;
                    mon->searchLocationY=y;
                    mon->searchLocationX=x;
                }
            }
        }else{
            done=1;
        }
         error = error + angle;
        if(error>0.0){
            y=y-1;
            error=error-1;
        }
        }
        
    }            
}

/*Functions for Library*/
int hasMonster(int yl, int xl){
    if(yl>21 || 0>yl){
        return 0;
    }
    if(xl>80 || 0>xl){
        return 0;
    }
    if(!monsterArray[yl][xl]){
        return 0;
    }
    return 1;
}
Monster getMonster(yl,xl){
    return monsterArray[yl][xl];
}
