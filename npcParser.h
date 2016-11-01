#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h> 

class npcInfo {
    private:
        string name;
        string symbol;
        string description;
        int color;
        int speed;
        int hp;
        int dam;
        Dice speed;
        Dice 
    public:
    npcInfo();
    ~npcInfo();
    
};
int validSyntax(std::string input);
void readFile();
int getColor(string c);
int getDice(string spee);
Dice& getDice(string spee);
  class Dice{
      private:
        int base;
        int sides;
        int numDice;
        
      public:
        Dice(int ba,int si,int nu);
        ~Dice();
        int roleDice();
  };