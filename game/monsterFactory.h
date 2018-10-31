#include <vector>
#include "npcParser.h"
#include "objectParser.h"
#include "gameMap.h"

using namespace std;
/*let off some steam bennett*/
class Factory{
    public:
        Factory();
        ~Factory();
        void locked(vector<npcInfo> v);
        /*and*/
        void loaded(vector<objectInfo> v);
        Monster* getMon(Map *map,int x,int y,int isPlayer);
    private:
        int numOfMonsters;
        vector<npcInfo> monstersD;
        vector<objectInfo> objectD;
};

extern Factory factory;
 