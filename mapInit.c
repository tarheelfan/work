#include <stdio.h>
#include <stdlib.h>
#include "mapInit.h"
#include <time.h>
#include <stdlib.h>

int const x = 80;
int const y = 21;



struct Room {
    int topLeft[2];
    int topright[2];
    int bottomLeft[2];
    int bottomRight[2];
    int connected;
};

struct Map{
    char grid[21][80];
};

Map *m;

static Room* createRoom(void);
static void initRooms(Map *m);

int initMap(void);
static void initBorder(Map *m);
static int collides(Room *r,Room *ma,int s);
static void waitFor (unsigned int secs);
static int contains(Room *r,Room *ro);
static void connect(Map *m,Room *start,Room *end);

static void initBorder(Map *m){
    int count;
     srand(time(NULL));
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
        (*m).grid[20][count]='-';Map *map;
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
            //printf("%i\n",(*p).topLeft[0]);
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
    int myCount;
    
    for(er=0;er<7;er++){
        Room *temp = array[er];
        

    int coun;
    int height = (*temp).bottomLeft[0]-(*temp).topLeft[0];
    int width = (*temp).topright[1]-(*temp).topLeft[1];
    int co;
    int co2;
    
    for(co=0;co<height;co++){
        for(co2=0;co2<width;co2++){
            (*m).grid[(*temp).topLeft[0]+co][(*temp).topLeft[1]+co2]='.';
        }
    }  
   }
    int co;
    for(co=0;co<7;co++){
        Room *tem = array[co];
        char don='f';
        int incra=0;
        while(don!='t'){
            
            if((*m).grid[(*tem).bottomLeft[0]+incra][(*tem).bottomLeft[1]+2]!='.'){
                (*m).grid[(*tem).bottomLeft[0]+incra][(*tem).bottomLeft[1]+2]='#';
            }

            
            incra++;
            if(incra+(*tem).bottomLeft[0]>19){
                don='t';
            }
        }
        int q;
        for(q=1;q<79;q++){
            (*m).grid[19][q]='#';
        }
        char dona='f';
        int incraa=0;
        while(dona!='t'){
            int start = (*tem).bottomLeft[1]-1;
            if((*m).grid[(*tem).bottomLeft[0]-3][start-(incraa)]=='.'){
                (*m).grid[(*tem).bottomLeft[0]-3][(*tem).bottomLeft[1]-incraa]='#';
                dona='t';
                break;
            }
            
            if((*m).grid[(*tem).bottomLeft[0]-3][((*tem).bottomLeft[1])-(incraa)]=='|'){
                dona='t';
                break;
            }

            if((*m).grid[(*tem).bottomLeft[0]-3][(*tem).bottomLeft[1]-incraa]!='.'){
                (*m).grid[(*tem).bottomLeft[0]-3][(*tem).bottomLeft[1]-incraa]='#';
            }

            
            incraa++;
        }
        
    }
    int climb;
    for(climb=1;climb<20;climb++){
        (*m).grid[climb][2]='#';
    }
    



}



static int collides(Room *r,Room *ro, int s){
    
   int var1 = contains(r,ro);
   int var2 = contains(ro,r);

   if(var1==1 || var2==1){
       return 1;
   }else{
       return 0;
   }

    
}
static int contains(Room *inside,Room *out){
    int x1 = (*out).topLeft[0]-1;
    int y1 = (*out).topLeft[1]-1;
    int x2 = (*out).bottomRight[0]+1;
    int y2 = (*out).bottomRight[1]+1;

    int pointx1 = (*inside).topLeft[0];
    int pointy1 = (*inside).topLeft[1];
    int pointx2 = (*inside).bottomRight[0];
    int pointy2 = (*inside).bottomRight[1];
    
    int pointx3 = (*inside).topright[0];
    int pointy3 = (*inside).topright[1];

    int pointx4 = (*inside).bottomLeft[0];
    int pointy4 = (*inside).bottomLeft[1];

    if(pointx1>=x1 && x2>=pointx1){
        if(pointy1>=y1 && y2>=pointy1){
            return 1;
        }
    }
    if(pointx2>=x1 && x2>=pointx2){
        if(pointy2>=y1 && y2>=pointy2){
            return 1;
        }
    }
    if(pointx3>=x1 && x2>=pointx3){
        if(pointy3>=y1 && y2>=pointy3){
            return 1;
        }
    }
    if(pointx4>=x1 && x2>=pointx4){
        if(pointy4>=y1 && y2>=pointy4){
            return 1;
        }
    }
    return 0;
}


static void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

static Room* createRoom(void){
    char done ='n';
    Room *room;
    room = (struct Room*)malloc(sizeof(struct Room));
    (*room).connected=0;
    while(done!='y'){
        //waitFor(1);
        //srand(time(NULL));
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
        int locx = rand() % 19;
        locx++;
        int locy = rand() % 78;
        locy++;
        if((width+locy)<78){
            if((height+locx)<19){
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
    m = (struct Map*)malloc(sizeof(struct Map));
    initBorder(m);
    initRooms(m);
    return 0;
}

 void printGrid(){
    int i;
    int j;
    
    for(i=0;i<21;i++){
        for(j=0;j<80;j++){
            char temp = (*m).grid[i][j];
            if(!(temp=='-' || temp == '|' || temp=='.' || temp=='#')){
                temp=' ';
            }
            printf("%c",temp);
        }
        printf("%c\n",' ');
    }
}

void saveGame(){
    FILE *f;
    char *path = gentenv("PATH");
    *path += ".rlg327/";
    f = fopen(*path,"w");
    if(!f){
        fprint("could not write file");
        return 1;
    }


}