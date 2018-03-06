

#ifndef FIRENICE_PLATFORM_H
    #define FIRENICE_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "VisibleGameObject.h"
class Platform : public VisibleGameObject {
public:
    Platform(const std::string &fName , sf::Vector2f size, sf::Vector2f position);
    ~Platform();

    void Draw(sf::RenderWindow& window);
    bool checkCollision(VisibleGameObject* other, float e);
    void Update(float elapsedTime,sf::Event& _event,std::map<std::string, VisibleGameObject*>& _object);



private:
    const float vBarrierMoveDist;


};


#endif //FIRENICE_PLATFORM_H
