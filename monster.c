#include "monster.h"
#include "mapInit.h"
#include <time.h>
#include <stdlib.h>

#define Intelligent 0x00000001
static void performWander(Monster *npc);
static void moveNearestNonTunneling(Monster *npc);
void initList(struct list);
void addToList(struct list,int num);
int removeFromList(struct list);
static void getDirections(Monster *npc);
void reset(struct list);
static void getDirectionsTunneling(Monster *npc)
/*Public Class Monster */
struct list{
    int directions[1000];
    int size;
}
void initList(struct list){
    list.size=0;
}
void addToList(struct list,int num){
    list.directions[list.size]=num;
    list.size++;
}
int removeFromList(struct list){
    int num = list.directions[list.size];
    list.size--;
    return num;
}
void reset(struct list){
    list.size=0;
} 

struct Monster{
     struct list;
     int thePlayer;
     int bigPeople;
     int dragon;
     int other;
     unsigned int characteristics : 4; /*Intel,Telapath,Tunneling,Erratic*/
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
    initList(monster->list);
    monster->thePlayer=0;
    monster->bigPeople=0;
    monster->dragon=0;
    monster->other=0;
    monster->patrolMode=1;
    monster->alive=1;
    monster->characteristics = rand()%16;
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
    int typeSwitch = rand()%3;
    switch(typeSwitch){
        case 0:
            monster->bigPeople=1;
            break;
        case 1:
            monster->dragon=1;
            break;
        case 2:
            monster->other=1;
            break;
    }
    
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

