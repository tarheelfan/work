#include <stdio.h>
#include <stdlib.h>
#include "mapInit.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//4 bytes per room
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
    int hardness[21][80];
    Room *rooms;
};
/* turn this into package */
typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
/*                            */
Map *m;
static int initMapFile(void);
static Room* createRoom(void);
static void initRooms(void);
int initMap(void);
static void initBorder(void);
static int collides(Room *r,Room *ma,int s);
static int contains(Room *r,Room *ro);


static void initBorder(void){
    int count;
    srand(time(NULL));
    int e;
    int ein;
    for(e=1;e<21;e++){
        for(ein=1;ein<80;ein++){
            if((*m).grid[e][ein]=='.' || (*m).grid[e][ein]=='#'){
              (*m).hardness[e][ein]=0;  
            }
            (*m).hardness[e][ein]=(rand()%245)+1;
        }
    }
    for(count=0;count<80;count++){
        (*m).grid[20][count]='-';
        (*m).hardness[20][count]=255;
    }
    for(count=0;count<21;count++){
        (*m).grid[count][0]='|';
        (*m).hardness[count][0]=255;
    }
    for(count=0;count<21;count++){
        (*m).grid[count][79]='|';
        (*m).hardness[count][79]=255;
    }
   for(count=0;count<80;count++){
        (*m).grid[0][count] = '-';
        (*m).hardness[0][count] = 255;
    }
    
   
}
//h to be 32()
//be 32 to h()
static void initRooms(void){
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
                (*m).rooms[size]=*p;
                size++;
                done='t';
            }
        }
    }

    int er;
    
    
    for(er=0;er<7;er++){
        Room *temp = array[er];
        

    
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
static Room createRoomFile(int xUperLeft,int xSize,int yUperLeft,int ySize){
    Room r;
    r.topLeft[0]=xUperLeft;
    r.topLeft[1]=yUperLeft;
    r.bottomLeft[0]=xUperLeft+xSize;
    r.bottomLeft[1]=yUperLeft;
    r.topright[0]=xUperLeft;
    r.topright[1]=yUperLeft+ySize;
    r.bottomRight[0]=xUperLeft+xSize;
    r.bottomRight[1]=yUperLeft+ySize;
    return r;
}
static Room* createRoom(void){
    char done ='n';
    Room *room;
    room = (struct Room*)malloc(sizeof(struct Room));
    (*room).connected=0;
    while(done!='y'){
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
    initBorder();
    initRooms();
    return 0;
}
static int initMapFile(void){
    m = (struct Map*)malloc(sizeof(struct Map));
    (*m).rooms= (Room*)calloc(30,sizeof(Room));
    initBorder();
    return 0;
}
//Room *rooms[20];
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

int saveGame(){
   
    FILE *f;
    char *home = getenv("HOME");
    strcat(home,"/.rlg327/");
    strcat(home,"Dungeon");
    f = fopen(home,"w");
    if(!f){
      printf("could not write file\n");
        return 1;
    }
    char *title = "RLG327";
    //unsigned char *version =(unsigned char*)"0";
    unsigned int version = 0;
    int sizeint=0;
    sizeint = 1694 + sizeof((*m).rooms);

    fwrite(title,sizeof(char),6,f);
    fwrite(&version,sizeof(char),4,f);
    fwrite(&sizeint,sizeof(char),4,f);//bug here
    fwrite((*m).hardness,sizeof(char),1680,f);
    char dungeons[sizeof((*m).rooms)] ="";
    int iou;
    for(iou=0;iou<sizeof((*m).rooms);iou++){
        Room t = (*m).rooms[iou];
        char val = t.topLeft[0];
        strcpy(dungeons,&val);
        Room q = (*m).rooms[iou];
        int dif = q.bottomLeft[0]-q.topLeft[0];
        int intsizz = dif;
        char charsize = intsizz;
        strcpy(dungeons,&charsize);
        Room wer = (*m).rooms[iou];
        int yloc = wer.topLeft[1];
        char ylocchar = yloc;
        strcpy(dungeons,&ylocchar);
        Room pl =(*m).rooms[iou];
        int ysize = pl.topright[1]-pl.topLeft[1];
        char charysize = ysize;
        strcpy(dungeons,&charysize);
    
    }
    fwrite(dungeons,sizeof(char),4*sizeof((*m).rooms),f);
    fclose(f);
    return 0;
}

int size;
int loadGame(){
    FILE *f;
    char title[6];
    char version[4];
    char rowMajor[1680];
    char *home = getenv("HOME");
    strcat(home,"/.rlg327/");
    strcat(home,"Dungeon");
    f= fopen(home,"r");
    if(!f){
        printf("cant open file");
        return 1;
    }
    fread(title,sizeof(char),6,f);
    fread(version,sizeof(char),4,f);
    fread(&size,sizeof(char),4,f);
    fread(rowMajor,sizeof(char),1680,f);
    size=size/4;
    initMapFile();
    char *dat;
    dat = (char*)calloc(size,4);
    fread(dat,sizeof(char),4*size,f);
    int backup =size;
    int q;
    int counter=0;
    for(q=0;q<size;q++,counter=counter+4){
        (*m).rooms[size]=createRoomFile((dat[counter]),(dat[counter+1]),(dat[counter+2]),(dat[counter+3]));
    }
    printf("%d",(*m).rooms[2].topLeft[1]);
    int y;
    int o;
    for(y=0;y<21;y++){
        for(o=0;o<80;o++){
            (*m).hardness[y][o]=rowMajor[y*o];
        }
        
    }
    initBorder();
    for(y=0;y<21;y++){
        for(o=0;o<80;o++){
            if((*m).hardness[y][o]==0){
                (*m).grid[y][o]='#';
            }
            
        }
    }
        int az;
        //size
        for(az=0;az<4;az++){
            Room temp;
            temp = (*m).rooms[az];
            
            int num = temp.topLeft[0];
            int num2 = temp.topLeft[1];
            (*m).grid[num][num2]='.';

            num = temp.topright[0];
            num2 = temp.topright[1];
            (*m).grid[num][num2]='.';

            num = temp.bottomLeft[0];
            num2 = temp.bottomLeft[1];
            (*m).grid[num][num2]='.';

            num =temp.bottomRight[0];
            num2=temp.bottomRight[1];
            (*m).grid[num][num2]='.';
            
        }
        fclose(f);
return 0;
}


