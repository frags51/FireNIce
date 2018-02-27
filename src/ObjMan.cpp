#include "ObjMan.h"

ObjMan::ObjMan() {};
ObjMan::~ObjMan() {std::for_each(_gameObjects.begin(), _gameObjects.end(), ObjMan::GameObjDealloc());}

void ObjMan::add(std::string name, GameObject *gameObject) {
    _gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
}

void ObjMan::remove(std::string name) {
    auto it = _gameObjects.find(name); // This is an iterator
    if(it!=_gameObjects.end()){
        delete it->second;
        _gameObjects.erase(it);
    }
}

GameObject *ObjMan::get(std::string name) const {
    auto it = _gameObjects.find(name);
    if(it!=_gameObjects.end()) return it->second;
    return nullptr;
}

int ObjMan::getObjCount() const {
    return _gameObjects.size();
}

void ObjMan::drawAll(sf::RenderWindow &renderWindow) {
    auto it = _gameObjects.begin();
    while(it!=_gameObjects.end()) {
        it->second->draw(renderWindow);
        it++;
    }
};




