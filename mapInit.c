#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "mapInit.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <endian.h>
#include <stdint.h>
#include <sys/stat.h>
#include <limits.h>
int const x = 80;
int const y = 21;
#define DUNGEON_X 80
#define DUNGEON_Y 21
#define mappair(pair) ((*m).grid[pair[dim_y]][pair[dim_x]])
#define mapxy(x, y) ((*m).grid[y][x])
#define hardnesspair(pair) ((*m).hardness[pair[dim_y]][pair[dim_x]])
#define hardnessxy(x, y) ((*m).hardness[y][x])

Map *m;
static int getWeight(int num);
static void analyzeDistances(void);
static Room* createRoom(void);
static void initRooms(void);
int initMap(void);
static void initBorder(void);
static int collides(Room *r,Room *ma,int s);
static int contains(Room *r,Room *ro);
static void addRoom(Room r);
static char getAsci(int num);
static void analyzeDistancesPlus(void);


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
            (*m).hardness[e][ein]=(rand()%243)+2;
            //(*m).hardness[e][ein]=2;
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
static int getWeight(int num){
    if(num<85){
        return 1;
    }
    if(num<171){
        return 2;
    }
    if(num<255){
        return 3;
    }
    return 10000;
}


void static addRoom(Room r){
    int x;
    int y;
    int xStart = r.topLeft[0];
    int yStart = r.topLeft[1];
    int xHeight = r.bottomLeft[0]-r.topLeft[0];
    int yHeight = r.topright[1] - r.topLeft[1];
    for(x=xStart;x<xHeight+xStart;x++){
        for(y=yStart;y<yHeight+yStart;y++){
            (*m).grid[x][y]='.';
        }
    }
}

int32_t compare_cell(const void *key,const void *with){
  return (*(const distanceCell *) key).distance - (*(const distanceCell *) with).distance;
}


