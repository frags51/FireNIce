#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"
#include "Animation.h"
#include "Collision.h"

class Player : public VisibleGameObject{
public:
    Player(std::string fName);
    ~Player();

    void Update(float elapsedTime,sf::Event& _event);

    float GetVelocity() const;
    Collision GetCollider(){return Collision(_player);}

private:
    bool isJumping;
    float dJump;
    float _velocity;  // -- left ++ right
    float _maxVelocity;
    Animation animation;
};
#endif // PLAYER_H
