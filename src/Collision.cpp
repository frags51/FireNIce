#include "Collision.h"
#include <cmath>
#include <iostream>

Collision::Collision(sf::RectangleShape& body) :
        _player(body)
{

}
bool Collision::checkCollision(Collision &other, float e) {
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = this->GetPosition();
    sf::Vector2f thisHalfSize = this->GetHalfSize();
    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
    if(intersectX<0.0f && intersectY<0.0f) {
        e = std::min(std::max(e,0.0f),1.0f);
        if( intersectX > intersectY) {
            if(deltaX >0.0f){
                move(intersectX * (1.0f -e),0.0f);
                other.move((-intersectX*e),0.0f);
            }
            else{
                move(-intersectX * (1.0f -e),0.0f);
                other.move(intersectX*e,0.0f);
            }
        }
        else{
            if(deltaY >0.0f){
                move(0.0f,intersectY * (1.0f -e));
                other.move(0.0f,(-intersectY*e));
            }
            else{
                move(0.0f,-intersectY * (1.0f -e));
                other.move(0.0f,intersectY*e);
            }
        }
        return true;
    }




    return false;


}