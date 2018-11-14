#include "objectManager.h"
#include "gameMap.h"

 static char convertType(int ty);
 Item::Item(string name,int type,int weight,int color,Dice dodge, int value,Dice dam, int def,int hit,int speed, string desc, int attr ){
        this->name=name;
        this->type=type;
        this->weight = weight;
        this->color= color;
        this->dodge = dodge.roleDice();
        this->value=value;
        this->dam = dam;
        this->def = def;
        this->hit=hit;
        this->speed=speed;
        this->desc = desc;
        this->attr = attr;    
    }
void Item::copy(Item t){
    this->type=t.type;
    this->weight=t.weight;
    this->color=t.color;
    this->dodge=t.dodge;
    this->value=t.value;
    this->dam=t.dam;
    this->def=t.def;
    this->hit=t.hit;
    this->speed=t.speed;
    this->desc=t.desc;
    this->attr=t.attr;
}
/*Returns 0 if nothing was found*/
char getCharacter(int x, int y){
    if(itemGrid[x][y].size()>0){
        if(itemGrid[x][y].size()==1){
            int ty = (itemGrid[x][y]).at(0).getType();
            return convertType(ty);
        }
        if(itemGrid[x][y].size()>1){
            return '&';
        }
    }
        return '0';   
}
Item searchItem(int x, int y){
    int size = itemGrid[x][y].size();
    size--;
    Item temps = itemGrid[x][y].at(size);
    itemGrid[x][y].erase(itemGrid[x][y].begin()+size);
    return temps;
}



static char convertType(int ty){
    switch(ty){
        case 0:
            return '_';
        break;
        case 1:
            return '=';
        break;
        case 2:
            return '|';
        break;
        case 3:
            return ')';
        break;
        case 4:
            return '}';
        break;
        case 5:
            return '[';
        break;
        case 6:
            return ']';
        break;
        case 7:
            return '(';
        break;
        case 8:
            return '{';
        break;
        case 9:
            return '\\' ; 
        break;
        case 10:
            return '"';
        break;
        case 11:
            return '~';
        break;
        case 12:
            return '?';
        break;
        case 13:
            return '!';
        break;
        case 14:
            return '$';
        break;
        case 15:
            return '/';
        break;
        case 16:
            return ',';
        break;
        case 17:
            return '-';
        break;
        case 18:
            return '%';
        break;
        /*If this occures then there is an error*/
        default :
            return '*';
        break;

    }
}
