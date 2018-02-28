#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>
class Animation{

public:
    Animation();
    ~Animation();
    void update(int row,float deltaTime,bool faceRight);
    void create(sf::Texture* texture,sf::Vector2u imageCount,float switchTime);

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;
    float totalTime;
    float switchTime;

};

#endif