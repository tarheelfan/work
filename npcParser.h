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
        std::vector<unsinged int>
        int hp;
        int dam;
    public:
    npcInfo(char* filename);
    ~npcInfo();
    
}
int notDesc(std::string word);
void readFile();