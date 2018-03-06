
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
/**@class Game State
 * @brief Saves the current state of the game
 *
 *      Saves the state similar to a finite state machine transitioning between various states which define
 *      the snapshot of game at any instant. Some of the states include game in Playing State , At Main Menu or
 *      the server waiting for its client.
 *
 *      Takes the responsibility of setting up the server and keeping it's state in sync with it's client.
 *
 *      All the members of the class are static as the class is not instantiated and require to set up with an
 *      intialiser list.
 *
 *
 *
 *




    */

class GameState{
public:
    /** @brief The way paths are written: false for linux, true for OSX

                Filepath in Ubuntu requires going up a directory for loading resources (img or fonts) while
                OSX doesn't.
     */
    static bool filePath;

    /** @brief Horizontal Resolution
     *
     *          Sets up the horizontal length of the main rendering window , in the case of this game it is
     *          1600px.
     */
    static const unsigned short _resX {1600};
    /** @brief Vertical Resolution
     *
     *          Sets up the vertical length of the main rendering window , in the case of this game it is
     *          900px.
     */
    static const unsigned short _resY {900};

    /** @brief Start Playing the game!

             * Sets the game running up right on and loads all the required resources (fonts or images) .
             * Renders the main window and pushes the game to the Splash flashing state and sets up the main
             * Game Loop in action
     */
    static void play();

    /** @brief Has the task of loading the resources from the Level<num>.text file which sets up the required
     *          resources for setting up the level. Reserves memory in heap for all the GameObjects and adds them into
     *          a map as a common storage entity.
     * @param level
     */
    static void LoadFromFile(unsigned int level);


     /**@enum State
      *     @brief The following are the States of the Game.
     */

    enum state {Not_init , /**< Game is not init */
                LevelCheck ,/**< Level Selection Menu */
                AtSplash, /**< Splash state of Game*/
                AtMenu, /**< The main menu of game*/
                WaitForClient, /**< Server waiting state for Client */
                WaitForServer, /**< Client waiting for Server */
                Playing, /**< The right on playing state*/
                Exiting, /**< Windowexits */
                GameOver, /**< Shows the defeat of player  */
                GameWon}; /**< Shows the win of player */
                // More maybe added later.
    static state _state;
    static Server server;
    static Client client;
    static bool isClient;

    static unsigned short port1;
    static unsigned short port2;

    static unsigned short _curLevel;

    static std::mutex race;
    static std::vector<VisibleGameObject *> _objToBeActed;

    static unsigned short redGemsCollected;
    static unsigned short blueGemsCollected;
    static unsigned short maxRedGems;
    static unsigned short maxBlueGems;

    static bool _winI;
    static bool _winF;

private:

    //! \brief Check if the game is in Exiting state.
    static bool isExiting();
    static void gameLoop();

    //! \brief Init and show a splash screen.
    static void showSplashScreen();
    static void showMainMenu();
    static void showLevelScreen();
    //! \brief The current state of the game

private:
    static Player *fireboy;
    static Player *watergirl;
    static ObjMan _gameObjectManager;

    static sf::RenderWindow _mainWindow;

};

#endif //FIRENICE_GAMESTATE_H
