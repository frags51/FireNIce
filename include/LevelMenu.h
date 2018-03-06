//! \brief This is a level menu object.
#ifndef FIRENICE_LEVELMENU_H
#define FIRENICE_LEVELMENU_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
//#include <list>

/**
    @author G M Aishwarya
    @date March 2018
    */

class LevelMenu{
	/** Default constructor. new window for level selection.
	    */
public:
    /**number of levels*/
    static const short N_LEVELS = 2;
    /**behavior of the LevelMenu window*/
    LevelMenu(float width, float height);

    unsigned short show(sf::RenderWindow &renderWindow); // Returns the id of the pressed button
    /**increments the curIndex value (level number),updates the text on the window*/
    void up();
    /**decrements the curIndex value (level number),updates the text on the window*/
    void down();


private:
    /**initial curIndex (level number)*/
    unsigned short curIndex;
    /**The text displayed on the LevelMenu window*/
    sf::Text item;
    /**The font of the text on the LevelMenu window*/
    sf::Font font;
    
};
#endif //FIRENICE_LevelMenu_H