static void analyzeDistancesPlus(void){//x loc 17 loc 6
    int xPre=0;
    int yPre=0;

    for(xPre=1;xPre<79;xPre++){
        for(yPre=1;yPre<20;yPre++){
            distanceCell pass;
            pass.distance=10000;
            pass.yloc=yPre;/* 1000 will represent infinity */
            pass.xloc=xPre; 
            (*m).distanceGrid[yPre][xPre]=pass; 
        }
    }
    (*m).distanceGrid[(*m).pcY][(*m).pcX].distance=0;
    binheap_t heap;
    binheap_init(&heap,compare_cell,free);
    int pcXl;
    int pcYl;
    pcXl=(*m).pcX;
    pcYl=(*m).pcY;
    distanceCell root = (*m).distanceGrid[pcYl][pcXl];
    root.distance=0;
    binheap_insert(&heap,&root);
    int tempx;
    int tempy;
    while(!binheap_is_empty(&heap)){
        distanceCell *temp;
        temp =(distanceCell*) binheap_remove_min(&heap);
        tempx = (*temp).xloc;
        tempy = (*temp).yloc;
        int alt;
        //if(tempy<22 && tempx<81 && tempy>-1 && tempx>-1){
        if((*m).grid[(*temp).yloc-1][(*temp).xloc]!='-' || (*m).grid[(*temp).yloc-1][(*temp).xloc]!='|'){/* top */
                
                alt = getWeight((*m).hardness[tempy-1][tempx]);
                alt = alt + (*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy-1][tempx].distance>alt){
                    (*m).distanceGrid[tempy-1][tempx].distance=alt;
                    distanceCell *temp0;
                    temp0 = &(*m).distanceGrid[tempy-1][tempx];
                    binheap_insert(&heap, temp0);
                    
            }
        } 
         if((*m).grid[(*temp).yloc+1][(*temp).xloc]!='-' || (*m).grid[(*temp).yloc+1][(*temp).xloc]!='|'){/* bottom */
                
                alt = getWeight((*m).hardness[tempy+1][tempx])+(*m).distanceGrid[tempy][tempx].distance; 
                if((*m).distanceGrid[tempy+1][tempx].distance>alt){
                    (*m).distanceGrid[tempy+1][tempx].distance=(*temp).distance+1;
                    distanceCell *temp1;
                    temp1 = &(*m).distanceGrid[tempy+1][tempx];
                    binheap_insert(&heap,temp1);
                }
        } 
         if((*m).grid[(*temp).yloc][(*temp).xloc+1]!='-' || (*m).grid[(*temp).yloc][(*temp).xloc+1]!='|'){/* right */
                
                alt = getWeight((*m).hardness[tempy][tempx+1])+(*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy][tempx+1].distance>alt){
                    (*m).distanceGrid[tempy][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp2;
                    temp2 = &(*m).distanceGrid[tempy][tempx+1];
                    binheap_insert(&heap,temp2);
                }
        } 
         if((*m).grid[(*temp).yloc][(*temp).xloc-1]!='-' || (*m).grid[(*temp).yloc][(*temp).xloc-1]!='|'){/* left */
                
                
                 alt = getWeight((*m).hardness[tempy][tempx])+(*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy][tempx-1].distance>alt){
                    (*m).distanceGrid[tempy][tempx-1].distance=alt;
                    distanceCell *temp3;
                    temp3 = &(*m).distanceGrid[tempy][tempx-1];
                    binheap_insert(&heap,temp3);   
                }
        }
        if((*m).grid[(*temp).yloc-1][(*temp).xloc+1]!='-' || (*m).grid[(*temp).yloc-1][(*temp).xloc+1]!='|'){/* top right */
            
                
                alt = getWeight((*m).hardness[tempy-1][tempx+1])+(*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy-1][tempx+1].distance>alt){
                    (*m).distanceGrid[tempy-1][tempx+1].distance=alt;
                    distanceCell *temp4;
                    temp4 = &(*m).distanceGrid[tempy-1][tempx+1];
                    binheap_insert(&heap,temp4);
                    
                }

            
        }
        if((*m).grid[(*temp).yloc-1][(*temp).xloc-1]!='-' || (*m).grid[(*temp).yloc-1][(*temp).xloc-1]=='|'){/* top left */
           
                
                 alt = getWeight((*m).hardness[tempy-1][tempx-1])+(*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy-1][tempx-1].distance>alt){
                    (*m).distanceGrid[tempy-1][tempx-1].distance=alt;
                    distanceCell *temp5;
                    temp5 = &(*m).distanceGrid[tempy-1][tempx-1];
                   binheap_insert(&heap,temp5);
                }

            
        }
        if((*m).grid[(*temp).yloc+1][(*temp).xloc-1]!='-' || (*m).grid[(*temp).yloc+1][(*temp).xloc-1]!='|'){/* bottomLeft left */
            
                
                 alt = getWeight((*m).hardness[tempy+1][tempx-1])+(*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy+1][tempx-1].distance>alt){
                    (*m).distanceGrid[tempy+1][tempx-1].distance=alt;
                    distanceCell *temp6;
                    temp6 = &(*m).distanceGrid[tempy+1][tempx-1];
                    binheap_insert(&heap,temp6);
                    
                }

            
        }
        if((*m).grid[(*temp).yloc+1][(*temp).xloc+1]!='-' || (*m).grid[(*temp).yloc+1][(*temp).xloc+1]!='|'){/* bottom right */
            
                
                 alt = getWeight((*m).hardness[tempy+1][tempx+1])+(*m).distanceGrid[tempy][tempx].distance;
                if((*m).distanceGrid[tempy+1][tempx+1].distance>alt){
                    (*m).distanceGrid[tempy+1][tempx+1].distance=alt;
                    distanceCell *temp7;
                    temp7 = &(*m).distanceGrid[tempy+1][tempx+1];
                    binheap_insert(&heap,temp7);
                    
                }
        }

       // }
    }
}

    



