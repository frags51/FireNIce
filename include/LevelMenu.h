//! \brief This is a main menu object.
#ifndef FIRENICE_LEVELMENU_H
#define FIRENICE_LEVELMENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <list>

class LevelMenu{
public:
    static const short N_LEVELS = 2;
    LevelMenu(float width, float height);

    short show(sf::RenderWindow &renderWindow); // Returns the id of the pressed button
    void up();
    void down();


private:
    short curIndex;
    sf::Text item;
    sf::Font font;
};
#endif //FIRENICE_LevelMenu_H
