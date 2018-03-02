#include "Player.h"
#include "GameState.h"
#include <cmath>
Player::Player(std::string fName) :
        _velocity(0),
        _maxVelocity(600.0f),
        dJump {0.f}

{
    Load(fName, GameState::_resX/16,GameState::_resY/9);
    animation.create(&playerTexture,sf::Vector2u(3,9),0.3f);
    isJumping=false;
    setCollision = false;

}


Player::~Player()
{
}



void Player::Update(float elapsedTime,sf::Event& _event)
{
    if(setCollision){
        return ;
    }
    int row =0;
    bool toRight = true;
    if((_event.type==sf::Event::KeyPressed && _event.key.code==sf::Keyboard::Left) || isLPressed)
    {
        isLPressed=true;
        _player.move(-1.5f,0);
        row =1;
        toRight = false;
    }
    if((_event.type==sf::Event::KeyPressed && _event.key.code==sf::Keyboard::Right) || isRPressed)
    {
        isRPressed=true;
        _player.move(1.5f,0);
        row =1;
    }
    if(((_event.type==sf::Event::KeyPressed && _event.key.code==sf::Keyboard::Up) || isUpPressed) && !isJumping)
    {
        isUpPressed=true;
        row = 2;
        _player.move(0, -2.f);
    }
    if((_event.type==sf::Event::KeyReleased && _event.key.code==sf::Keyboard::Left)) isLPressed=false;
    if((_event.type==sf::Event::KeyReleased && _event.key.code==sf::Keyboard::Right)) isRPressed=false;
    if((_event.type==sf::Event::KeyReleased && _event.key.code==sf::Keyboard::Up)) isUpPressed=false;


    // Simulate Gravity -> Add Collision platform detection here
    if(isJumping && _player.getPosition().y < GameState::_resY-GameState::_resY/8) {
        _velocity+=1.f;
        _player.move(0,_velocity*elapsedTime);
        dJump=0.f;
    }
    else if(!isJumping){
        dJump+=2.f;
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
        setCollision = true;
        return true;
    }
    setCollision = false;
    return false;
}






