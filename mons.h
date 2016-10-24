#include "monstruct.h"


class MonsterClass {

    public:
          ~MonsterClass();
          MonsterClass(int x, int y,int isPlayer);
          int moveUpC();
          int moveDownC();
          int moveRightC();
          int moveLeftC();
          int moveTopRightC();
          int moveTopLeftC();
          int moveBottomLeftC();
          int moveBottomRightC();
          int isIntelegentC();
          int isTelapathicC();
          int canTunnleC();
          int isErraticC();
          void performActionC();
          void deconstructorC();
          void readDirectionsC();
          void getDirectionsTunnelingC();
          void getDirectionsC();
          void performWanderC();
          void moveNearestNonTunnelingC();
          int scanAreaC();
          void moveNearestTunnelingC();
    
        iMonster *monster;
        struct ilist directions;
        void initList();
        void addToList(int num);
        void reset();
        int removeFromList();
        int thePlayer;
        int bigPeople;
        int dragon;
        int other;
        unsigned int characteristics : 4; /*Intel,Telapath,Tunneling,Erratic*/
        int alive;
        int xloc;
        int yloc;
        int modelNumber;
        unsigned int roundVal;
        int speed;
        int patrolMode;
        int searchLocationX;
        int searchLocationY;
        private:
};

