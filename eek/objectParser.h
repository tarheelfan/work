#ifndef OBJECTPARSER
#define OBJECTPARSER
#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h> 
#include "dice.h"
using namespace std;

class objectInfo {
    public:
        string name;
        int type; 
        int weight;
        int color;
        Dice dodge;
        int value;
        Dice dam;
        Dice def;
        Dice hit;
        Dice speed;
        string desc;
        int attr;
    objectInfo(string name,string type,string weight,
    string color,string dodge,string val, string dam,
    string def, string hit,string speed, string desc, string attr);
    objectInfo();
    ~objectInfo();
};
int validSyntax(std::string input);
void readFileObjects();
int getColor(string c);
int getCharacteristics(string desc);
int getType(string color);
#endif