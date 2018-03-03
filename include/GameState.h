/**
 * \brief Saves Game state
 */

#ifndef FIRENICE_GAMESTATE_H
#define FIRENICE_GAMESTATE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Platform.h"
#include "Server.h"
#include "ObjMan.h"
#include "VisibleGameObject.h"
#include "Client.h"
#include "ObjMan.h"

class GameState{
public:
    //! \brief The way paths are written: false for linux, true for OSX
    static bool filePath;
    //! \brief Horizontal Resolution
    static const unsigned short _resX {1600};
    //! \brief Vertical Resolution
    static const unsigned short _resY {900};

    //! \brief Start Playing the game!
    static void play();
    static void LoadFromFile(unsigned int level);

    //! \brief The set of possible states of the game
    enum state {Not_init ,LevelCheck , AtSplash, AtMenu, WaitForClient, WaitForServer, Playing, Exiting}; // More maybe added later.
    static state _state;
    static Server server;
    static Client client;
    static bool isClient;

    static unsigned short port1;
    static unsigned short port2;

    static unsigned short _curLevel;

private:

    //! \brief Check if the game is in Exiting state.
    static bool isExiting();
    static void gameLoop(VisibleGameObject *fireboy, VisibleGameObject *watergirl);

    //! \brief Init and show a splash screen.
    static void showSplashScreen();
    static void showMainMenu();
    static void showLevelScreen();
    //! \brief The current state of the game

private:

    static ObjMan _gameObjectManager;

    static sf::RenderWindow _mainWindow;

};

#endif //FIRENICE_GAMESTATE_H
