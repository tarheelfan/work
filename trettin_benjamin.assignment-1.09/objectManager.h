#ifndef ITEMs
#define ITEMs
#include "dice.h"
#include <vector>

using namespace std;
class Item{
    public:
    inline Item(){}
    inline ~Item(){}
    inline int getType(){
        return type;
    }
    Item(int type,int weight,int color,Dice dodge, int value,Dice dam, int def,int hit,int speed, string desc, int attr );
    void copy(Item t);
    private:
        int type;  
        int weight;
        int color;
        int dodge;
        int value;
        Dice dam;
        int def;
        int hit;
        int speed;
        string desc;
        int attr;
};
char getCharacter(int x, int y);
vector<Item> getItem(int x, int y);
Item searchItem(int x, int y);


#endif