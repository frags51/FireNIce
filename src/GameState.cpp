#include "MainMenu.h"
#include "GameState.h"
#include "Splash.h"
#include <thread>
#include <iostream>

GameState::state GameState::_state = Not_init; // Need to initialize these
sf::RenderWindow GameState::_mainWindow;
Server GameState::server{45004};
Client GameState::client{};

ObjMan GameState::_gameObjectManager;

bool GameState::filePath {false}; // false for linux, true for OSX

bool GameState::isClient;

void GameState::play() {
    static_assert(_resX <= 1920 && _resY <= 1080, "Invalid Screen Resolution!");
    if(_state!=Not_init) return;
    _mainWindow.create(sf::VideoMode(_resX, _resY, 32), "Fire & Ice");
    Player *fireboy= nullptr;
    if(!filePath)fireboy = new Player("../res/img/tux.png");
    else fireboy = new Player("res/img/tux.png");
    fireboy->SetPosition(0,_resY-_resY/8);
    _gameObjectManager.add("Fireboy",fireboy);

    _state=state::AtSplash;

    while(!isExiting()) {
        gameLoop(fireboy);
    }
    if(isClient) client.socket.disconnect();
    else GameState::server.client.disconnect();
    _mainWindow.close();
} // play()

bool GameState::isExiting() {
    return _state==state::Exiting;
} // isExiting

