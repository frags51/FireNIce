#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
class task_player{
private:
    sf::RectangleShape player;
    sf::Texture playerTexture;
    sf::Vector2u textureSize;
public:
    bool isjumping;


public:
    void make_player(const char* src , unsigned int size_x , unsigned int size_y);
    sf::RectangleShape get_player();
    void move_right(float index);
    void move_left(float index);
    void move_up(float index);
    void move_down(float index);

    int getY();

    //src is the image file location
    //size_x and size_y are image dimensions
};
#endif // PLAYER_H
