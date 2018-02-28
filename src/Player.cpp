#include "Player.h"
#include "GameState.h"
#include <iostream>
Player::Player() :
        _velocity(0),
        _maxVelocity(600.0f)
{
    Load("res/img/tux.png", GameState::_resX/16,GameState::_resY/8);
    this->set_size();
}


Player::~Player()
{
}


float Player::GetVelocity() const
{
    return _velocity;
}

void Player::Update(float elapsedTime)
{
    std::cout<<"Hi\n";
    if(GameState::GetInput().type == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        _velocity-= 3.0f;
    }
    if(GameState::GetInput().type == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        std::cout<<"Hi\n";
        _velocity+= 3.0f;
    }

    if(GameState::GetInput().type == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity= 0.0f;
    }

    if(_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if(_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;




    _player.move(_velocity * elapsedTime, 0);
}
void Player::set_size(){
    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x/=3;
    textureSize.y/=9;
    _player.setTextureRect(sf::IntRect (textureSize.x *2, textureSize.y *8 , textureSize.x , textureSize.y));
}