void GameState::gameLoop(VisibleGameObject *fireboy) {
    bool execdOnce=false;

    sf::Event _event;
    _mainWindow.pollEvent(_event);
        switch (_state) {
            case GameState::state::AtSplash: {
                showSplashScreen();
            }
                break; // Showing Splash screen
            case GameState::state::AtMenu: {
                showMainMenu();
            }
                break; // Showing Main Menu
            case GameState::state::WaitForClient: {
                bool res = false;
                std::thread t1(&Server::waitForClient, &server, &res);
                _mainWindow.clear(sf::Color::Cyan);
                sf::Text dmsg;
                sf::Font f1;
                std::string fontFileM;
                if(!GameState::filePath) fontFileM="../res/fonts/Phetsarath_OT.ttf";
                else fontFileM="res/fonts/Phetsarath_OT.ttf";
                f1.loadFromFile(fontFileM);
                dmsg.setFont(f1);
                dmsg.setFillColor(sf::Color::Black);
                dmsg.setString("Waiting for connection!\nConnect To:" + sf::IpAddress::getLocalAddress().toString());
                dmsg.setPosition(sf::Vector2f(800, 400));
                _mainWindow.draw(dmsg);
                _mainWindow.display();
                std::cout << "Waiting for clients to join!" << std::endl;
                t1.join();
                while (!res); // Wait to get connection
                std::cout << "Connected to: " << server.client.getRemoteAddress() << std::endl;
                isClient = false;
                _state = GameState::state::Playing;
            }
                break;
            case GameState::state::WaitForServer: {
                _mainWindow.clear(sf::Color::Cyan);
                sf::Text dmsg;
                sf::Font f1;
                std::string fontFileM;
                if(!GameState::filePath) fontFileM="../res/fonts/Phetsarath_OT.ttf";
                else fontFileM="res/fonts/Phetsarath_OT.ttf";
                f1.loadFromFile(fontFileM);
                dmsg.setFont(f1);
                dmsg.setString("Please enter IP");
                dmsg.setFillColor(sf::Color::Black);
                dmsg.setPosition(sf::Vector2f(800, 400));
                _mainWindow.draw(dmsg);
                _mainWindow.display();
                //! \brief For storing IP address of the server to be connected (as input).
                std::string enter;
                bool flag = false;
                _mainWindow.pollEvent(_event);
                while ((flag = _mainWindow.pollEvent(_event)) == true || !flag) { // flag required for inf loop
                    // Since pollEvent returns false if no event has been registered
                    // Causing re init of enter strings.
                    if (flag && _event.type == sf::Event::TextEntered) {
                        if (_event.text.unicode < 128) {
                            if (_event.text.unicode != 13 && _event.text.unicode != 10)
                                enter += static_cast<char>(_event.text.unicode);
                            else {
                                std::cout << "Got an enter! after " << enter << std::endl;
                                if (client.socket.connect(enter, 45004) != sf::Socket::Done) {
                                    std::cerr << "Error in Client Socket!" << std::endl;
                                    enter = "";
                                } else {
                                    isClient = true;
                                    _state = Playing;
                                    flag = false;
                                    break;
                                }
                            }
                        }
                        dmsg.setString("You Entered: " + enter);
                        _mainWindow.clear(sf::Color::Cyan);
                        _mainWindow.draw(dmsg);
                        _mainWindow.display();
                    } else if (flag && _event.type == sf::Event::Closed) {
                        _state = Exiting;
                        _mainWindow.close();
                        break;
                    }
                } // inner eve loop
            } // Wait for server
                break;
            case GameState::state::Playing: {

                if(!isClient){ // Server

                    _mainWindow.clear(sf::Color{255, 0, 0, 150});
                    float telap = _gameObjectManager._clock.getElapsedTime().asSeconds();
                    _gameObjectManager.updateAll(_event);

                    if (_event.type == sf::Event::Closed) {
                        _state = GameState::state::Exiting;
                    }
                    else if(_event.type==sf::Event::KeyPressed || _event.type==sf::Event::KeyReleased){
                    //    server.checkSent();
                        //   server.send(_gameObjectManager.get("Fireboy")->GetPosition());
                    //    std::cout<<"sent: "<<_gameObjectManager.get("Fireboy")->GetPosition().x<<" "<<_gameObjectManager.get("Fireboy")->GetPosition().y<<std::endl;
                        sf::Packet t;
                        t<<_event.key.code<<(_event.type==sf::Event::KeyPressed) <<telap;
                        server.client.send(t);
                    }
                    else if(_event.type==sf::Event::Closed){
                        _state=Exiting;
                        break;
                    }
                    _gameObjectManager.drawAll(_mainWindow);
                    _mainWindow.display();


                }
                else{ // Client
                    _gameObjectManager.remove("Fireboy");
                    _mainWindow.clear(sf::Color::Cyan);

                    //client.receive();

                    if (_event.type == sf::Event::Closed) {
                        _state = GameState::state::Exiting;
                    }
                    else if(_event.type==sf::Event::KeyPressed){
                        //server.checkSent();
                        //server.send(_gameObjectManager.get("Fireboy")->GetPosition());
                    }
                    else if(_event.type==sf::Event::Closed){
                        _state=Exiting;
                        break;
                    }
                    _mainWindow.clear(sf::Color{255, 0, 0, 150});
                    _gameObjectManager.updateAll(_event);
                    _gameObjectManager.drawAll(_mainWindow);

                    /*if(client.recdStatus.wait_for(std::chrono::seconds(0))==std::future_status::ready){
                        if(client.recdStatus.get()==sf::Socket::Done){
                            float x,y;
                            client.recd>>x>>y;
                            std::cout<<"in client code:: "<<x<<" "<<y<<fireboy->IsLoaded()<<std::endl;
                            fireboy->SetPosition(x,y);
                            fireboy->Draw(_mainWindow);
                        }
                    } */
                    sf::Packet t;
                    if(client.socket.receive(t)==sf::Socket::Done){
                        int x; bool press; float telap;
                        t>>x>>press>>telap;

                        sf::Event::KeyEvent data;
                        data.code = (sf::Keyboard::Key)x;
                        data.alt = false;
                        data.control = false;
                        data.shift = false;
                        data.system = false;

                        sf::Event __event;
                        if(press)__event.type = sf::Event::KeyPressed;
                        else __event.type=sf::Event::KeyReleased;
                        __event.key = data;

                        fireboy->Update(telap, __event);
                        fireboy->Draw(_mainWindow);
                    }

                    _mainWindow.display();


                }
                break;
            } // Case Playing.

            default:
                break;
        } //switch

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


