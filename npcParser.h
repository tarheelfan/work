#include<iostream>
#include<fstream>
#include <string>
#include <vector>

class npcInfo {
    private:
        std::string name;
        std::string description;
        int color;
        int speed;
        int hp;
        int dam;
    public:
    npcInfo(char* filename);
    ~npcInfo();
    
};
int validSyntax(std::string input);
void readFile();