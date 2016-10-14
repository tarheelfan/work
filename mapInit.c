#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "gameMap.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <endian.h>
#include <stdint.h>
#include <sys/stat.h>
#include <limits.h>
#include <ncurses.h>

int const x = 80;
int const y = 21;
#define DUNGEON_X 80
#define DUNGEON_Y 21
#define mappair(pair) ((*m).grid[pair[dim_y]][pair[dim_x]])
#define mapxy(x, y) ((*m).grid[y][x])
#define hardnesspair(pair) ((*m).hardness[pair[dim_y]][pair[dim_x]])
#define hardnessxy(x, y) ((*m).hardness[y][x])

Map *m;
int numberOfMonster;
static int getWeight(int num);
static Room* createRoom(void);
static void initRooms(void);
static void initBorder(void);
struct xy;
static int collides(Room *r,Room *ma,int s);
static int contains(Room *r,Room *ro);
static struct xy getCoords();
static char getAsci(int num);
static void analyzeDistancesPlus(void);

WINDOW *window;
struct xy{
    int x;
    int y;
};
int32_t compare_monster(const void *key,const void *with){
    int32_t first = (*(const Monster *) key).roundVal;
    int32_t second = (*(const Monster *) with).roundVal;
    return first - second;
}
void playGame(){
    int done = 0;
    binheap_t heap;
    binheap_init(&heap,compare_monster,free);
        initMonsterLib(m, numberOfMonster);
        /*Setup Monsters*/
        int x;
        for(x=0;x<numberOfMonster;x++){
            struct xy coords;
            coords = (getCoords());
            int isPlay=0;
            if(x==0){
                isPlay=1;
            }
            Monster *monster;
            monster = MonsterInit(m,coords.x,coords.y,isPlay);
            
            if(!x){
                m->thePlayer=monster;
            }
           
            binheap_insert(&heap,monster);
        }
    while(!done){
       
        Monster *tem;
        tem = (Monster*)binheap_remove_min(&heap);
        if((*tem).thePlayer){
            if(!tem->alive){
                printf("DEAD");
                return;
            }else{
                if(binheap_peek_min(&heap)==NULL){
                    printf("VICTORY");
                    return;
                }
            }
        }
        analyzeDistances();
        analyzeDistancesPlus();
        if((*tem).alive){
            performAction(tem);
            tem->roundVal= tem->roundVal + tem->speed;
        }
        if((*tem).alive){
            binheap_insert(&heap,tem);
        }else{
            deconstructor(tem);
        }
        printGrid();
        wrefresh(window);
        clear();
        
    }
}

static struct xy getCoords(){
    struct xy coords;
    int x;
    int y;
    while(1){
     y = (rand()%18)+1;
     x = (rand()%78)+1;
    if((*m).grid[y][x]==('#') || (*m).grid[y][x]==('.')){
        if(monsterArray[y][x]==NULL){
        coords.x=x;
        coords.y=y;
        return coords;
        }
    }
}
        
    
    return coords;
} 
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
    (*m).distanceGrid[(*m).thePlayer->yloc][(*m).thePlayer->xloc].distance=0;
    binheap_t heap;
    binheap_init(&heap,compare_cell,free);
    
    distanceCell root = (*m).distanceGrid[(*m).thePlayer->yloc][(*m).thePlayer->xloc];
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


