#include "main.h"
#include <stdio.h>
#include "gameMap.h"
#include <string.h>
#include "heap.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "npcParser.h"
#include "objectParser.h"
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
     readFile();
//     readFileObjects();
      if(1){
        initMap(5);
      }else{
          printf("Need The Number of Monsters and --nummon command \n");
          return 1;
   }
    return 0;

}
void StartGame(void){
    char ex;
   printw("Enter Any Key To Start");
   while(1){
        ex = getch();

    if(ex){
        playGame();
        return;
    }
    }


}
void closeGame(void){
    endwin();

}
