#include "Player.h"
#include "GameState.h"
#include <cmath>
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

void Player::Update(float elapsedTime,sf::Event& _event,std::map<std::string, VisibleGameObject*>& _object)
{
    bool isCollide = false;
    for(auto it:_object){
        if(checkCollision(it.second,1.0f)) isCollide = true;
    }
    if(isCollide) return;
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

bool Player::checkCollision(VisibleGameObject* other, float e){
    sf::Vector2f otherPosition = other->GetPosition();
    sf::Vector2f otherHalfSize = other->GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
    if(intersectX<0.0f && intersectY<0.0f) {
        e = std::min(std::max(e,0.0f),1.0f);
        if( intersectX > intersectY) {
            if(deltaX >0.0f){
                move(intersectX * (1.0f -e),0.0f);
                other->move((-intersectX*e),0.0f);
            }
            else{
                move(-intersectX * (1.0f -e),0.0f);
                other->move(intersectX*e,0.0f);
            }
        }
        else{
            if(deltaY >0.0f){
                move(0.0f,intersectY * (1.0f -e));
                other->move(0.0f,(-intersectY*e));
            }
            else{
                move(0.0f,-intersectY * (1.0f -e));
                other->move(0.0f,intersectY*e);
            }
        }
        return true;
    }
    return false;
}






