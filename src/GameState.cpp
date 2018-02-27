#include "MainMenu.h"
#include "GameState.h"
#include "Splash.h"
#include "Server.h"
#include <thread>
#include <iostream>

GameState::state GameState::_state = Not_init; // Need to initialize these
sf::RenderWindow GameState::_mainWindow;
Server GameState::server(45000);

void GameState::play() {
    static_assert(_resX <= 1920 && _resY <= 1080, "Invalid Screen Resolution!");
    if(_state!=Not_init) return;


    _mainWindow.create(sf::VideoMode(_resX, _resY, 32), "Fire & Ice");
    _state=state::AtSplash;

    while(!isExiting()) gameLoop();

    _mainWindow.close();
} // play()

bool GameState::isExiting() {
    return _state==state::Exiting;
} // isExiting

void GameState::gameLoop() {
    sf::Event _event;
    while(_mainWindow.pollEvent(_event)){
        switch (_state){
            case GameState::state::AtSplash:{
                showSplashScreen();
            }
            break; // Showing Splash screen
            case GameState::state::AtMenu:{
                showMainMenu();
            }
            break; // Showing Main Menu
            case GameState::state::WaitForClient:{
                bool res=false;
                std::thread t1(&Server::waitForClient,&server, &res);
                _mainWindow.clear(sf::Color::Cyan);
                sf::Text dmsg;
                sf::Font f1;
                f1.loadFromFile("../res/fonts/Phetsarath_OT.ttf");
                dmsg.setFont(f1);
                dmsg.setFillColor(sf::Color::Black);
                dmsg.setString("Waiting for connection!\nConnect To:"+sf::IpAddress::getLocalAddress().toString());
                dmsg.setPosition(sf::Vector2f(800, 400));
                _mainWindow.draw(dmsg);
                _mainWindow.display();
                std::cout<<"waiting to join"<<std::endl;
                t1.join();
                while(!res);
                _state=GameState::state::Playing;
            }
            break;
            case GameState::state::WaitForServer:{
                _mainWindow.clear(sf::Color::Cyan);
                sf::Text dmsg;
                sf::Font f1;
                f1.loadFromFile("../res/fonts/Phetsarath_OT.ttf");
                dmsg.setFont(f1);
                dmsg.setString("Please enter IP");
                dmsg.setFillColor(sf::Color::Black);
                dmsg.setPosition(sf::Vector2f(800, 400));
                _mainWindow.draw(dmsg);
                _mainWindow.display();
                std::string enter;
                bool flag=false;
                _mainWindow.pollEvent(_event);
                while((flag=_mainWindow.pollEvent(_event))==true || !flag){
                    if(flag && _event.type==sf::Event::TextEntered){
                        if(_event.text.unicode<128 ){
                            if(_event.text.unicode!=13 && _event.text.unicode!=10)
                                enter+= static_cast<char>(_event.text.unicode);
                            else {
                                std::cout<<"Got an enter! after "<<enter<<std::endl;
                                _state=Playing;
                                flag=false;
                                break;
                            }
                        }
                        dmsg.setString("You Entered: "+enter);
                        _mainWindow.clear(sf::Color::Cyan);
                        _mainWindow.draw(dmsg);
                        _mainWindow.display();
                    }
                } // inner eve loop
            } // Wait for server
            break;
            case GameState::state::Playing:{
                _mainWindow.clear(sf::Color{255,0,0,150});
                _mainWindow.display();
                if(_event.type==sf::Event::Closed){
                    _state = GameState::state ::Exiting;
                }
                break;
            } // Case Playing.

            default:
                break;
        } //switch
    } //while
} //gameLoop()

void GameState::showSplashScreen() {
    Splash splashScreen;
    if(splashScreen.show(_mainWindow)==-1) {
        _state = GameState::state::Exiting;
        return;
    }
    // When this returns, show the menu!
    _state=GameState::state::AtMenu; // Change this to AtMenu when menu is added
} // showSplashScreen

void GameState::showMainMenu() {
    MainMenu mm(_mainWindow.getSize().x, _mainWindow.getSize().y);
    short res = mm.show(_mainWindow);
    if(res==-1 || res== 2) _state=Exiting;
    else if(res==0) _state=WaitForClient;
    else if(res==1) _state=WaitForServer;
}