#ifndef KnowledgeMapHeader
#define KnowledgeMapHeader

#ifdef __cplusplus
#include "gameMap.h"

class KnowledgeMap {
    public:
        KnowledgeMap();
        ~KnowledgeMap();
        char getCharC(int x,int y);
        void setCharC(int x,int y,char val);
        void setMap(Map* map);
        Map* map;
        char grid[21][80];
    
        
};

extern "C"{

#endif

void linkMapandMapI(Map* ma);
char getCharI(void* s,int x,int y);
void setCharI(int x,int y,char val);
void updateKnowledgeMap(void* s);

# ifdef __cplusplus
}

#endif

#endif