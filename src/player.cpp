#include "player.h"

void task_player::make_player(const char* src , unsigned int size_x , unsigned size_y){
    sf::RectangleShape in_player(sf::Vector2f(size_x,size_y));
    this->player = in_player;
    this->playerTexture.loadFromFile((src));
    this->textureSize = playerTexture.getSize();
    this->player.setTexture(&playerTexture);
    this->player.setPosition(sf::Vector2f(0,750));
    this->textureSize.x/=3;
    this->textureSize.y/=9;
    player.setTextureRect(sf::IntRect (textureSize.x *2, textureSize.y *8 , textureSize.x , textureSize.y));
}

void task_player::move_right(float index) {
    this->player.move(index,0);
}
void task_player::move_left(float index) {
    this->player.move(-index,0);
}
void task_player::move_up(float index) {
    this->player.move(0,-index);
}
void task_player::move_down(float index) {
    this->player.move(0,index);
}
sf::RectangleShape task_player::get_player() {
    return this->player;
}
