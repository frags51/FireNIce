#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"

class Player : public VisibleGameObject{
public:
    Player();
    ~Player();
    void set_size();
    void updateMovement();

public:
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;
    float gravity;
};
#endif // PLAYER_H
