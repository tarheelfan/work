#include "dice.h"
using namespace std;
Dice::Dice(int ba,int si,int nu){
    srand(time(NULL));
    this->base=ba;
    this->sides=si;
    this->numDice=nu;
}
Dice::~Dice(){}
Dice::Dice(){

}
int Dice::roleDice(){
    int x;
    int total=0;
    for(x=0;x<numDice;x++){
        int num = rand() % sides;
        num++;
        total+=num;
    }
    total+=base;
    return total;
}
Dice getDice(string spee){
    int x=0;
    string baseNum;
    while(spee.at(x)!='+'){
        x++;    
    }
    baseNum = spee.substr(0,x);
    int base = atoi(spee.c_str());
    int y=0;
    while(spee.at(y)!='d'){
        y++;
    }
    string numDice = spee.substr(x+1,(y-1)-x);
    int numOfDice= atoi(numDice.c_str());

    int stringLength = spee.length();

    string rolesS = spee.substr(y+1,stringLength-(y+1));
    int sides = atoi(rolesS.c_str());
    Dice d(base,sides,numOfDice);

    return d;

}