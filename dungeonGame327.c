#include <stdio.h>
#include "mapInit.h"
#include <string.h>

void initGame(void);

void initGame(void);
void playGame(void);
void closeGame(void);

int main (int argc, char* argv[]){
    //char *save = "--help";
    //char *argv1 = argv[1];
    
    initGame();
    playGame();
    closeGame();
    return 0;
}

void initGame(void){
    initMap();
    
}
void playGame(void){
    printGrid();
}
void closeGame(void){
    //if (strcmp(argv1, save) == 0){
        //saveGame();
    //}
}