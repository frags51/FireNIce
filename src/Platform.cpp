#include "Platform.h"
Platform::Platform(const std::string &texture, sf::Vector2f size, sf::Vector2f position) {
    Load(texture,size.x,size.y);
    _player.setSize(size);
    _player.setPosition(position);
    _player.setOrigin(0,0);
    _player.setOutlineColor(sf::Color::Black);
    _player.setOutlineThickness(3.f);
}
Platform::~Platform() {

}
void Platform::Draw(sf::RenderWindow &window) {
    window.draw(_player);
}
