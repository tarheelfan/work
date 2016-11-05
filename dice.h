#ifndef DICE
# define DICE

#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 
#include <string>
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
  Dice getDice(std::string spee);

  #endif