Room* pointContains(int y,int x){
    int xt;
     Room *temp;
    int number = m->numOfRooms;
    for(xt=0;xt<number;xt++){
       
        temp = &(m->rooms[xt]);
        if(y>=temp->topLeft[2]){
            if(y<=temp->bottomLeft[2]){
                if(x>=temp->topLeft[1]){
                    if(x<=temp->topright[1]){
                        return temp; 
                    }
                }
            }
        }
    }
    return NULL;
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
/*nonTunnelingDistanceGrid - gonna use this*/
 void analyzeDistances(void){
    int xPre;
    int yPre;
    for(xPre=0;xPre<80;xPre++){
        for(yPre=0;yPre<21;yPre++){
            distanceCell pass;
            pass.distance=1000;
            pass.yloc=yPre;/* 1000 will represent infinity */
            pass.xloc=xPre; 
            (*m).nonTunnelingDistanceGrid[yPre][xPre]=pass; 
        }
    }
    (*m).nonTunnelingDistanceGrid[(*m).thePlayer->yloc][(*m).thePlayer->xloc].distance=0;
    binheap_t heap;
    binheap_init(&heap,compare_cell,free);
    distanceCell root = (*m).nonTunnelingDistanceGrid[(*m).thePlayer->yloc][(*m).thePlayer->xloc];
    root.distance=0;
    binheap_insert(&heap,&root);
    int tempx;
    int tempy;
    while(!binheap_is_empty(&heap)){
        distanceCell *temp;
        temp =(distanceCell*) binheap_remove_min(&heap);
        tempx = (*temp).xloc;
        tempy = (*temp).yloc;
        if((*m).grid[(*temp).yloc-1][(*temp).xloc]=='.' || (*m).grid[(*temp).yloc-1][(*temp).xloc]=='#'){/* top */
                if((*m).nonTunnelingDistanceGrid[tempy-1][tempx].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy-1][tempx].distance=(*temp).distance+1;
                    distanceCell *temp0;
                    temp0 = &(*m).nonTunnelingDistanceGrid[tempy-1][tempx];
                    binheap_insert(&heap, temp0);
            }
        } 
         if((*m).grid[(*temp).yloc+1][(*temp).xloc]=='.' || (*m).grid[(*temp).yloc+1][(*temp).xloc]=='#'){/* bottom */
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy+1][tempx].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy+1][tempx].distance=(*temp).distance+1;
                    distanceCell *temp1;
                    temp1 = &(*m).nonTunnelingDistanceGrid[tempy+1][tempx];
                    binheap_insert(&heap,temp1);
                }
        } 
         if((*m).grid[(*temp).yloc][(*temp).xloc+1]=='.' || (*m).grid[(*temp).yloc][(*temp).xloc+1]=='#'){/* right */
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy][tempx+1].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp2;
                    temp2 = &(*m).nonTunnelingDistanceGrid[tempy][tempx+1];
                    binheap_insert(&heap,temp2);
                }
        } 
         if((*m).grid[(*temp).yloc][(*temp).xloc-1]=='.' || (*m).grid[(*temp).yloc][(*temp).xloc-1]=='#'){/* left */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy][tempx-1].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy][tempx-1].distance=(*temp).distance+1;
                    distanceCell *temp3;
                    temp3 = &(*m).nonTunnelingDistanceGrid[tempy][tempx-1];
                    binheap_insert(&heap,temp3);
                    
                }
        }
        if((*m).grid[(*temp).yloc-1][(*temp).xloc+1]=='.' || (*m).grid[(*temp).yloc-1][(*temp).xloc+1]=='#'){/* top right */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy-1][tempx+1].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy-1][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp4;
                    temp4 = &(*m).nonTunnelingDistanceGrid[tempy-1][tempx+1];
                    binheap_insert(&heap,temp4);   
                }            
        }
        if((*m).grid[(*temp).yloc-1][(*temp).xloc-1]=='.' || (*m).grid[(*temp).yloc-1][(*temp).xloc-1]=='#'){/* top left */
           
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy-1][tempx-1].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy-1][tempx-1].distance=(*temp).distance+1;
                    distanceCell *temp5;
                    temp5 = &(*m).nonTunnelingDistanceGrid[tempy-1][tempx-1];
                   binheap_insert(&heap,temp5);
                }
        }
        if((*m).grid[(*temp).yloc+1][(*temp).xloc-1]=='.' || (*m).grid[(*temp).yloc+1][(*temp).xloc-1]=='#'){/* bottomLeft left */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy+1][tempx-1].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy+1][tempx-1].distance=(*temp).distance+1;
                    distanceCell *temp6;
                    temp6 = &(*m).nonTunnelingDistanceGrid[tempy+1][tempx-1];
                    binheap_insert(&heap,temp6);
                    
                }

            
        }
        if((*m).grid[(*temp).yloc+1][(*temp).xloc+1]=='.' || (*m).grid[(*temp).yloc+1][(*temp).xloc+1]=='#'){/* bottom right */
            
                tempx = (*temp).xloc;
                tempy = (*temp).yloc;
                if((*m).nonTunnelingDistanceGrid[tempy+1][tempx+1].distance==1000){
                    (*m).nonTunnelingDistanceGrid[tempy+1][tempx+1].distance=(*temp).distance+1;
                    distanceCell *temp7;
                    temp7 = &(*m).nonTunnelingDistanceGrid[tempy+1][tempx+1];
                    binheap_insert(&heap,temp7);
                }
        }
    }
}

int initMap(int numOfMonster){
    initscr(); /*starts curses mode*/
    window = newwin(21,80,0,0); /*Creates Window*/
    numberOfMonster=numOfMonster;
    m = (Map*)malloc(sizeof(Map));
   
    initBorder();
    initRooms();
    int done=0;
    while(!done){
        int xrand = rand()%80;
        int yrand = rand()%21;
        if((*m).grid[yrand][xrand]=='.'){
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
    return 0;
}

 void printGrid(){
    int i;
    int j;
    for(i=0;i<21;i++){
        for(j=0;j<80;j++){
            char temp[1];
            temp[0] = (*m).grid[i][j];
            if(!(temp[0]=='-' || temp[0] == '|' || temp[0]=='.' || temp[0]=='#')){
                temp[0] = ' ';
            }
            Monster *tempMon;
            tempMon = monsterArray[i][j];
               
                if(tempMon!=NULL){
                    if(tempMon->bigPeople){
                        mvwprintw(window,i,j,"P");
                    }
                    if(tempMon->dragon){
                        mvwprintw(window,i,j,"D");
                    }
                    if(tempMon->thePlayer){
                        mvwprintw(window,i,j,"@");
                    }
                    if(tempMon->other){
                        mvwprintw(window,i,j,"p");
                    }
            }else{
                mvwprintw(window,i,j,temp);
            }
            
        }
        //mvprintw(window,i,j,'\n');
    }
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
            if((*m).thePlayer->xloc==j && (*m).thePlayer->yloc==i){
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
            if((*m).thePlayer->yloc==j && (*m).thePlayer->yloc==i){
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
