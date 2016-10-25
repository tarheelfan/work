#include <cstring>
#include <cstdlib>
#include "mons.h"
#include "gameMap.h"


/*Library Variables*/
int numOfMonsters;

/*Functions to be called by C*/

void MonsterClass::initList(){
    this->directions.size=0;
}
MonsterClass::MonsterClass(int x, int y,int isPlayer){
    iMonster *monster;
    monster = (iMonster*)malloc(sizeof(iMonster));
    if(isPlayer){
        monster->thePlayer=1;    
        monster->speed=10;
        monster->roundVal=10;
        monster->xloc=x;
        monster->yloc=y;
        monster->alive=1;
    }else{
    initList();
    monster->monsterC =this;
    monster->thePlayer=0;
    monster->bigPeople=0;
    monster->dragon=0;
    monster->other=0;
    monster->patrolMode=1;
    monster->alive=1;
    monster->characteristics = rand()%16;
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
        int spee = (rand()%19)+1;
        spee = 100 / spee;

    if(spee<5){
        spee=spee+5;
    }
    monster->roundVal=spee;
    monster->speed= spee;
    }
    
    numOfMonsters++;
    }
this->monster = monster;
iMonster* array;
array = (iMonster)getMonArray();
array[monster->yloc][monster->xloc]= (Monster*)this->monster;

}
MonsterClass::~MonsterClass(){
    free(monster);
}


/*Private*/


void MonsterClass::addToList(int num){
    this->directions.directions[this->directions.size]=num;
    this->directions.size++;
}
void MonsterClass::reset(){
    this->directions.size=0;
}
int MonsterClass::removeFromList(){
    int num = this->directions.directions[0];
    int x;
    for(x=1;x<this->directions.size;x++){
        this->directions.directions[x-1]=this->directions.directions[x];
    }
    this->directions.size--;
    return num;
}


/*public*/
int moveUpI(void* s){ /*C function*/
    s = (MonsterClass)s;
    return s::moveUpC();
}
int MonsterClass::moveUpC(){ 
    return moveUp((Monster*)this->monster); 
}

int moveDownI(void* s){ /*C function*/
    s=(MonsterClass)s;
    return s::moveDownC();
}
int MonsterClass::moveDownC(){
    return moveDown((Monster*)this->monster);
}
int moveRightI(void* s){ /*C function*/
    s = (MonsterClass)s;
    return s::moveRightC();
}
int MonsterClass::moveRightC(){
    return moveRight((Monster*)this->monster);
}

int moveLeftI(void* s){ /*C function*/
    s = (MonsterClass)s;
    return s::moveLeftC();
}
int MonsterClass::moveLeftC(){
    return moveLeft((Monster*)this->monster);
}

int moveTopRightI(void* s){ /*C function*/
    s =(MonsterClass)s;
    return s::moveTopRightC();
}
int MonsterClass::moveTopRightC(){
    return moveTopRight((Monster*)this->monster);
}
int moveTopLeftI(void* s){ /*C function*/
    s =(MonsterClass)s;
    return moveTopLeftC();
}
int MonsterClass::moveTopLeftC(){
    return moveTopLeft((Monster*)this->monster);
}
int moveBottomLeftI(void* s){ /*C function*/
    s = (MonsterClass)s;
    return s::moveBottomLeftC();
}
int MonsterClass::moveBottomLeftC(){
    return moveBottomLeft((Monster*)this->monster);
}
int moveBottomRightI(void* s){ /*C function*/
    s =(MonsterClass)s;
    return s:moveBottomRightC();
}
int MonsterClass::moveBottomRightC(){
    return moveBottomRight((Monster*)this->monster);
}
int isIntelegentI(void* s){ /*C functions*/
    s = (MonsterClass)s;
    return s::isIntelegentC();
}
int MonsterClass::isIntelegentC(){
    int unsigned temp = this->characteristics;
    return 1 & temp;
}
int isTelapathicI(void* s){ /*C function*/
    s = (MonsterClass)s;
    return s::isTelapathicC();
}
int MonsterClass::isTelapathicC(){
    int unsigned temp = this->characteristics;
    return 2 & temp;
}
int canTunnleI(void* s){ /*C function*/
    s =(MonsterClass)s;
    return s::canTunnleC();
}
int MonsterClass::canTunnleC(){
    int unsigned temp = this->characteristics;
    return 4 & temp;
}
int isErraticI(void* s){ /*C function*/
    s = (MonsterClass)s;
    return s::isErraticC();
}
int MonsterClass::isErraticC(){
    int unsigned temp = this->characteristics;
    return 8 & temp;
}
void performActionI(void* s){ /*C function*/
    s =(MonsterClass)s;
    s::performActionC();
}
void MonsterClass::performActionC(){
    performAction((Monster*)this->monster);
}

void readDirectionsI(void* s){ /*C function*/
    s =(MonsterClass)s;
    s::readDirections();
}
void MonsterClass::readDirectionsC(){
    readDirections((Monster*)this->monster);
}
void getDirectionsTunnelingI(void* s){ /*C function*/
    s = (MonsterClass)s;
    s::getDirectionsTunnelingC();
}
void MonsterClass::getDirectionsTunnelingC(){
    getDirectionsTunneling((Monster*)this->monster);
}
void getDirectionsI(void* s){ /*C function*/
    s =(MonsterClass)s;
    s::getDirectionsC();
}
void MonsterClass::getDirectionsC(){
    getDirections((Monster*)this->monster);
}
void performWanderI(void* s){ /*C function*/
    s =(MonsterClass)s;
    s::performWanderC();
}
void MonsterClass::performWanderC(){
    performWander((Monster*)this->monster);
}
void moveNearestNonTunnelingI(void* s){ /*C function*/
    s = (MonsterClass)s;
    s::moveNearestNonTunnelingC();
}

void MonsterClass::moveNearestNonTunnelingC(){
    moveNearestNonTunneling((Monster*)this->monster);
}
void moveNearestTunneling(void* s){ /*C function*/
    s = (MonsterClass)s;
    s::moveNearestTunnelingC();
}
void MonsterClass::moveNearestTunnelingC(){
    moveNearestTunneling((Monster*)this->monster);
}
int scanAreaI(void* s){/*C function*/
    s = (MonsterClass)s;
    return s::scanAreaC();
}
int MonsterClass::scanAreaC(){
    return scanArea((Monster*)this->monster);
}
}
