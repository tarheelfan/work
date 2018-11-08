#include "knowledgeMap.h"
#include "gameMap.h"

using namespace std;
/*Constructor*/
KnowledgeMap::KnowledgeMap(){
    int x,y;
    for(x=0;x<21;x++){
        for(y=0;y<80;y++){
            grid[x][y]=' ';
        }
    }
}
/*Deconstructor*/
KnowledgeMap::~KnowledgeMap(){}
 
void KnowledgeMap::setMap(Map* map){
     this->map=map;
 }
/*C++ Method*/
char KnowledgeMap::getCharC(int x,int y){
    char temp = grid[x][y];
    return temp;
}

/*C interface*/
char getCharI(void* s,int x,int y){
     KnowledgeMap* t = (KnowledgeMap*) s;
     return t->getCharC(x,y);
}
/*C++ Method*/
void KnowledgeMap::setCharC(int x,int y,char val){
    grid[x][y]=val;
}

/*C interface*/
void setCharI(void* s,int x,int y,char val){
    KnowledgeMap* t = (KnowledgeMap*) s;
    t->setCharC(x,y,val);
}

void linkMapandMapI(Map* ma){
    KnowledgeMap* t = new KnowledgeMap();
    t->setMap(ma);
    ma->knowledgeMap=(void*) t;
}

void updateKnowledgeMap(void* s){
    KnowledgeMap* t = (KnowledgeMap*) s;
    int xlocal = m->thePlayer->xloc;
    int ylocal = m->thePlayer->yloc;
    int x,y;
    for(x=xlocal-3;x<=xlocal+3;x++){
        for(y=ylocal-3;y<=ylocal+3;y++){
            if(x>=0 && x<80){
                if(y>=0 && y<21){
                    t->setCharC(y,x,m->grid[y][x]);    
                }
            }
        }
    }
}