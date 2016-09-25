#include <stdio.h>
#include "mapInit.h"
#include <string.h>
#include "heap.h"

int load=0;
int save=0;
void initGame(void);
void playGame(void);
void closeGame(void);

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