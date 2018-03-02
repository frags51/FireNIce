#ifndef FIRENICE_COLLISION_H
#define FIRENICE_COLLISION_H

#include <SFML/Graphics.hpp>

class Collision{
public:
    Collision(sf::RectangleShape& body);
    ~Collision();


    bool checkCollision(Collision &other , float e);
    sf::Vector2f GetPosition(){ return _player.getPosition();}


private:
    sf::RectangleShape& _player;

};


#endif //FIRENICE_COLLISION_H
