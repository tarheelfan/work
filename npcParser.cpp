#include <stdexcept>
#include "npcParser.h"

void readFile(){
    ifstream file ("test.txt");
    stringstream s;
    s << file;
    string buffer;
    int createMon=0;
    while(s >> buffer){
        if(!buffer.compare("BEGIN")){
            if(!createMon){
                string name;
                string symb;
                string color;
                string desc;
                string speed;
                string dam;
                string hp;
                string abil;
                s >> buffer;
                if(!buffer.compare("MONSTER"){
                    s >> buffer;
                    if(!buffer.compare("NAME")){
                        while(1){
                            s >> buffer;
                        if(validSyntax(buffer)){
                            name=buffer;
                        }else{
                            break;
                        }
                    }
                    }
                    if(!buffer.compare("SYMB")){

                    }
                    if(!buffer.compare("COLOR")){

                    }
                    if(!buffer.compare("DESC")){

                    }
                    if(!buffer.compare("SPEED")){

                    }
                    if(!buffer.compare("DAM")){

                    }
                    if(!buffer.compare("HP")){

                    }
                    if(!buffer.compare("ABIL")){

                    }
                    if(!buffer.compare("END")){
                        createMon=0;
                        /*Create Monster Here*/
                    }
                }else{
                    throw std::invalid_argument( "Incorrect File Format");
                }
            }else{
                throw std::invalid_argument( "Incorrect File Format");
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