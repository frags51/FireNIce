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
    auto tPos=this->_player.getPosition();
    auto tSize = this->_player.getSize();
    auto oPos=other->_player.getPosition();
    auto oSize = other->_player.getSize();

    sf::Rect<float> a {tPos.x-tSize.x/2, tPos.y-tSize.y/2, this->_player.getSize().x, this->_player.getSize().y};
    sf::Rect<float> b {oPos.x-oSize.x/2, oPos.y-oSize.y/2, other->_player.getSize().x, other->_player.getSize().y};


    bool x = a.intersects(b);
    //if(x) {std::cout<<"Intersect\nAPos: "<<tPos.x<<" "<<tPos.y<<" Bpos: "<<oPos.x<<" "<<oPos.y<<std::endl;}
    return x;
}






