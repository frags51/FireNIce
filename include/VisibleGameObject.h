#ifndef GAME_OBJECT
#define GAME_OBJECT
#include <iostream>
#include <SFML/Graphics.hpp>
class VisibleGameObject{
public:
    VisibleGameObject();
    ~VisibleGameObject();

    virtual void Load(std::string filename,float x,float y);
    virtual void Draw(sf::RenderWindow & window);

    virtual void SetPosition(float x, float y);
    virtual void Update(float elapsedTime,sf::Event& event,std::map<std::string, VisibleGameObject*>& _object);
    virtual sf::Vector2f GetPosition() const;
    virtual bool IsLoaded() const;
    virtual sf::Vector2f GetHalfSize() { return _player.getSize()/2.0f;}
    virtual void move(float dx,float dy){ _player.move(dx,dy); }
    sf::RectangleShape _player;

    enum stateOfObj {DEF, VBSPRESSED, VBMOVED};
    stateOfObj _stateOfObj;
protected:
    sf::Texture playerTexture;
    std::string _filename;
    bool _isLoaded;

};
#endif