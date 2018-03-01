#ifndef FIRENICE_OBJMAN_H
#define FIRENICE_OBJMAN_H

#include "VisibleGameObject.h"
#include <string>
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>

class ObjMan{
public:
    ObjMan();
    ~ObjMan();
    void add(std::string name, VisibleGameObject *gameObject);
    void remove(std::string name);
    void updateAll(sf::Event& _event);
    int getObjCount() const;
    VisibleGameObject *get(std::string name) const;
    void drawAll(sf::RenderWindow &renderWindow);
    void dAU(sf::RenderWindow &renderWindow, sf::Event & _event);
    sf::Clock _clock;
private:
    std::map<std::string, VisibleGameObject*> _gameObjects;

    struct GameObjDealloc{
        void operator()(const std::pair<std::string, VisibleGameObject*> &a) const{
            delete a.second;
        }
    }; //functor ends
};

//class
#endif //FIRENICE_OBJMAN_H
