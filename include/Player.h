#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"
#include "Animation.h"

class Player : public VisibleGameObject{
public:
    Player(std::string fName);
    ~Player();

    void Update(float elapsedTime,sf::Event& _event);

    float GetVelocity() const;

private:
    bool isUpPressed;
    bool isLPressed;
    bool isRPressed;
    bool isJumping;
    float dJump;
    float _velocity;  // -- left ++ right
    float _maxVelocity;
    Animation animation;
};
#endif // PLAYER_H
