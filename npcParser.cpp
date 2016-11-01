
#include "npcParser.h"
#include <sstream>
using namespace std;
void readFile(){
    ifstream file ("test.txt",std::ifstream::in);
    
    stringstream s;
    s << file.rdbuf();
    string buffer;
    file.close();
    int createMon=0;
    int namei=0;
    int symbi=0;
    int colori=0;
    int desci=0;
    int speedi=0;
    int dami=0;
    int abili=0;
    int hpi=0;
    int error=0;
    s >> buffer;
    s >> buffer;
    s >> buffer;
    while(s >> buffer){
        if(!buffer.compare("BEGIN")){
            if(!createMon){
                string name =" ";
                string symb = " ";
                string color = " ";
                string desc = " ";
                string speed = " ";
                string dam = " ";
                string hp = " ";
                string abil =" ";
                s >> buffer;
                if(!buffer.compare("MONSTER")){
                    s >> buffer;
                    if(!buffer.compare("NAME")){
                       
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            name+=buffer;
                            name+=" ";
                        }else{
                             if(namei){
                            error=1;
                            }else{
                                namei=1;
                                cout << "Read Monster: " << name <<  endl;
                            }
                            break;
                        }
                    }
                    }
                    
                    if(!buffer.compare("SYMB")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            symb+=buffer;
                        }else{
                            if(symbi){
                                error=1;
                            }else{
                                symbi=1;
                                cout << "Read Monster: " << symb <<  endl;
                            }
                            break;
                        }
                        }
                    }
                    
                    if(!buffer.compare("COLOR")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            color+=buffer;
                        }else{
                            if(colori){
                                error=1;
                            }else{
                                colori=1;
                                cout << "Read Monster: " << color <<  endl;
                            }
                            break;
                        }
                        }
                    }
                    
                    if(!buffer.compare("DESC")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            
                            desc+=buffer;
                            desc+=" ";
                        }else{
                             if(desci){
                                 error=1;
                             }else{
                                 desci=1;
                                 cout << "Read Monster: " << desc <<  endl;
                             }
                             
                             break;
                        }
                        }
                    }
                   
                    if(!buffer.compare("SPEED")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            speed+=buffer;
                        }else{
                            if(speedi){
                                error=1;
                            }else{
                                speedi=1;
                                cout << "Read Monster: " << speed <<  endl;
                            }
                            
                            break;
                        }
                        }
                    }
                    if(!buffer.compare("DAM")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            dam+=buffer;
                        }else{
                            if(dami){
                                error=1;
                            }else{
                                dami=1;
                                cout << "Read Monster: " << dam <<  endl;
                            }
                            
                            break;
                        }
                        }
                    }
                    
                    if(!buffer.compare("HP")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            hp+=buffer;
                        }else{
                            if(hpi){
                                error=1;
                            }else{
                                hpi=1;
                                cout << "Read Monster: " << hp <<  endl;
                            }
                            break;
                        }
                        }
                    }
                    
                    if(!buffer.compare("ABIL")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            abil+=buffer;
                        }else{
                            if(abili){
                                error=1;
                            }else{
                                abili=1;
                                cout << "Read Monster: " << abil <<  endl;
                            }
                            
                            break;
                        }
                        }
                    }
                    if(!buffer.compare("END")){
                        if(!error){
                            if(namei && symbi && colori && desci && speedi && dami && abili && hpi){
                                cout << "created" << endl;

                            }else{
                                cout << "Not Created" << endl;
                            }
                        }else{
                            cout << "Not Created" << endl;
                        }
                        createMon=0;
                        namei=0;
                        symbi=0;
                        colori=0;
                        desci=0;
                        speedi=0;
                        dami=0;
                        abili=0;
                        hpi=0;
                        error=0;
                    
                    }
                }
            }
        }
    }

}
int validSyntax(string input){
    if(!input.compare("NAME")){
        return 0;
    }
    if(!input.compare("SYMB")){
        return 0;
    }
    if(!input.compare("COLOR")){
        return 0;
    }
    if(!input.compare("DESC")){
        return 0;
    }
    if(!input.compare("SPEED")){
        return 0;
    }
    if(!input.compare("DAM")){
        return 0;
    }
    if(!input.compare("HP")){
        return 0;
    }
    if(!input.compare("ABIL")){
        return 0;
    }
    if(!input.compare("END")){
        return 0;
    }
    return 1;
}
/*Constructor*/
npcInfo()::npcInfo(string name,string symbol,string color,string desc,string speed,string dam,string hp, string abil){
    this.name=name;
    this.symbol=symbol;
    this.color=getColor(color);
    this.description=desc;
    this.speed = getDice(speed);
    this.dam = getDice(dam);
    this.hp=getDice(hp);

}
Dice::Dice(int ba,int si,int nu){
    srand(time(NULL));
    this.base=ba;
    this.sides=si;
    this.numDice=nu;
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
int getColor(string c){
    if(!c.compare("WHITE")){
        return 0;
    }
    if(!c.compare("RED")){
        return 1;
    }
    if(!c.compare("BLUE")){
        return 2;
    }
    if(!c.compare("YELLOW")){
        return 3;
    }
    if(!c.compare("BLACK")){
        return 4;
    }
    if(!c.compare("GREEN")){
        return 5;
    }
    if(!c.compare("BLUE")){
        return 6;
    }
    if(!c.compare("CYAN")){
        return 7;
    }
    if(!c.compare("MAGENTA")){
        return 8;
    }
}
Dice getDice(string spee){
    int x=0;
    string baseNum;
    while(spee.at(x)!='+'){
        x++;    
    }
    baseNum = spee.substr(0,x);
    int base = std::stoi(spee);
    int y=0;
    while(spee.at(y)!='d'){
        y++;
    }
    string numDice = spee.substr(x+1,(y-1)-x;);
    int numOfDice= stoi(numDice);

    int stringLength = spee.lenght();

    string rolesS = spee.substr(y+1,stringLength-(y+1));
    int sides = stoi(rolesS);
    Dice d(base,sides,numOfDice);

    return d;

}
