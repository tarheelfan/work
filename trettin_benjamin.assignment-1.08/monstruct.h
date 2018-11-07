struct ilist{
    int directions[1000];
    int size;
};
typedef struct{
     struct ilist directions;
     int thePlayer;
     int bigPeople;
     int dragon;
     int other;
     unsigned int characteristics : 4; /*Intel,Telapath,Tunneling,Erratic*/
     void* monsterC;
     int alive;
     int xloc;
     int yloc;
     int modelNumber;
     unsigned int roundVal;
     int speed;
     int patrolMode;
     int searchLocationX;
     int searchLocationY;
}iMonster;