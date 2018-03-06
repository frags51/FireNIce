
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
 *      Pushes the state to WaitforClient if client calls for joining and to WaitforServer if process wishes to
 *      create a server.

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

    /** @brief Stores the current state of game.
     *
     */
    static state _state;

    /** @brief Object representing the server class initialised in initiation list with the listening and sending ports.
     *
     */
    static Server server;
    /** @brief Oject representing the client class initialised in initiation list with the listening and sending ports.
     *
     */
    static Client client;
    /**
     * @brief A boolean which checks if the running code is exectued from client or server side.
     */
    static bool isClient;

    /**
     * @brief Represents sending port for server and listening for client.
     */
    static unsigned short port1;
    /**
    * @brief Represents listening port for server and sending for client.
    */
    static unsigned short port2;

    /**
     * @brief Integer variable to denote the state of current level.
     */
    static unsigned short _curLevel;

    /**
     * @brief Race - A mutex for keeping the state of switch.
     *      In consistency.Adding and removing the switch into
     *      _objToBeActed container which has to be a critical section , to avoid multiple additions/removals.
     */
    static std::mutex race;
    /**
     * @brief Contains the objects (switch) state , checks whether they are activated or not which leads to further change other objects.
     *
     */
    static std::vector<VisibleGameObject *> _objToBeActed;

    /**
     *  @brief Contains the number of red gems collected by the fireboy .
     */
    static unsigned short redGemsCollected;
    /**
     * @brief Contains the number of blue gems collected by the watergirl .
     */
    static unsigned short blueGemsCollected;
    /**
     * @brief Game completes if maxRedGems is equal to the Red gems collected.
     */
    static unsigned short maxRedGems;
    /**
     * @brief Game completes if maxBlueGems is equal to the Blue gems collected.
     */
    static unsigned short maxBlueGems;

    /**
     * @brief Boolean checks whether Ice door is opened or not.
     */
    static bool _winI;
    /**
     * @brief Boolean checks whether Fire door is opened or not.
     */
    static bool _winF;

private:

    //! \brief Check if the game is in Exiting state.
    static bool isExiting();

    /**
     * @brief The big game loop which keeps the game going, checking for events.
     */
    static void gameLoop();

    //! \brief Init and show a splash screen.
    static void showSplashScreen();
    //! \brief Shows the Main menu , option to create or join server after flash screen.
    static void showMainMenu();
    //! \brief Shows the Level Screen , for selecting the level.
    static void showLevelScreen();
    //! \brief The current state of the game

private:
    /**
     * @brief Player from the server.
     *
     *      A basic entity of the game , is of type Player and has the task of collecting all the red gems
     *      and reach the red door without striking green fire or water.
     */
    static Player *fireboy;
    /**
     * @brief Player from the client.
     *
     *      A basic entity of the game , is of type Player and has the task of collecting all the blue gems
     *      and reach the blue door without striking green fire or fire.
     */
    static Player *watergirl;
    /**
     * @brief Holds all the objects as a map.
     *
     *      A class which has the responsibility of keeping all the game objects in a container , a map in this case
     *      iteration over which is used to update every object.
     */
    static ObjMan _gameObjectManager;

    /**
     * @brief The main window.
     *
     *      The window over which the game presides.
     */
    static sf::RenderWindow _mainWindow;

};

#endif //FIRENICE_GAMESTATE_H
