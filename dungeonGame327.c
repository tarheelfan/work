#include <stdio.h>
#include "mapInit.h"

void initGame(void);

void initGame(void);
void playGame(void);
void closeGame(void);

int main (int argc, char* argv[]){
    initGame();
    playGame();
    return 0;
}

void initGame(void){
    initMap();
    
}
void playGame(void){
    printGrid();
}
void closeGame(void){

}