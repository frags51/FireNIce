#include "player.h"

void task_player::make_player(const char* src , unsigned int size_x , unsigned size_y){
    sf::RectangleShape in_player(sf::Vector2f(size_x,size_y));
    player = in_player;
    playerTexture.loadFromFile((src));
    textureSize = playerTexture.getSize();
    player.setTexture(&playerTexture);
    player.setPosition(sf::Vector2f(0,750));
    textureSize.x/=3;
    textureSize.y/=9;
    player.setTextureRect(sf::IntRect (textureSize.x *2, textureSize.y *8 , textureSize.x , textureSize.y));
}

sf::RectangleShape task_player::get_player() {
    return this->player;
}
