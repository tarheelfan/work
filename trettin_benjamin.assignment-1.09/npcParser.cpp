#include "npcParser.h"
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include "monsterFactory.h"
using namespace std;

int validSyntaxNPC(string input){
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
    if(!input.compare("HP")){
        return 0;
    }
    if(!input.compare("ABIL")){
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



npcInfo::~npcInfo(){}

/*Constructor*/
npcInfo::npcInfo(){};
npcInfo::npcInfo(string name,string symbol,string color,string desc,string speed,string dam,string hp, string abil){
    this->name=name;
    this->symbol=symbol.at(1);
    this->color=getColorNPC(color);
    this->description=desc;
    this->speed = getDice(speed);
    this->dam = getDice(dam);
    this->hp=getDice(hp);
    this->speed_i = this->speed.roleDice();
    this->hp_i = this->hp.roleDice();
    this->dam_i = this->dam.roleDice();
    this->characteristics = getCharacteristics(abil);
}
int getColorNPC(string c){
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
    if(!c.compare("CYAN")){
        return 6;
    }
    if(!c.compare("MAGENTA")){
        return 7;
    }
    return 0;
}
void npcInfo::printInfo(){
    cout << this->name << endl;
    cout << "Symbol: " << this->symbol << endl;
    unsigned int x;
    int y=0;
    cout << "Description: ";
    for(x=0;x<this->description.size();x++){
        cout << this->description.at(x);
        if((70<y && this->description.at(x)==' ')){
            y=-1;
            cout << endl;
        }
        y++;
    }
    cout << endl;

    cout << "Color Number: " << this->color << endl;
    cout << "Speed: " << this->speed_i << endl;
    cout << "HP: " << hp_i << endl;
    cout << "Damage: " << dam_i << endl;
    cout << "Characteristic Num: " << characteristics << endl;
}

int getCharacteristics(string desc){
    int intelegent=0;
    int telapathic=0;
    int tunnle=0;
    int erratic=0;
    stringstream stream(desc);
    string buffer;
    int character=0;
    while(stream >> buffer){
        boost::algorithm::trim ( buffer );
        if(!buffer.compare("INTELLIGENT")){
            intelegent=1;
        }
        if(!buffer.compare("SMART")){
            intelegent=1;
        }
        if(!buffer.compare("TELEPATHIC")){
            telapathic=1;
        }
        if(!buffer.compare("TUNNEL")){
            tunnle=1;
        }
        if(!buffer.compare("ERRATIC")){
            erratic=1;
        }

        if(intelegent){
            character = character | 1;
        }
        if(telapathic){
            character = character | 2;
        }
        if(tunnle){
            character = character | 4;
        }
        if(erratic){
            character = character | 8;
        }
    }
    return character;
}
Factory factory;
void readFile(){

    vector<npcInfo> monstersD;
    std::vector<npcInfo>::iterator it;
    it = monstersD.begin();

    char *se = getenv("HOME");
    string fileName(se);
    fileName+="/.rlg327/monster_desc.txt";
    ifstream file (fileName.c_str());
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
    if(buffer.compare("RLG327")){
        exit(1);
    }
    s >> buffer;
    if(buffer.compare("MONSTER")){
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
                string symb = " ";
                string color = " ";
                string desc = " ";
                string speed = " ";
                string dam = " ";
                string hp = " ";
                string abil =" ";
                s >> buffer;
                if(!buffer.compare("MONSTER")){
                    createMon=1;

                    namei=0;
                    colori=0;
                    desci=0;
                    speedi=0;
                    dami=0;
                    abili=0;
                    hpi=0;
                    error=0;
                    s >> buffer;
                    int continu=0;
                    while(1){
                    continu=0;
                    if(!buffer.compare("NAME")){
                       continu=1;
                        while(1){
                            if(s >> buffer){
                        if(validSyntaxNPC(buffer)){
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

                    if(!buffer.compare("SYMB")){
                        continu=1;
                        while(1){
                            if(s >> buffer){
                        if(validSyntaxNPC(buffer)){
                            symb+=buffer;
                        }else{
                            if(symbi){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                symbi=1;
                                cout << "Read Monster Symbol : " << symb <<  endl;
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
                        if(validSyntaxNPC(buffer)){
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
                        if(validSyntaxNPC(buffer)){

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

                    if(!buffer.compare("SPEED")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntaxNPC(buffer)){
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
                        if(validSyntaxNPC(buffer)){
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

                    if(!buffer.compare("HP")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntaxNPC(buffer)){
                            hp+=buffer;
                        }else{
                            if(hpi){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                hpi=1;
                                cout << "Read Monster HP: " << hp <<  endl;
                            }
                            break;
                        }
                        }
                    }

                    if(!buffer.compare("ABIL")){
                        continu=1;
                        while(1){
                            if(!(s >> buffer)){
                                cout << "Unexpected End" << endl;
                                break;
                            }
                        if(validSyntaxNPC(buffer)){
                            abil+=buffer;
                            abil+=" ";
                        }else{
                            if(abili){
                                error=1;
                                cout << "Duplicate Not Created" << endl;
                                break;
                            }else{
                                abili=1;
                                cout << "Read Monster Abilities: " << abil <<  endl;
                            }

                            break;
                        }
                        }
                    }
                    if(!buffer.compare("END")){
                        if(!error){
                            if(namei && symbi && colori && desci && speedi && dami && abili && hpi){
                                cout << "created" << endl;
                                npcInfo i(name,symb,color,desc,speed,dam,hp,abil);
                                cout << "Object Info: " << endl;
                                i.printInfo();
                                it = monstersD.insert(it,i);

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
                        break;
                    }
                    if(!continu){
                        cout << "Not Created" << endl;
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
                        break;
                    }
                    }
                }
            }
        }
    }
    if(monstersD.size()>0){
        factory.locked(monstersD);
    }

}
