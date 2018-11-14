#ifndef DICE
# define DICE

#include <stdlib.h>
#include <stdio.h> 
#include <time.h> 
#include <string>
#include <sstream>
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

        inline string getDescription(){
          std::ostringstream stream;
          stream << "BASE : " << base << " SIDES: " << sides << " NUM_OF_DICE: " << numDice;
          return stream.str();
        }
  };
  Dice getDice(std::string spee);

  #endif