#include <stdexcept>
#include "npcParser.h"
#include <sstream>
using namespace std;
void readFile(){
    ifstream file ("test.txt",std::ifstream::in);
    
    stringstream s;
    s << file.rdbuf();
    string buffer;
    int createMon=0;
    file.close();
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
                            cout << "Read Monster: " << name <<  endl;
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
                            cout << "Read Monster: " << symb <<  endl;
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
                            cout << "Read Monster: " << color <<  endl;
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
                             cout << "Read Monster: " << desc <<  endl;
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
                             cout << "Read Monster: " << speed <<  endl;
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
                            cout << "Read Monster: " << dam <<  endl;
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
                            cout << "Read Monster: " << hp <<  endl;
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
                            cout << "Read Monster: " << abil <<  endl;
                            break;
                        }
                        }
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