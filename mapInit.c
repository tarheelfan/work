#include <stdio.h>
#include <stdlib.h>
#include "mapInit.h"
#include <time.h>
#include <stdlib.h>

int const x = 80;
int const y = 24;



 struct Room {
    int topLeft[2];
    int topright[2];
    int bottomLeft[2];
    int bottomRight[2];
};

 struct Map{
    char grid[24][80];
};
static Room* createRoom(void);
static void initRooms(Map *m);
static void printGrid(Map *m);
int initMap(void);
static void initBorder(Map *m);


static void initBorder(Map *m){
    int count;
    
    for(count=0;count<80;count++){
        (*m).grid[count][0]='|';
    }
    for(count=0;count<80;count++){
        (*m).grid[count][79]='|';
    }
    for(count=0;count<80;count++){
        (*m).grid[0][count] = '-';
    }
    for(count=0;count<80;count++){
        (*m).grid[23][count]='-';Map *map;
    map = (struct Map*)malloc(sizeof(struct Map));
    }
}
static void initRooms(Map *m){
    Room *p = createRoom();
    (*m).grid[(*p).topLeft[0]][(*p).topLeft[1]]='X';
    (*m).grid[(*p).topright[0]][(*p).topright[1]]='X';
    (*m).grid[(*p).bottomLeft[0]][(*p).bottomLeft[1]]='X';
    (*m).grid[(*p).bottomRight[0]][(*p).bottomRight[1]]='X';
}
static Room* createRoom(void){
    Room *room;
    room = (struct Room*)malloc(sizeof(struct Room));
    srand(time(NULL));
    int height = rand();
    height = height % 7;
    if(height<5){
        height=height+5;
    }
    int width = rand();
    width = width % 7;
    if(width<5){
        width=width+5;
    }
    int locx = rand() % 22;
    locx++;
    int locy = rand() % 78;
    locy++;

    (*room).topLeft[0]=locx;
    (*room).topLeft[1]=locy;
    (*room).topright[0]=locx;
    (*room).topright[1]=locy+width;
    (*room).bottomLeft[0]=locx+height;
    (*room).bottomLeft[1]=locy;
    (*room).bottomRight[0]=locx+height;
    (*room).bottomRight[1]=locy+width;
    return room;
}
int initMap(void){
    Map *map;
    map = (struct Map*)malloc(sizeof(struct Map));
    initBorder(map);
    initRooms(map);
    printGrid(map);
    free(map);
    return 0;
}

static void printGrid(Map *m){
    int i;
    int j;
    
    for(i=0;i<24;i++){
        for(j=0;j<80;j++){
            char temp = (*m).grid[i][j];
            if(!(temp=='-' || temp == '|' || temp=='X')){
                temp=' ';
            }
            printf("%c",temp);
        }
        printf("%c\n",' ');
    }
}