#ifndef PLAYER_DEF
#define PLAYER_DEF
#include "VisibleGameObject.h"
#include "Animation.h"

class Player : public VisibleGameObject{
public:
    Player(std::string fName, sf::Keyboard::Key _u, sf::Keyboard::Key _l, sf::Keyboard::Key _r);
    ~Player();

    void Update(float elapsedTime,sf::Event& _event);

    float GetVelocity() const;

private:
    sf::Keyboard::Key u;
    sf::Keyboard::Key l;
    sf::Keyboard::Key r;
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
