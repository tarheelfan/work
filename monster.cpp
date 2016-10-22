#include <cstring>
#include <cstdlib>

/*Library Variables*/
int maxNumberofMonsters;
int pcx;
int pcy;
Monster* monsterArray[21][80] = {{NULL}};
/*Functions to be called by C*/
void initMonsterLib(int numMonsters){
    maxNumberofMonsters=numMonsters;
}
int getPCX(){
    return pcx;
}
int getPCY(){
    return pcy;
}

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

Monster::Monster(int x, int y,int isPlayer){
    Monster *monster;
    monster = malloc(sizeof(Monster));
    if(isPlayer){
        monster->thePlayer=1;   
        monster->speed=10;
        monster->roundVal=10;
        monster->xloc=x;
        monster->yloc=y;
        pcx = x;
        pcy = y;
        monster->alive=1;
    }else{
    initList();
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
monsterArray[monster->yloc][monster->xloc]=monster;
this.monster = monster;
}
Monster::~Monster(){
    free(monster);
}

Monster::moveUp(){

}

/*Private*/

void Monster::initList(){
    this.directions.size=0;
}
void Monster::addToList(int num){
    this.directions.directions[this.directions.size]=num;
    this.directions.size++;
}
void Monster::reset(){
    this.directions.size=0;
}
int Monster::removeFromList(){
    int num = this.directions.directions[0];
    int x;
    for(x=1;x<this.directions.size;x++){
        this.directions.directions[x-1]=this.directions.directions[x];
    }
    this.directions.size--;
    return num;
}


/*public*/

int Monster::moveUpC(){
    return moveUp(this.monster);
}
int Monster::moveDownC(){
    return moveDown(this.monster);
}
int Monster::moveRightC(){
    return moveRight(this.monster);
}
int Monster::moveLeftC(){
    return moveLeft(this.monster);
}
int Monster::moveTopRightC(){
    return moveTopright(this.monster);
}
int Monster::moveTopLeftC(){
    return moveTopLeft(this.monster);
}
int Monster::moveBottomLeftC(){
    return moveBottomLeft(this.monster);
}
int Monster::moveBottomRightC(){
    return moveBottomRight(this.monster);
}
int Monster::isIntelegent(){
    int unsigned temp = this.characteristics;
    return 1 & temp;
}
int Monster::isTelapathic(){
    int unsigned temp = this.characteristics;
    return 2 & temp;
}
int Monster::canTunnle(){
    int unsigned temp = this.characteristics;
    return 4 & temp;
}
int Monster::isErratic(){
    int unsigned temp = this.characteristics;
    return 8 & temp;
}
void Monster::performAction(){
    performAction(this.monster);
}
void Monster::readDirectionsC(){
    readDirections(this.monster);
}
void Monster::getDirectionsTunnelingC(){
    getDirectionsTunneling(this.monster);
}
void Monster::getDirectionsC(){
    getDirections(this.monster);
}
void Monster::performWanderC(){
    performWander(this.monster);
}
void Monster::moveNearestNonTunnelingC(){
    moveNearestNonTunneling(this.monster)
}
void Monster::moveNearestTunnelingC(){
    moveNearestTunneling(this.monster);
}
int Monster::scanAreaC(){
    return scanArea(this.monster);
}