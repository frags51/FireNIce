#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject(){
    _isLoaded = false;
}


VisibleGameObject::~VisibleGameObject(){
}

void VisibleGameObject::Load(std::string filename,float x,float y){
    if(playerTexture.loadFromFile(filename) == false){
        _filename = "";
        _isLoaded = false;
    }
    else{
        _filename = filename;
        _isLoaded = true;
        _player.setSize(sf::Vector2f(x,y));
        _player.setTexture(&playerTexture);
    }
}


void VisibleGameObject::Draw(sf::RenderWindow & renderWindow){
    if(_isLoaded){
        renderWindow.draw(_player);
    }
}

void VisibleGameObject::SetPosition(float x, float y){
    if(_isLoaded){
        _player.setPosition(x,y);
    }
}