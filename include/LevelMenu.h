//! \brief This is a main menu object.
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
	/** Default constructor. Creates a new window to display the selected level.
	    */
public:
    static const short N_LEVELS = 2;/**Stores the number of levels*/
    LevelMenu(float width, float height);/**controls the behavior of the generated window*/

    unsigned short show(sf::RenderWindow &renderWindow); // Returns the id of the pressed button
    void up();/**increments the curIndex value i.e,level and also updates the text on the window*/
    void down();/**decrements the curIndex value i.e,level and also updates the text on the window*/


private:
    unsigned short curIndex;/**<initial curIndex i.e, level number*/
    sf::Text item;/**<initial text on the screen*/
    /**The text displayed on the generated window*/
    sf::Font font;/**<initial font*/
    /**The font of the text on the generated window*/
};
#endif //FIRENICE_LevelMenu_H
