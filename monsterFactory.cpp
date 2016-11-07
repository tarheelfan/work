#include <time.h> 
#include "monsterFactory.h"
#include "gameMap.h"
using namespace std;

void initList(struct list dir){
    dir.size=0;
}
Factory::Factory(){
    numOfMonsters = 0;
    srand(0);
}
Factory::~Factory(){
    /*Deconstructor*/
}
void Factory::locked(vector<npcInfo> v){
    this->monstersD=v;
}
void Factory::loaded(vector<objectInfo> v){
    this->objectD=v;
}
 Monster* Factory::getMon(Map *map,int x,int y,int isPlayer){
    int random = rand() % this->monstersD.size();
    npcInfo info = monstersD.at(random);
    Monster *monster;
    monster =(Monster*) malloc(sizeof(Monster));
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
        initList(monster->directions);
        monster->thePlayer=0;
        monster->patrolMode=1;
        monster->alive=1;
        monster->characteristics = info.getInfoCharacter();
        monster->modelNumber=numOfMonsters;
        monster->yloc=y;
        monster->searchLocationY=y;
        monster->searchLocationX=x;
        monster->xloc=x;
        monster->symbol=info.symbol;
        monster->name=info.name;
        monster->color = info.getColori();
        monster->desc = info.getDesc();
        monster->hp = info.getHP();
        monster->dam = info.getDamDice();
        if(!isPlayer){
            int spee = info.speed_i;
            spee = 100 / spee;
            monster->roundVal=spee;
            monster->speed= spee;
        }
    numOfMonsters++;
    monsterArray[monster->yloc][monster->xloc]=monster;
    
 }
 return monster;
}
 