#include "Player.h"
#include "GameState.h"
Player::Player(const std::string &fName, sf::Keyboard::Key _u, sf::Keyboard::Key _l, sf::Keyboard::Key _r) :
        _velocity(0),
        _maxVelocity(600.0f),
        dJump {0.f},
        isRPressed{false},
        isLPressed{false},
        isUpPressed{false},
        u{_u},
        l{_l},
        r{_r},
        _xVal {550.f},
        _upVel {550.f}

{
    Load(fName, GameState::_resX/16,GameState::_resY/8);
    animation.create(&playerTexture,sf::Vector2u(3,9),0.3f);
    isJumping=false;

}


Player::~Player() {

}


float Player::GetVelocity() const
{
    return _velocity;
}

void Player::Update(float elapsedTime,sf::Event& _event)
{
    int row =0;
    bool toRight = true;
    if((_event.type==sf::Event::KeyPressed && _event.key.code==l) || isLPressed)
    {
        isLPressed=true;
        _player.move(-_xVal*elapsedTime,0);
        row =1;
        toRight = false;
    }
    if((_event.type==sf::Event::KeyPressed && _event.key.code==r) || isRPressed)
    {
        isRPressed=true;
        _player.move(_xVal*elapsedTime,0);
        row =1;
    }
    if(((_event.type==sf::Event::KeyPressed && _event.key.code==u) || isUpPressed) && !isJumping)
    {
        isUpPressed=true;
        row = 2;
        //_player.move(0, -2.f);
        _player.move(0, -_upVel*elapsedTime);
    }
    if((_event.type==sf::Event::KeyReleased && _event.key.code==l)) isLPressed=false;
    if((_event.type==sf::Event::KeyReleased && _event.key.code==r)) isRPressed=false;
    if((_event.type==sf::Event::KeyReleased && _event.key.code==u)) {isUpPressed=false;isJumping=true;}


    // Simulate Gravity -> Add Collision platform detection here
    if(isJumping && _player.getPosition().y < GameState::_resY-GameState::_resY/8) {
        _velocity+=1.f;
        _player.move(0,_velocity*elapsedTime);
        dJump=0.f;
    }
    else if(!isJumping){
        dJump+=_upVel*elapsedTime;
        if(dJump>=150.f) isJumping=true;
    }
    else {_velocity=0;isJumping=false;}

    if(_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if(_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;
    animation.update(row,elapsedTime,toRight);
    _player.setTextureRect(animation.uvRect);


}