 int moveUp(Monster *mon){/*y-1,x*/
    Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp-1][xtemp];
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp-1][xtemp]==('#'||'.')){
       monsterArray[ytemp-1][xtemp] = mon;
       (*mon).yloc=ytemp-1; 
    }else{
        unsigned char hardness =m->hardness[ytemp-1][xtemp];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp-1][xtemp]=hardness;
        if(hardness==0){
            monsterArray[ytemp-1][xtemp] = mon;
            (*mon).yloc=ytemp-1;
            m->grid[ytemp-1][xtemp]='#'; 
        }
    }
    
    return 0;
}
 int moveDown(Monster *mon){/*y+1,x*/
    Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp+1][xtemp];/*y+1,x*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp+1][xtemp]==('#'||'.')){/*y+1,x*/
       monsterArray[ytemp+1][xtemp] = mon;/*y+1,x*/
       (*mon).yloc=ytemp+1; /*y+1,x*/
    }else{
        unsigned char hardness =m->hardness[ytemp+1][xtemp];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp+1][xtemp]=hardness;/*y+1,x*/
        if(hardness==0){
            monsterArray[ytemp+1][xtemp] = mon;/*y+1,x*/
            (*mon).yloc=ytemp+1;/*y+1,x*/
            m->grid[ytemp+1][xtemp]='#'; /*y+1,x*/
        }
    }
    
    return 0;
}
 int moveRight(Monster *mon){/*y,x+1*/
    Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    temp = monsterArray[ytemp][xtemp+1];/*y,x+1*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp][xtemp+1]==('#'||'.')){/*y,x+1*/
       monsterArray[ytemp][xtemp+1] = mon;/*y,x+1*/
       (*mon).xloc=xtemp+1; /*y,x+1*/
    }else{
        unsigned char hardness =m->hardness[ytemp][xtemp+1];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp][xtemp+1]=hardness;/*y,x+1*/
        if(hardness==0){
            monsterArray[ytemp][xtemp+1] = mon;/*y,x+1*/
            (*mon).xloc=xtemp+1;/*y,x+1*/
            m->grid[ytemp][xtemp+1]='#'; /*y,x+1*/
        }
    }
    
    return 0;
}
 int moveLeft(Monster *mon){/*y,x-1*/
    Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp][xtemp-1];/*y,x-1*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp][xtemp-1]==('#'||'.')){/*y,x-1*/
       monsterArray[ytemp][xtemp-1] = mon;/*y,x-1*/
       (*mon).xloc=xtemp-1; /*y,x-1*/
    }else{
        unsigned char hardness =m->hardness[ytemp][xtemp-1];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp][xtemp-1]=hardness;/*y,x-1*/
        if(hardness==0){
            monsterArray[ytemp][xtemp-1] = mon;/*y,x-1*/
            (*mon).xloc=xtemp-1;/*y,x-1*/
            m->grid[ytemp][xtemp-1]='#'; /*y,x-1*/
        }
    }
    
    return 0;
}
 int moveTopRight(Monster *mon){/*y-1,x+1*/
    Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp-1][xtemp+1];/*y-1,x+1*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp-1][xtemp+1]==('#'||'.')){/*y-1,x+1*/
       monsterArray[ytemp-1][xtemp+1] = mon;/*y-1,x+1*/
       (*mon).yloc=ytemp-1;/*y-1,x+1*/
        (*mon).xloc=xtemp+1;
    }else{
        unsigned char hardness =m->hardness[ytemp-1][xtemp+1];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp-1][xtemp+1]=hardness;/*y-1,x+1*/
        if(hardness==0){
            monsterArray[ytemp-1][xtemp+1] = mon;/*y-1,x+1*/
            (*mon).yloc=ytemp-1;/*y-1,x+1*/
            (*mon).xloc=xtemp+1
            m->grid[ytemp-1][xtemp+1]='#'; /*y-1,x+1*/
        }
    }
    
    return 0;
}
 int moveTopLeft(Monster *mon){/*y-1,x-1*/
        Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp-1][xtemp-1];/*y-1,x-1*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp-1][xtemp-1]==('#'||'.')){/*y-1,x-1*/
       monsterArray[ytemp-1][xtemp-1] = mon;/*y-1,x-1*/
       (*mon).yloc=ytemp-1;/*y-1,x-1*/
        (*mon).xloc=xtemp-1;
    }else{
        unsigned char hardness =m->hardness[ytemp-1][xtemp-1];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp-1][xtemp-1]=hardness;/*y-1,x-1*/
        if(hardness==0){
            monsterArray[ytemp-1][xtemp-1] = mon;/*y-1,x-1*/
            (*mon).yloc=ytemp-1;/*y-1,x-1*/
            (*mon).xloc=xtemp-1
            m->grid[ytemp-1][xtemp-1]='#'; /*y-1,x-1*/
        }
    }
    
    return 0;
}
 int moveBottomLeft(Monster *mon){/*y+1,x-1*/
        Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp+1][xtemp-1];/*y+1,x-1*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp+1][xtemp-1]==('#'||'.')){/*y+1,x-1*/
       monsterArray[ytemp+1][xtemp-1] = mon;/*y+1,x-1*/
       (*mon).yloc=ytemp+1;/*y+1,x-1*/
        (*mon).xloc=xtemp-1;
    }else{
        unsigned char hardness =m->hardness[ytemp+1][xtemp-1];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp+1][xtemp-1]=hardness;/*y+1,x-1*/
        if(hardness==0){
            monsterArray[ytemp+1][xtemp-1] = mon;/*y+1,x-1*/
            (*mon).yloc=ytemp+1;/*y+1,x-1*/
            (*mon).xloc=xtemp-1
            m->grid[ytemp+1][xtemp-1]='#'; /*y+1,x-1*/
        }
    }
    
    return 0;
}
 int moveBottomRight(Monster *mon){/*y+1,x+1*/
        Monster *temp;
    int ytemp = (*mon).yloc;
    if(ytemp==1){
        return 1;
    }
    int xtemp = (*mon).xloc;
    monsterArray[ytemp][xtemp]=NULL;/*y,x*/
    
    
    temp = monsterArray[ytemp+1][xtemp+1];/*y+1,x+1*/
    if(temp!=NULL){
        temp.alive=0;
    }
    if(m->grid[ytemp+1][xtemp+1]==('#'||'.')){/*y+1,x+1*/
       monsterArray[ytemp+1][xtemp+1] = mon;/*y+1,x+1*/
       (*mon).yloc=ytemp+1;/*y+1,x+1*/
        (*mon).xloc=xtemp+1;
    }else{
        unsigned char hardness =m->hardness[ytemp+1][xtemp+1];
        if(hardness>85){
            hardness=hardness-85;
        }else{
            hardness=0;
        }
        m->hardness[ytemp+1][xtemp+1]=hardness;/*y+1,x+1*/
        if(hardness==0){
            monsterArray[ytemp+1][xtemp+1] = mon;/*y+1,x+1*/
            (*mon).yloc=ytemp+1;/*y+1,x+1*/
            (*mon).xloc=xtemp+1
            m->grid[ytemp+1][xtemp+1]='#'; /*y+1,x+1*/
        }
    }
    
    return 0;
}
 int isIntelegent(Monster *mon){
    int unsigned temp = mon->characteristics;
    return 1 & temp

}
 int isTelapathic(Monster *mon){
    int unsigned temp = mon->characteristics;static void performWander(Monster *npc)
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
    if(mon->thePlayer){
        performWander(mon);
        return;
    }else{
        scanArea(mon);
        int twoFacesCoin = rand()%2;
        if(isErratic(mon) && twoFacesCoin){
            performWander(mon);
            return;
        }else{

        }

}
/*Helper Functions For Monsters */
static void getDirectionsTunneling(Monster *npc){
    int min = 1000;
    int xhere = npc->xloc;
    int yhere = npc->yloc;
    int xtogo;
    int ytogo;
    int topLeft=0;
    int top=0;
    int topRight=0;
    int left=0;
    int right =0;
    int bottomLeft =0;
    int bottom =0;
    int bottomRight=0;
    /*Top Left*/
    if(xhere-1!=0 && yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=1;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Top*/
    if(yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=0;
                 top=1;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*TopRight*/
    if(xhere+1!=79 && yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=1;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Left*/
    if(xhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=1;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }   
    }
    /*Right*/
    if(xhere+1!=79){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =1;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*BottomLeft*/
    if(xhere-1!=0 && yhere+1!=20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =1;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Bottom*/
    if(yhere+1!=79){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =1;
                 bottomRight=0;
            }
    }
    /*BottomRight*/
    if(xhere+1!=79 && yhere+1!=20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=1;
            }
    }
    if(top){
        addToList(npc->list,2);
    }
    if(TopLeft){
        addToList(npc->list,1);
    }
    if(TopRight){
        addToList(npc->list,3);
    }
    if(left){
        addToList(npc->list,4);
    }
    if(right){
        addToList(npc->list,5);
    }
    if(bottomLeft){
        addToList(npc->list,6);
    }
    if(bottomRight){
        addToList(npc->list,8);
    }
    if(bottom){
        addToList(npc->list,7);
    }
}
static void getDirections(Monster *npc){/*Hey Shane please work here on this function and check for correct dimensions and terrain*/
    int min = 1000;
    int xhere = npc->xloc;
    int yhere = npc->yloc;
    int xtogo;
    int ytogo;
    int topLeft=0;
    int top=0;
    int topRight=0;
    int left=0;
    int right =0;
    int bottomLeft =0;
    int bottom =0;
    int bottomRight=0;
    /*Top Left*/
    if(xhere-1!=0 && yhere-1!=0 && xtemp<79 && xtemp>0 && ytemp>0 && ytemp<20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=1;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Top*/
    if(yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=0;
                 top=1;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*TopRight*/
    if(xhere+1!=79 && yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=1;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Left*/
    if(xhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=1;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }   
    }
    /*Right*/
    if(xhere+1!=79){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =1;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*BottomLeft*/
    if(xhere-1!=0 && yhere+1!=20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =1;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Bottom*/
    if(yhere+1!=79){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =1;
                 bottomRight=0;
            }
    }
    /*BottomRight*/
    if(xhere+1!=79 && yhere+1!=20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=1;
            }
    }
    if(top){
        addToList(npc->list,2);
    }
    if(TopLeft){
        addToList(npc->list,1);
    }
    if(TopRight){
        addToList(npc->list,3);
    }
    if(left){
        addToList(npc->list,4);
    }
    if(right){
        addToList(npc->list,5);
    }
    if(bottomLeft){
        addToList(npc->list,6);
    }
    if(bottomRight){
        addToList(npc->list,8);
    }
    if(bottom){
        addToList(npc->list,7);
    }
}
/*
    [1][2][3]
    [4][0][5]
    [6][7][8]  

*/


static void performWander(Monster *npc){
    int done = 0;
    while(!done){
        int control = rand();%8;
        switch(control){
            case 0:/*Move Up*/
            if(m->grid[mon->yloc-1][mon->xloc]==('#'||'.')){
                if(!moveUp(mon)){
                    done=1;
                }
            }
            break;
            case 1:/*Move Down*/
            if(m->grid[mon->yloc+1][mon->xloc]==('#'||'.')){
                if(!moveDown(mon)){
                    done=1;
                }
            }
            break;
            case 2:/*Move Right*/
            if(m->grid[mon->yloc][mon->xloc+1]==('#'||'.')){
                if(!moveRight(mon)){
                    done=1;
                }
            }
            break;
            case 3:/*Move Left*/
             if(m->grid[mon->yloc][mon->xloc-1]==('#'||'.')){
                if(!moveLeft(mon)){
                    done=1;
                }
            }
            break;
            case 4:/*Move TopRight*/
            if(m->grid[mon->yloc-1][mon->xloc+1]==('#'||'.')){
                if(!moveTopRight(mon)){
                    done=1;
                }
            }
            break;
            case 5:/*Move TopLeft*/
            if(m->grid[mon->yloc-1][mon->xloc-1]==('#'||'.')){
                if(!moveTopLeft(mon)){
                    done=1;
                }
            }
            break;
            case 6:/*Move BottomRight*/
             if(m->grid[mon->yloc1+1][mon->xloc+1]==('#'||'.')){
                if(!moveBottomRight(mon)){
                    done=1;
                }
            }
            break;
            case 7:/*Move BottomLeft*/
             if(m->grid[mon->yloc+1][mon->xloc-1]==('#'||'.')){
                if(!moveBottomLeft(mon)){
                    done=1;
                }
            }
        }
    }
}
static void moveNearestNonTunneling(Monster *npc){
    int min = 1000;
    int xhere = npc->xloc;
    int yhere = npc->yloc;
    int xtogo;
    int ytogo;
    

    int topLeft=0;
    int top=0;
    int topRight=0;
    int left=0;
    int right =0;
    int bottomLeft =0;
    int bottom =0;
    int bottomRight=0;
    /*Top Left*/
    if(xhere-1!=0 && yhere-1!=0){
        if(m->grid[yhere-1][xhere-1]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=1;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
        }
    }
    /*Top*/
    if(yhere-1!=0){
        if(m->grid[yhere-1][xhere]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=0;
                 top=1;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
        }
    }
    /*TopRight*/
    if(xhere+1!=79 && yhere-1!=0){
        if(m->grid[yhere-1][xhere+1]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=1;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
        }
    }
    /*Left*/
    if(xhere-1!=0){
        if(m->grid[yhere][xhere-1]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=1;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
        }
    }
    /*Right*/
    if(xhere+1!=79){
        if(m->grid[yhere-1][xhere+1]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =1;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
        }
    }
    /*BottomLeft*/
    if(xhere-1!=0 && yhere+1!=20){
        if(m->grid[yhere+1][xhere-1]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =1;
                 bottom =0;
                 bottomRight=0;
            }
        }
    }
    /*Bottom*/
    if(yhere+1!=79){
        if(m->grid[yhere+1][xhere]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =1;
                 bottomRight=0;
            }
        }
    }
    /*BottomRight*/
    if(xhere!=0 && yhere+1!=0){
        if(m->grid[yhere+1][xhere]==('#'||'.')){
            int temp = m->distanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=1;
            }
        }
    }
    if(top){
        moveUp(npc);
    }
    if(TopLeft){
        moveTopLeft(npc);
    }
    if(TopRight){
        moveTopRight(npc);
    }
    if(left){
        moveLeft(npc);
    }
    if(right){
        moveRight(npc);
    }
    if(bottomLeft){
        moveBottomLeft(npc);
    }
    if(bottomRight){
        moveBottomRight(npc);
    }
    if(bottom){
        moveDown(npc);
    }
}
static void moveNearestTunneling(Monster *npc){
    int min = 1000;
    int xhere = npc->xloc;
    int yhere = npc->yloc;
    int xtogo;
    int ytogo;
    int topLeft=0;
    int top=0;
    int topRight=0;
    int left=0;
    int right =0;
    int bottomLeft =0;
    int bottom =0;
    int bottomRight=0;
    /*Top Left*/
    if(xhere-1!=0 && yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=1;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Top*/
    if(yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                 topLeft=0;
                 top=1;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*TopRight*/
    if(xhere+1!=79 && yhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=1;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Left*/
    if(xhere-1!=0){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=1;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }   
    }
    /*Right*/
    if(xhere+1!=79){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =1;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*BottomLeft*/
    if(xhere-1!=0 && yhere+1!=20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =1;
                 bottom =0;
                 bottomRight=0;
            }
    }
    /*Bottom*/
    if(yhere+1!=79){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =1;
                 bottomRight=0;
            }
    }
    /*BottomRight*/
    if(xhere+1!=79 && yhere+1!=20){
            int temp = m->didistanceGrid.distance;
            if(temp<min){
                min=temp;
                topLeft=0;
                 top=0;
                 topRight=0;
                 left=0;
                 right =0;
                 bottomLeft =0;
                 bottom =0;
                 bottomRight=1;
            }
    }
    if(top){
        moveUp(npc);
    }
    if(TopLeft){
        moveTopLeft(npc);
    }
    if(TopRight){
        moveTopRight(npc);
    }
    if(left){
        moveLeft(npc);
    }
    if(right){
        moveRight(npc);
    }
    if(bottomLeft){
        moveBottomLeft(npc);
    }
    if(bottomRight){
        moveBottomRight(npc);
    }
    if(bottom){
        moveDown(npc);
    }
}
/*********************************/
void scanArea(Monster *mon){
    int xhere = mon->xloc;
    int yhere = mon->yloc;
    
    /*Monster Looks Forward*/
    int done=0;
    int ytemp = yhere;
    while(!done){
        ytemp++;
        if(m->grid[ytemp][xhere])==(('.'||'#') && ytemp>0){
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
        if(m->grid[ytemp][xhere])==(('.'||'#') && ytemp<20){
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
        if(m->grid[ytemp][xhere])==(('.'||'#') && xtemp<79){
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
        if(m->grid[ytemp][xhere])==(('.'||'#') && xtemp>0){
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
    short angle;
    done=0;
    for(angle=.5;angle<90;angle=angle+.1){
        short error = -1;
        int y = yhere;
        int x =xhere;
        while(!done){
            x++

            if(m->grid[y][x])==(('.'||'#') && xtemp<79 && xtemp>0 && ytemp>0 && ytemp<20){
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

            if(m->grid[y][x])==(('.'||'#') && xtemp<79 && xtemp>0 && ytemp>0 && ytemp<20){
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

            if(m->grid[y][x])==(('.'||'#') && xtemp<79 && xtemp>0 && ytemp>0 && ytemp<20){
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

            if(m->grid[y][x])==(('.'||'#') && xtemp<79 && xtemp>0 && ytemp>0 && ytemp<20){
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
