#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"

class Player : public VisibleGameObject{
public:
    Player();
    ~Player();
    void set_size();

};

#endif