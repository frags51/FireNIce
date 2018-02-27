#ifndef FIRENICE_OBJMAN_H
#define FIRENICE_OBJMAN_H

#include "Object.h"
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>

class ObjMan{
public:
    ObjMan();
    ~ObjMan();
    void add(std::string name, GameObject *gameObject);
    void remove(std::string name);
    int getObjCount() const;
    GameObject *get(std::string name) const;
    void drawAll(sf::RenderWindow &renderWindow);

private:
    std::map<std::string, GameObject*> _gameObjects;

    struct GameObjDealloc{
        void operator()(const std::pair<std::string, GameObject*> &a) const{
            delete a.second;
        }
    }; //functor ends
};

//class
#endif //FIRENICE_OBJMAN_H
