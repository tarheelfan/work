#ifndef FACTORY
#define FACTORY
#include <time.h> 
#include "monsterFactory.h"
#include "gameMap.h"
#include "objectManager.h"
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
    Monster *monster = new Monster();
   // monster =(Monster*) malloc(sizeof(Monster));
    if(isPlayer){
        monster->symbol='@';
        monster->name = "The Player";
        monster->thePlayer=1;   
        monster->speed=10;
        monster->roundVal=10;
        monster->xloc=x;
        monster->yloc=y;
        monster->hp=10000;
        pcx = x;
        pcy = y;
        monster->alive=1;
        monster->dam = getDice("0+1d4");


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
        string temp=info.name;
        monster->name = temp;
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
 Item Factory::getItem(){
     int index = rand() % objectD.size();
     objectInfo temp = objectD.at(index);
    Item send(temp.name,temp.type,temp.weight,temp.color,temp.dodge,temp.value,temp.dam,temp.def.roleDice(),temp.hit.roleDice(),temp.speed.roleDice(),temp.desc,temp.attr);
     send.equiped=0;
     return send;
      
     
 }

 #endif