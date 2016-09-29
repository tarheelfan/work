#include "dungeonGame327.h"
#include <stdio.h>
#include "mapInit.h"
#include <string.h>
#include "heap.h"
/*Switches*/
int load=0;
int save=0;
int numberOfCreatures=0;
int main (int argc, char* argv[]){
    int x;
    int eval;
    for(x=1;x<argc;x++){
        eval=strcmp(argv[x],"--save");
        if(eval==0){
            save=1;
        }
        eval=strcmp(argv[x],"--load");
        if(eval==0){
            load=1;
        }
        eval=strcmp(argv[x],"--nummon");
        if(eval==0){
            if(x+1>argc){
                printf("Please enter a value after the command --nummon");
                return 1;
            }
            char* numberOfCritters = argv[x+1];
            numberOfCreatures = atoi(numberOfCritters);
            if(numberOfCreatures>=1680){
                printf("What are you even doing bro");
                return 1;
            }
        }
    }
    initGame();
    playGame();
    closeGame();
    return 0;
}
void initGame(void){
    if(load){
        loadGame();
    }else{
      initMap();
    }
}
void playGame(void){
    printGrid();
    //printDistanceGrid();
    printDistanceGrid();
    printDistanceGridPlus();
}
void closeGame(void){
    if(save){
        saveGame();
    }
}