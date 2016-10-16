#include "dungeonGame327.h"
#include <stdio.h>
#include "gameMap.h"
#include <string.h>
#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
/*Switches*/
int numberOfCreatures= 0;
char* numberOfCritters = 0;
int main (int argc, char* argv[]){
    int x;
    int eval;
    
    for(x=1;x<argc;x++){
        eval=strcmp(argv[x],"--nummon");
        if(eval==0){
            
            numberOfCritters = argv[x+1];
            numberOfCreatures = atoi(numberOfCritters);
            if(numberOfCreatures>=1680 || numberOfCreatures==0){
                printf("What are you even doing bro");
                return 1;
            }else{
                
            }
        }
    }
    
    if(initGame()){
        return 1;
    }
    StartGame();
    closeGame();
    return 0;
}
int initGame(void){
      if(1){/*Code Changed for Purpose of Debugging*/
        initMap(15);
      }else{
          printf("Need The Number of Monsters and --nummon command \n");
          return 1;
      }
    return 0;
}
void StartGame(void){
    playGame();
}
void closeGame(void){
    endwin();
    
}