static void analyzeDistances(void){
    int xPre;
    int yPre;
    for(xPre=0;xPre<80;xPre++){
        for(yPre=0;yPre<21;yPre++){
            distanceCell pass;
            pass.distance=1000;
            pass.yloc=yPre;/* 1000 will represent infinity */
            pass.xloc=xPre; 
            (*m).distanceGrid[yPre][xPre]=pass; 
        }
    }
    (*m).distanceGrid[(*m).pcY][(*m).pcX].distance=0;
    binheap_t heap;
    binheap_init(&heap,compare_cell,free);
    int pcXl;
    int pcYl;
    pcXl=(*m).pcX;
    pcYl=(*m).pcY;
    distanceCell root = (*m).distanceGrid[pcYl][pcXl];
    root.distance=0;
    binheap_insert(&heap,&root);
    int tempx;
    int tempy;
    while(!binheap_is_empty(&heap)){
        
        distanceCell *temp;
        temp =(distanceCell*) binheap_remove_min(&heap);
        tempx = (*temp).xloc;
        tempy = (*temp).yloc;

        int nextVal =(*m).distanceGrid[tempy][tempx].distance+1;

        //int nextVal =(*m).distanceGrid[tempy][tempx].distance+1;

        if((*m).grid[(*temp).yloc-1][(*temp).xloc]=='.' || (*m).grid[(*temp).yloc-1][(*temp).xloc]=='#'){/* top */
                if((*m).distanceGrid[tempy-1][tempx].distance==1000){
                    (*m).distanceGrid[tempy-1][tempx].distance=(*temp).distance+1;
                    distanceCell *temp0;
                     temp0 = &(*m).distanceGrid[tempy-1][tempx];
                    binheap_insert(&heap, temp0);
                    
            }
        } 
         if((*m).grid[(*temp).yloc+1][(*temp).xloc]=='.' || (*m).grid[(*temp).yloc+1][(*temp).xloc]=='#'){/* bottom */
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy+1][tempx].distance==1000){
                    (*m).distanceGrid[tempy+1][tempx].distance=(*temp).distance+1;
                    distanceCell *temp1;
                    temp1 = &(*m).distanceGrid[tempy+1][tempx];
                    binheap_insert(&heap,temp1);
                }
        } 
         if((*m).grid[(*temp).yloc][(*temp).xloc+1]=='.' || (*m).grid[(*temp).yloc][(*temp).xloc+1]=='#'){/* right */
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy][tempx+1].distance==1000){
                    (*m).distanceGrid[tempy][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp2;
                    temp2 = &(*m).distanceGrid[tempy][tempx+1];
                    binheap_insert(&heap,temp2);
                }

            
        } 
         if((*m).grid[(*temp).yloc][(*temp).xloc-1]=='.' || (*m).grid[(*temp).yloc][(*temp).xloc-1]=='#'){/* left */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy][tempx-1].distance==1000){
                    (*m).distanceGrid[tempy][tempx-1].distance=(*temp).distance+1;
                    distanceCell *temp3;
                    temp3 = &(*m).distanceGrid[tempy][tempx-1];
                    binheap_insert(&heap,temp3);
                    
                }

            
        }
        if((*m).grid[(*temp).yloc-1][(*temp).xloc+1]=='.' || (*m).grid[(*temp).yloc-1][(*temp).xloc+1]=='#'){/* top right */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy-1][tempx+1].distance==1000){
                    (*m).distanceGrid[tempy-1][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp4;
                    temp4 = &(*m).distanceGrid[tempy-1][tempx+1];
                    binheap_insert(&heap,temp4);
                    
                }

            
        }
        if((*m).grid[(*temp).yloc-1][(*temp).xloc-1]=='.' || (*m).grid[(*temp).yloc-1][(*temp).xloc-1]=='#'){/* top left */
           
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy-1][tempx-1].distance==1000){
                    (*m).distanceGrid[tempy-1][tempx-1].distance=(*temp).distance+1;
                    distanceCell *temp5;
                    temp5 = &(*m).distanceGrid[tempy-1][tempx-1];
                   binheap_insert(&heap,temp5);
                }

            
        }
        if((*m).grid[(*temp).yloc+1][(*temp).xloc-1]=='.' || (*m).grid[(*temp).yloc+1][(*temp).xloc-1]=='#'){/* bottomLeft left */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy+1][tempx-1].distance==1000){
                    (*m).distanceGrid[tempy+1][tempx-1].distance=(*temp).distance+1;
                    distanceCell *temp6;
                    temp6 = &(*m).distanceGrid[tempy+1][tempx-1];
                    binheap_insert(&heap,temp6);
                    
                }

            
        }
        if((*m).grid[(*temp).yloc+1][(*temp).xloc+1]=='.' || (*m).grid[(*temp).yloc+1][(*temp).xloc+1]=='#'){/* bottom right */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).distanceGrid[tempy+1][tempx+1].distance==1000){
                    (*m).distanceGrid[tempy+1][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp7;
                    temp7 = &(*m).distanceGrid[tempy+1][tempx+1];
                    binheap_insert(&heap,temp7);
                }
        }
    }
}
static void initRooms(void){
    Room* array[7];
    (*m).numOfRooms=7;
    int z;
    int size=0;
    for(z=0;z<7;z++){
        char done ='f';
        while(done!='t'){
            if(z==0){
                Room *r = createRoom();
                array[z]=r;// *array[z]=createRoom();
                 (*m).rooms[0]=*r;
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
    
int a;
int g;
for(a=0;a<21;a++){
    for(g=0;g<80;g++){
        char temp = (*m).grid[21][80];
        if(temp=='.' || temp=='#'){
            (*m).hardness[21][80]=0;
        }
        if(temp=='|' || temp=='-'){
            (*m).hardness[21][80]=255;
        }
    }
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
    room = (Room*)malloc(sizeof( Room));
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

static char getAsci(int num){
    char asci;
    if(num>=10 && num<36){
        num = num-10;
        num = num%26;
        asci='a';
        int x;
        for(x=0;x<num;x++){
            asci++;
        }
        return asci;
    }else{
            num=num-10;
            num= num%26;
            asci='A';
            int x;
            for(x=0;x<num;x++){
                asci++;
            }
            return asci;
        }
}


int initMap(void){
    m = (Map*)malloc(sizeof(Map));
    initBorder();
    initRooms();
    int done=0;
    while(!done){
        int xrand = rand()%80;
        int yrand = rand()%21;
        if((*m).grid[yrand][xrand]=='.'){
            (*m).pcX=xrand;
            (*m).pcY=yrand;
            done=1;
        } 
    }
    int c;
    int f;
    for(c=0;c<21;c++){
        for(f=0;f<80;f++){
            char temp = (*m).grid[c][f];
            if(temp=='.' || temp=='#'){
                (*m).hardness[c][f]=0;
            }

        }
    }
    //analyzeDistances();
    analyzeDistancesPlus();
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
            if((*m).pcX==j && (*m).pcY==i){
                printf("@");
            }else{
                printf("%c",temp);
            }
            
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
    int version = 0;
    version = htobe32(version);
    int sizeint;
    sizeint = 1694;
    sizeint = sizeint + 4 * (*m).numOfRooms;
    sizeint = htobe32(sizeint);
    fwrite(title,1,6,f);
    fwrite(&version,4,1,f);
    fwrite(&sizeint,4,1,f);
    fwrite((*m).hardness,1,1680,f);
    
    int a;

        
    for (a=0; a<(*m).numOfRooms; a++){
         
        int topLeftX; 
        int xWidth;
        int topLeftY;
        int yWidth;
         topLeftY =  (*m).rooms[a].topLeft[1];
         yWidth = (*m).rooms[a].bottomLeft[0]-(*m).rooms[a].topLeft[0];
         topLeftX = (*m).rooms[a].topLeft[0];
         xWidth = (*m).rooms[a].topright[1]-(*m).rooms[a].topLeft[1];
        fwrite(&topLeftY, 1, 1, f);
        fwrite(&xWidth, 1, 1, f);
        fwrite(&topLeftX, 1, 1, f);
        fwrite(&yWidth, 1, 1, f);
        //Room r = createRoomFile(topLeftY,yWidth,topLeftX,xWidth);
        
    }

    fclose(f);
    return 0;
}



int size;
int loadGame(){
    m = (Map*)malloc(sizeof(Map));
    initBorder();
    FILE *f;
    char title[6];
    int version; 
    char *home;
    home = (char*) malloc(sizeof(char)*100);
    strcpy(home,getenv("HOME"));
    strcat(home,"/.rlg327/");
    strcat(home,"Dungeon");
    f= fopen(home,"r");
    if(!f){
        printf("cant open file");
        return 1;
    }
    unsigned char hardnessModel[21][80];
    int res;
    res = fread(title,1,6,f);
    res = fread(&version,4,1,f);
    res = fread(&size,4,1,f);
   
    
    res = fread(hardnessModel,1,1680,f);
    int az;
    int hg;
    for(az=0;az<21;az++){
        for(hg=0;hg<80;hg++){
            (*m).hardness[az][hg]=hardnessModel[az][hg];
        }
    }
    size = be32toh(size);
    int max = (size-1694)/4;
    int t;
    int j;
    for(t=0;t<21;t++){
        for(j=0;j<80;j++){
            if(hardnessModel[t][j]==0){
                (*m).grid[t][j]='#';
            }
        }
    }
    int a;
    (*m).numOfRooms=0;
    for (a=0; a<max; a++){
        uint8_t topLeftX;
        uint8_t xWidth;
        uint8_t topLeftY;
        uint8_t yWidth;
        res = fread(&topLeftX, sizeof(topLeftX), 1, f);
        res = fread(&xWidth, sizeof(xWidth), 1, f);
        res = fread(&topLeftY, sizeof(topLeftY), 1, f);
        res = fread(&yWidth, sizeof(yWidth), 1, f);
        if(res==-666){
            printf("0");
        }
        Room r = createRoomFile(topLeftY,yWidth,topLeftX,xWidth);
        (*m).rooms[a]=r;
        (*m).numOfRooms=(*m).numOfRooms+1;
        
        addRoom(r);
    }
    int done=0;
    while(!done){
        int xrand = rand()%80;
        int yrand = rand()%21;
        if((*m).grid[yrand][xrand]=='.'){
            (*m).pcX=xrand;
            (*m).pcY=yrand;
            done=1;
        } 
    }
    fclose(f);

    //analyzeDistances();
    analyzeDistancesPlus();
    //analyzeDistances();

    
return 0;
}



void printDistanceGrid(){
    int i;
    int j;
    for(i=0;i<21;i++){
        for(j=0;j<80;j++){
            char temp = (*m).grid[i][j];
            if(!(temp=='-' || temp == '|' || temp=='.' || temp=='#')){
                temp=' ';
            }
            if((*m).pcX==j && (*m).pcY==i){
                printf("0");
            }else{
                if((*m).grid[i][j]=='.' || (*m).grid[i][j]=='#'){

                    int num = (*m).distanceGrid[i][j].distance;
                        if(num<10){
                            printf("%i",num);
                        }
                        if(num<62 && num>9){
                            printf("%c",getAsci(num));
                        }
                    
            }else{
                printf("%c",' ');
        }
        }
            
    }
        printf("%c\n",' ');
}
    
}
void printDistanceGridPlus(){
    int i;
    int j;
    for(i=1;i<20;i++){
        for(j=1;j<79;j++){
            char temp = (*m).grid[i][j];
            if((*m).pcX==j && (*m).pcY==i){
                printf("0");
            }else{
                
                int num = (*m).distanceGrid[i][j].distance;

                if(num==10000){

                    printf("%c",(*m).grid[i][j]);
                }else{
                    if(num<10){
                        printf("%i",num);
                    }else{
                        if(num<62 && num>9){
                        printf("%c",getAsci(num));
                            }else{
                            char sample = (*m).grid[i][j];
                            if(sample!='.' && sample!='#'){
                                sample=' ';
                            }
                        printf("%c",sample);
                        }
                    }

                }
                
            }
            
        }
        printf("%c\n",' ');
    }
    
}
