#include "Player.h"
#include "GameState.h"
Player::Player(std::string fName) :
        _velocity(0),
        _maxVelocity(600.0f),
        dJump {0.f}

{
    Load(fName, GameState::_resX/16,GameState::_resY/8);
    animation.create(&playerTexture,sf::Vector2u(3,9),0.3f);
    isJumping=false;

}


Player::~Player()
{
}


float Player::GetVelocity() const
{
    return _velocity;
}

void Player::Update(float elapsedTime,sf::Event& _event)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _player.move(-1.5f,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        _player.move(1.5f,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping)
    {
        //_player.move(0,-180.5f);
        _player.move(0, -2.f);
    }
    // Simulate Gravity -> Add Collision platform detection here
    if(isJumping && _player.getPosition().y < GameState::_resY-GameState::_resY/8) {
        _velocity+=1.f;
        _player.move(0,_velocity*elapsedTime);
        dJump=0.f;
    }
    else if(!isJumping){
        dJump+=2.f;
        //_player.move(0, _velocity*elapsedTime);
        if(dJump>=150.f) isJumping=true;
    }
    else {_velocity=0;isJumping=false;}

    if(_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if(_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;

    animation.update(0,elapsedTime);
    _player.setTextureRect(animation.uvRect);


}






