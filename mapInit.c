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
static int collides(Room *r,Room *ma,int s);

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
    
    Room* array[7];
    int z;
    int size=0;
    for(z=0;z<7;z++){
        char done ='f';
        while(done!='t'){
            if(z==0){
                array[z]=createRoom();// *array[z]=createRoom();
                 done='t';
                 size++;
                 break;
            }    
            Room *p = createRoom();
            int a;
            int col =0;
            for(a=0;a<size;a++){
                Room *cvb = array[a];
                if(collides(p,cvb,0)==1){
                    col=1;
                    
                }
            }
            if(col==0){
                array[size]= p; //might work lol
                size++;
                done='t';
            }
            

        }
    }

    int er;
    for(er=0;er<7;er++){
        Room *temp = array[er];

    (*m).grid[(*temp).topLeft[0]][(*temp).topLeft[1]]='X';
    (*m).grid[(*temp).topright[0]][(*temp).topright[1]]='X';
    (*m).grid[(*temp).bottomLeft[0]][(*temp).bottomLeft[1]]='X';
    (*m).grid[(*temp).bottomRight[0]][(*temp).bottomRight[1]]='X';
    
    } 
    
    
    
    



}
static int collides(Room *r,Room *ro, int s){
    int x1 = (*ro).topLeft[0];
    int x2 = (*ro).bottomLeft[0];
    int y1 = (*ro).topLeft[1];
    int y2 = (*ro).bottomLeft[1];



    int roomX1 = (*r).topLeft[0];
    int roomX2 = (*r).bottomLeft[0];
    int roomY1 = (*r).topLeft[1];
    int roomY2 = (*r).bottomLeft[1];
    if(roomX1>x1 && x2<roomX1){
        if(roomY1>y1 && y2<roomY1){
            return 1;
        }
    }
    if(roomX2>x1 && x2<roomX2){
        if(roomY2>y1 && y2<roomY2){
            return 1;
        }
    }
    
     x1 = (*ro).topright[0];
     x2 = (*ro).bottomRight[0];
     y1 = (*ro).topright[1];
     y2 = (*ro).bottomRight[1];



     roomX1 = (*r).topright[0];
     roomX2 = (*r).bottomRight[0];
     roomY1 = (*r).topright[1];
     roomY2 = (*r).bottomRight[1];
    if(roomX1>x1 && x2<roomX1){
        if(roomY1>y1 && y2<roomY1){
            return 1;
        }
    }
    if(roomX2>x1 && x2<roomX2){
        if(roomY2>y1 && y2<roomY2){
            return 1;
        }
    }
    if(s==1){
        return 0;
    }
    return collides(ro,r,1);
    
}
static Room* createRoom(void){
    char done ='n';
    Room *room;
    room = (struct Room*)malloc(sizeof(struct Room));
    while(done!='y'){
         
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
        if((width+locy)<78){
            if((height+locx)<23){
                done='y';
            }
        }
        /*printf("width: %i\n",width);*/
        /*printf("height: %i\n",height);*/
        /*printf("locx: %i\n",locx);*/
        /*printf("locy: %i\n",locy);*/
        (*room).topLeft[0]=locx;
        (*room).topLeft[1]=locy;
        (*room).topright[0]=locx;
        (*room).topright[1]=locy+width;
        (*room).bottomLeft[0]=locx+height;
        (*room).bottomLeft[1]=locy;
        (*room).bottomRight[0]=locx+height;
        (*room).bottomRight[1]=locy+width;
    }
   
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