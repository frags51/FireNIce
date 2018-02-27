#ifndef FIRENICE_OBJEC_H
#define FIRENICE_OBJEC_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class GameObject{
public:
    GameObject();
    virtual ~GameObject();

    virtual void load(std::string fName);
    virtual void draw(sf::RenderWindow &renderWindow);
    virtual void update(float timeElapsed);

    virtual void setPos(float x, float y);
    virtual sf::Vector2f getPos() const;
    virtual bool isLoaded() const;

protected: // Accessible to classes that inherit this class!
    sf::Sprite &getSprite();

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::string _fName;
    bool _isLoaded;
};

#endif //FIRENICE_OBJEC_H
