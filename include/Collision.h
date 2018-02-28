#ifndef FIRENICE_COLLISION_H
#define FIRENICE_COLLISION_H

#include <SFML/Graphics.hpp>

class Collision{
public:
    Collision(sf::RectangleShape& body);
    ~Collision();

    void move(float dx,float dy){
        _player.move(dx,dy);
    }
    bool checkCollision(Collision& other , float e);
    sf::Vector2f GetPosition(){ return _player.getPosition();}
    sf::Vector2f GetHalfSize() { return _player.getSize()/ 2.0f;}


private:
    sf::RectangleShape& _player;

};


#endif //FIRENICE_COLLISION_H
