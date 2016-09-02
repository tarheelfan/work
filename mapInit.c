#include <stdio.h>
#include <stdlib.h>
#include "mapInit.h"
int const x = 80;
int const y = 24;



 struct Room {
    int topLeft[1];
    int topright[1];
    int bottomLeft[1];
    int bottomRight[1];
};

 struct Map{
    char grid[24][80];
};

static void printGrid(Map *m);
int initMap(void);
static void initBorder(Map *m);

static void initBorder(Map *m){
    int count;
    for(count=0;count<80;count++){
        (*m).grid[0][count] = '-';
    }
    for(count=0;count<80;count++){
        (*m).grid[count][0]='|';
    }
    for(count=0;count<80;count++){
        (*m).grid[count][79]='|';
    }
    for(count=0;count<80;count++){
        (*m).grid[79][count]='-';
    }
}

int initMap(void){
    Map *map;
    map = (struct Map*)malloc(sizeof(struct Map));
    initBorder(map);
    printGrid(map);
    free(map);
    return 0;
}

static void printGrid(Map *m){
    int i;
    int j;
    
    for(i=0;i<24;i++){
        for(j=0;j<80;j++){
            printf("%c",(*m).grid[i][j]);
        }
        printf("%c\n",' ');
    }
}