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
    npcInfo(string name,string symbol,string color,string desc,string speed,string dam,string hp, string abil);
    npcInfo();
    void printInfo();
    ~npcInfo();
};
int validSyntax(std::string input);
void readFile();
int getColor(string c);
Dice getDice(string spee);
int getCharacteristics(string desc);
  