#include "Player.h"
Player::Player(){
    velocityX=0;
    velocityY=0;
    accelerationX=0;
    accelerationY=0;
    gravity =2;
}
Player::~Player(){

}
void Player::set_size(){
    sf::Vector2u textureSize = playerTexture.getSize();
    textureSize.x/=3;
    textureSize.y/=9;
    _player.setTextureRect(sf::IntRect (textureSize.x *2, textureSize.y *8 , textureSize.x , textureSize.y));
}

void Player::updateMovement() {
    int x = _player.getPosition().x;
    int y = _player.getPosition().y;

    if(y < 500)                  //If you are above ground
        velocityY += gravity;    //Add gravity
    else if(y > 500)             //If you are below ground
        y = 500;                 //That's not supposed to happen, put him back up

    velocityX += accelerationX;
    velocityY += accelerationY;

    _player.setPosition(x+velocityX,y+velocityY);
}
