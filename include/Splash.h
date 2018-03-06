/**
 * \brief Saves Game state
 */
#ifndef FIRENICE_SPLASH_H_H
#define FIRENICE_SPLASH_H_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Splash{
public:
	/**loads and renders Splash Window and splash sprite*/
    int show(sf::RenderWindow & renderWindow);
};

#endif //FIRENICE_SPLASH_H_H
