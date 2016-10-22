class MonsterClass {

    public:
          Monster();
          ~Monster();
          int moveUpC();
          int moveDownC();
          int moveRightC();
          int moveLeftC();
          int moveTopRightC();
          int moveTopLeftC();
          int moveBottomLeftC();
          int moveBottomRightC();
          int isIntelegent();
          int isTelapathic();
          int canTunnle();
          int isErratic();
          void performAction();
          void deconstructor();
          void readDirectionsC();
          void getDirectionsTunnelingC();
          void getDirectionsC();
          void performWanderC();
          void moveNearestNonTunnelingC();
          int scanAreaC();
          void moveNearestTunnelingC();
    private:
        Monster *monster;
        struct list directions;
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
};