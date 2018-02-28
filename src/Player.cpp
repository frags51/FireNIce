#include "Player.h"
#include "GameState.h"
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        _player.move(0,-1.5f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        _velocity= 0.0f;
    }
    if(_player.getPosition().y < GameState::_resY-GameState::_resY/8) {_velocity+=1.f; _player.move(0,_velocity*elapsedTime);}
    else _velocity=0;
    if(_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if(_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;



}
void Player::set_size(){
    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x/=3;
    textureSize.y/=9;
    _player.setTextureRect(sf::IntRect (textureSize.x *2, textureSize.y *8 , textureSize.x , textureSize.y));
}






