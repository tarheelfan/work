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
     int xloc;
     int yloc;
     int modelNumber;
     int speed;
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
    monster->characteristics = rand()%17;
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
    monster->yloc=y;
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
/*Public Functions For Monsters*/

/*moveUp
    returns 1 if attempting to move to immutable area
    returns 0 is move is successful
*/
static int moveUp(Monster *mon){
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
static int moveDown(Monster *mon){
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
static int moveRight(Monster *mon){
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
static int moveLeft(Monster *mon){
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
static int moveTopRight(Monster *mon){
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
static int moveTopLeft(Monster *mon){
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
static int moveBottomLeft(Monster *mon){
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
static int moveBottomRight(Monster *mon){
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
/*Intel,Telapath,Tunneling,Erratic
monster->characteristics = rand()%17;
*/
 int isIntelegent(Monster *mon){
    int unsigned temp = mon->characteristics;
    return temp >>> 3;

}
 int isTelapathic(Monster *mon){
    int unsigned temp = mon->characteristics;
    return (1 << temp)>>>3;
}
 int canTunnle(Monster *mon){
    int unsigned temp = mon->characteristics;
    return (2 << temp) >>> 3;
}
 int isErratic(Monster *mon){
    int unsigned temp = mon->characteristics;
    return (3<< temp) >>>3;
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
