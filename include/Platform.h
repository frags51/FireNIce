

#ifndef FIRENICE_PLATFORM_H
#define FIRENICE_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Platform.h"
#include "VisibleGameObject.h"
class Platform : public VisibleGameObject {
public:
    Platform(sf::Texture* texture , sf::Vector2f size, sf::Vector2f position);
    ~Platform();

    void Draw(sf::RenderWindow& window);

public:
    Collision GetCollider(){return Collision(_player);}

private:
};


#endif //FIRENICE_PLATFORM_H
