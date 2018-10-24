# ifndef MONS
# define MONS

#ifdef __cplusplus
#include "gameMap.h"
class MonsterClass {

    public:
          ~MonsterClass();
          MonsterClass(int x, int y,int isPlayer);
          MonsterClass(Monster* st);
          Monster *monster;
          int moveUpC();
          int moveDownC();
          int moveRightC();
          int moveLeftC();
          int moveTopRightC();
          int moveTopLeftC();
          int moveBottomLeftC();
          int moveBottomRightC();
          int isAliveC();
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
          struct list directions;
          void initList();
          void addToList(int num);
          void reset();
          int removeFromList();
          int thePlayerC();
          void setRoundValC();
};

#include "monstruct.h"
extern "C" {
  
#endif
  int thePlayerI(void* s);
  int isAliveI(void* s);
  int moveUpI(void* s);
  int moveDownI(void* s);
  int moveRightI(void* s);
  int moveLeftI(void* s);
  int moveTopRightI(void* s);  
  int moveTopLeftI(void* s);
  int moveBottomLeftI(void* s);
  int moveBottomRightI(void* s);
  int isIntelegentI(void* s);
  int isTelapathicI(void* s);
  int canTunnleI(void* s);
  int isErraticI(void* s);
  void performActionI(void* s);
  void readDirectionsI(void* s);
  void getDirectionsTunnelingI(void* s);
  void getDirectionsI(void* s);
  void performWanderI(void* s);
  void moveNearestNonTunnelingI(void* s);
  void moveNearestTunnelingI(void* s);
  int scanAreaI(void* s);
  void setRoundValI(void* s);
  void* linkClass(int x, int y, int isPlayer);
void* getObj(Monster* s);
void decoStructorI(void* s);
#ifdef __cplusplus
}

#endif

#endif