#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h> 
using namespace std;

class Dice{
      private:
        int base;
        int sides;
        int numDice;
        
      public:
        Dice(int ba,int si,int nu);
        Dice();
        ~Dice();
        int roleDice();
  };
class objectInfo {
    private:
        string name;
        int type; 
        /*
        0=light

        */
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
    public:
    objectcInfo(string name,string type,string,string weight,string color,string dodge,string val, string dam, string def, string hit,string speed, string desc, string attr);
    objectInfo();
    void printInfo();
    ~objectInfo();
};
int validSyntax(std::string input);
void readFile();
int getColor(string c);
Dice getDice(string spee);
int getCharacteristics(string desc);
int getType(string color);