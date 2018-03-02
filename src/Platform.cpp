#include "Platform.h"
Platform::Platform(sf::Texture* texture , sf::Vector2f size, sf::Vector2f position) {
    Load("",size.x,size.y);
    _player.setSize(size);
    _player.setPosition(position);
    //_player.setOrigin(size/2.0f);
}
Platform::~Platform() {

}
void Platform::Draw(sf::RenderWindow &window) {
    window.draw(_player);
}
