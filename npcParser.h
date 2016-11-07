#ifndef NPCPARSER
#define NPCPARSER
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h> 
#include "dice.h"

using namespace std;

class npcInfo {
    private:
        string name;
        char symbol;
        string description;
        int color;
        int speed_i;
        int hp_i;
        int dam_i;
        Dice speed;
        Dice dam;
        Dice hp;
        unsigned int characteristics : 4;
    public:
    inline unsigned int npcInfo::getInfoCharacter(){
        return this->characteristics;
    }
    inline int npcInfo::getColori(){
        return this->color;
    }
    inline string npcInfo::getDesc(){
        return this->description;
    }
    inline int npcInfo::getHP(){
        return this->hp_i;
    }
    inline Dice getDamDice(){
        return this->dam;
    }
    npcInfo(string name,string symbol,string color,string desc,string speed,string dam,string hp, string abil);
    npcInfo();
    void printInfo();
    ~npcInfo();
};
int validSyntaxNPC(std::string input);
void readFile();
int getColorNPC(string c);
Dice getDice(string spee);
int getCharacteristics(string desc);
  