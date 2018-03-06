//! \brief This is a main menu object.
#ifndef FIRENICE_MAINMENU_H
#define FIRENICE_MAINMENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <list>

class MainMenu{
public:
	/**number of items in the list displayed*/
    static const short N_ITEMS = 3;
    /**behavior of the MainMenu window*/
    MainMenu(float width, float height);

    short show(sf::RenderWindow &renderWindow); // Returns the id of the pressed button
    /**increments the curIndex value(list index) ,updates the text on the window*/
    void up();
    /**decrements the curIndex value(list index) ,updates the text on the window*/
    void down();


private:
	/**initial curIndex (list index)*/
    short curIndex;
    /**The list of text displayed on the MainMenu window*/
    sf::Text items[N_ITEMS];
    /**The font of the text on the MainMenu window*/
    sf::Font font;
};
#endif //FIRENICE_MAINMENU_H
