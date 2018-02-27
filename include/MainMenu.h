//! \brief This is a main menu object.
#ifndef FIRENICE_MAINMENU_H
#define FIRENICE_MAINMENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <list>

class MainMenu{
public:
    static const short N_ITEMS = 3;
    MainMenu(float width, float height);

    short show(sf::RenderWindow &renderWindow); // Returns the id of the pressed button
    void up();
    void down();


private:
    short curIndex;
    sf::Text items[N_ITEMS];
    sf::Font font;
};
#endif //FIRENICE_MAINMENU_H
