#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"

class Player : public VisibleGameObject{
public:
    Player();
    ~Player();
    void set_size();

    void Update(float elapsedTime);

    float GetVelocity() const;

private:
    float _velocity;  // -- left ++ right
    float _maxVelocity;
};
#endif // PLAYER_H
