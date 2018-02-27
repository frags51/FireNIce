#include "Object.h"

GameObject::GameObject(): _isLoaded {false} {};
GameObject::~GameObject() {}

void GameObject::load(std::string fName) {
    if(!_texture.loadFromFile(fName)) _isLoaded=false;
    else {
        _fName=fName;
        _isLoaded=true;
        _sprite.setTexture(_texture);
    }
}

void GameObject::draw(sf::RenderWindow &renderWindow) {
    if(_isLoaded) renderWindow.draw(_sprite);
}

void GameObject::update(float timeElapsed) {}

void GameObject::setPos(float x, float y) {
    if(_isLoaded) _sprite.setPosition(x, y);
}

sf::Vector2f GameObject::getPos() const {
    if(_isLoaded) return _sprite.getPosition();
    return sf::Vector2f{};
}

bool GameObject::isLoaded() const {
    return _isLoaded;
}

sf::Sprite &GameObject::getSprite() {
    return _sprite;
};



