#include "objectParser.h"
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include "monsterFactory.h"
using namespace std;

int validSyntax(string input){
    boost::algorithm::trim(input);
    if(!input.size()){
        return 0;
    }
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
    if(!input.compare("TYPE")){
        return 0;
    }
    if(!input.compare("ABIL")){
        return 0;
    }
    if(!input.compare("ATTR")){
        return 0;
    }
    if(!input.compare("SPEED")){
        return 0;
    }
    if(!input.compare("HIT")){
        return 0;
    }
    if(!input.compare("DEF")){
        return 0;
    }
    if(!input.compare("ABIL")){
        return 0;
    }
    if(!input.compare("VAL")){
        return 0;
    }
    if(!input.compare("DODGE")){
        return 0;
    }
    if(!input.compare("WEIGHT")){
        return 0;
    }
    if(!input.compare("END")){
        return 0;
    }
    if(!input.compare(".")){
        return 0;
    }
    return 1;
}

Dice::Dice(int ba,int si,int nu){
    srand(time(NULL));
    this->base=ba;
    this->sides=si;
    this->numDice=nu;
}
Dice::Dice(){

}
objectInfo::~objectInfo(){}
Dice::~Dice(){}
/*Constructor*/
objectInfo::objectInfo(){};
objectInfo::objectInfo(string name,string type,string weight,string color,string dodge,string val, string dam,string def, string hit,string speed, string desc, string attr){
    this->name= name;

    this->type=getType(type);

    this->weight= getDice(weight).roleDice();

    this->color = getColor(color);

    this->dodge = getDice(dodge);

    this->value = getDice(val).roleDice();

    this->dam = getDice(dam);

    this->def = getDice(def);

    this->hit = getDice(hit);

    this->speed = getDice(speed);

    this->desc = desc;

    this->attr = getDice(attr).roleDice();

}
int getType(string color){
    if(!color.compare("LIGHT")){
        return 0;
    }
    if(!color.compare("RING")){
        return 1;
    }
    if(!color.compare("WEAPON")){
        return 2;
    }
    if(!color.compare("OFFHAND")){
        return 3;
    }
    if(!color.compare("RANGED")){
        return 4;
    }
    if(!color.compare("ARMOR")){
        return 5;
    }
    if(!color.compare("HELMET")){
        return 6;
    }
    if(!color.compare("CLOAK")){
        return 7;
    }
    if(!color.compare("GLOVES")){
        return 8;
    }
    if(!color.compare("BOOTS")){
        return 9;
    }
    if(!color.compare("AMULET")){
        return 10;
    }
    if(!color.compare("SCROLL")){
        return 11;
    }
    if(!color.compare("BOOK")){
        return 12;
    }
    if(!color.compare("FLASK")){
        return 13;
    }
    if(!color.compare("GOLD")){
        return 14;
    }
    if(!color.compare("AMMUNITION")){
        return 15;
    }
    if(!color.compare("FOOD")){
        return 16;
    }
    if(!color.compare("WAND")){
        return 17;
    }
    if(!color.compare("CONTAINER")){
        return 18;
    }
    if(!color.compare("STACK")){
        return 19;
    }

    return -1;
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
    boost::algorithm::trim(c);
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
    return 0;
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
void readFileObjects(){
    char *se = getenv("HOME");
    string fileName(se);
    fileName+="/302/work/trettin_benjamin.assignment-1.08/rlg327/object_desc.txt";
    ifstream file (fileName.c_str());

    vector<objectInfo> obs;
    std::vector<objectInfo>::iterator it;
    it = obs.begin();

    stringstream s;
    s << file.rdbuf();
    string buffer;
    file.close();
    int createMon=0;
    int namei=0;
    int typei=0;
    int colori=0;
    int desci=0;
    int speedi=0;
    int dami=0;
    int hiti=0;
    int defi=0;
    int error=0;
    int dodgei=0;
    int vali=0;
    int weighti =0;
    int attri=0;
    s >> buffer;
    if(buffer.compare("RLG327")){
        exit(1);
    }
    s >> buffer;
    if(buffer.compare("OBJECT")){
        exit(1);
    }
    s >> buffer;
    if(buffer.compare("DESCRIPTION")){
        exit(1);
    }
    s >> buffer;
    if(buffer.compare("1")){
        exit(1);
    }

    while(s >> buffer){
        if(!buffer.compare("BEGIN")){
            if(!createMon){
                string name =" ";
                string type = " ";
                string color = " ";
                string desc = " ";
                string speed = " ";
                string dam = " ";
                string hp = " ";
                string abil =" ";
                string value= " ";
                string weight=" ";
                string dodge = " ";
                string def = " ";
                string hit = " ";
                string attr = " ";
                s >> buffer;

                if(!buffer.compare("OBJECT")){
                    createMon=1;

                    namei=0;
                    typei=0;
                    colori=0;
                    desci=0;
                    speedi=0;
                    dami=0;
                    hiti=0;
                    defi=0;
                    error=0;
                    dodgei=0;
                    vali=0;
                    weighti =0;
                    attri=0;

                    s >> buffer;
                    int continu=0;
                    while(1){
                    continu=0;
                    if(!buffer.compare("NAME")){
                       continu=1;
                        while(1){
                            if(s >> buffer){
                        if(validSyntax(buffer)){
                            name+=buffer;
                            name+=" ";
                        }else{
                             if(namei){
                            error=1;
                            cout << "Duplicate Not Created" << endl;
                            break;
                            }else{
                                namei=1;
                                cout << "Read Monster Name : " << name <<  endl;
                            }
                            break;
                        }
                    }else{
                            cout << "Unexpected End" << endl;
                            break;
                        }
                        }
                    }

                    if(!buffer.compare("TYPE")){
                        continu=1;
                        while(1){
                            if(s >> buffer){
                        if(validSyntax(buffer)){
                            type+=buffer;
                        }else{
                            if(typei){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                typei=1;
                                cout << "Read Monster Symbol : " << type <<  endl;
                            }
                            break;
                        }
                            }else{
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        }
                    }

                    if(!buffer.compare("COLOR")){
                        continu=1;
                        while(1){
                            if(s >> buffer){
                        if(validSyntax(buffer)){
                            color+=buffer;
                        }else{
                            if(colori){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                colori=1;
                                cout << "Read Monster Color: " << color <<  endl;
                            }
                            break;
                        }
                            }else{
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        }
                    }

                    if(!buffer.compare("DESC")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){

                            desc+=buffer;
                            desc+=" ";
                        }else{
                             if(!buffer.compare(".")){
                                 s >> buffer;
                             }
                             if(desci){
                                 error=1;
                                 cout << "Duplicate Not Created" << endl;
                                break;
                             }else{
                                 desci=1;
                                 unsigned int x;
                                 int y=0;
                                 cout << "Read Monster Description: ";
                                 for(x=0;x<desc.size();x++){
                                     cout << desc.at(x);
                                     if((70<y && desc.at(x)==' ')){
                                         y=-1;
                                         cout << endl;
                                     }
                                    y++;
                                 }
                                 cout << endl;
                             }

                             break;
                        }
                        }
                    }

                    if(!buffer.compare("VAL")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            value+=buffer;
                        }else{
                            if(vali){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                vali=1;
                                cout << "Read Monster Speed: " << value <<  endl;
                            }

                            break;
                        }
                        }
                    }
                    if(!buffer.compare("DODGE")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            dodge+=buffer;
                        }else{
                            if(speedi){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                dodgei=1;
                                cout << "Read Monster Speed: " << dodge <<  endl;
                            }

                            break;
                        }
                        }
                    }
                    if(!buffer.compare("WEIGHT")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            weight+=buffer;
                        }else{
                            if(weighti){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                weighti=1;
                                cout << "Read Monster Speed: " << weight <<  endl;
                            }

                            break;
                        }
                        }
                    }


                    if(!buffer.compare("SPEED")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            speed+=buffer;
                        }else{
                            if(speedi){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                speedi=1;
                                cout << "Read Monster Speed: " << speed <<  endl;
                            }

                            break;
                        }
                        }
                    }
                    if(!buffer.compare("DAM")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            dam+=buffer;
                        }else{
                            if(dami){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                dami=1;
                                cout << "Read Monster Damage: " << dam <<  endl;
                            }

                            break;
                        }
                        }
                    }
                    if(!buffer.compare("ATTR")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            attr+=buffer;
                        }else{
                            if(attri){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                attri=1;
                                cout << "Read Monster Damage: " << attr <<  endl;
                            }

                            break;
                        }
                        }
                    }

                    if(!buffer.compare("DEF")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            def+=buffer;
                        }else{
                            if(defi){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                defi=1;
                                cout << "Read Monster HP: " << def <<  endl;
                            }
                            break;
                        }
                        }
                    }

                    if(!buffer.compare("HIT")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntax(buffer)){
                            hit+=buffer;
                        }else{
                            if(hiti){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                hiti=1;
                                cout << "Read Monster Abilities: " << hit <<  endl;
                            }

                            break;
                        }
                        }
                    }
                    if(!buffer.compare("END")){
                        if(!error){
                            if(namei && typei && colori && desci && speedi && dami && hiti && defi && dodgei && vali && weighti && attri){
                                    cout << "created" << endl;
                                    boost::algorithm::trim(name);
                                    boost::algorithm::trim(type);
                                    boost::algorithm::trim(weight);
                                    boost::algorithm::trim(color);
                                    boost::algorithm::trim(dodge);
                                    boost::algorithm::trim(value);
                                    boost::algorithm::trim(dam);
                                    boost::algorithm::trim(def);
                                    boost::algorithm::trim(hit);
                                    boost::algorithm::trim(speed);
                                    boost::algorithm::trim(desc);
                                    boost::algorithm::trim(attr);
                                    objectInfo i(name,type,weight,color,dodge,value,dam, def,hit,speed,desc,attr);
                                    cout << endl;
                                    it = obs.insert(it,i);

                            }else{
                                cout << "Not Created" << endl;
                            }
                        }else{
                            cout << "Not Created" << endl;
                        }
                        createMon=0;
                        namei=0;
                        typei=0;
                        colori=0;
                        desci=0;
                        speedi=0;
                        dami=0;
                        hiti=0;
                        defi=0;
                        error=0;
                        dodgei=0;
                        vali=0;
                        weighti =0;
                        attri=0;
                        break;
                    }
                    if(!continu){
                        cout << "Not Created" << endl;
                        createMon=0;
                        namei=0;
                        typei=0;
                        colori=0;
                        desci=0;
                        speedi=0;
                        dami=0;
                        hiti=0;
                        defi=0;
                        error=0;
                        dodgei=0;
                        vali=0;
                        weighti =0;
                        attri=0;
                        break;
                    }
                    }
                }
            }
        }
    }
    if(obs.size()>0){
        factory.loaded(obs);
    }
}
