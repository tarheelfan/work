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
                s >> buffer;
                if(!buffer.compare("MONSTER"){
                    s >> buffer;
                    if(!buffer.compare("NAME")){

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