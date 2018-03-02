#include "MainMenu.h"
#include "GameState.h"
#include "Splash.h"
#include <thread>

GameState::state GameState::_state = Not_init; // Need to initialize these
sf::RenderWindow GameState::_mainWindow;
unsigned short GameState::port1 {45010};
unsigned short GameState::port2 {45011};
Server GameState::server{GameState::port1, GameState::port2};
Client GameState::client{};

ObjMan GameState::_gameObjectManager;

bool GameState::filePath {true}; // false for linux, true for OSX

bool GameState::isClient;

void GameState::play() {
    static_assert(_resX <= 1920 && _resY <= 1080, "Invalid Screen Resolution!");
    if(_state!=Not_init) return;
    _mainWindow.create(sf::VideoMode(_resX, _resY, 32), "Fire & Ice");
    Player *fireboy= nullptr;
    if(!filePath)fireboy = new Player("../res/img/tux.png", sf::Keyboard::Up,sf::Keyboard::Left, sf::Keyboard::Right);
    else fireboy = new Player("res/img/tux.png", sf::Keyboard::Up,sf::Keyboard::Left, sf::Keyboard::Right);
    fireboy->SetPosition(0,_resY-_resY/8);
    _gameObjectManager.add("Fireboy",fireboy);

    Player *watergirl= nullptr;
    if(!filePath)watergirl = new Player("../res/img/tux.png", sf::Keyboard::Up,sf::Keyboard::Left, sf::Keyboard::Right);
    else watergirl= new Player("res/img/tux.png", sf::Keyboard::Up,sf::Keyboard::Left, sf::Keyboard::Right);
    watergirl->SetPosition(_resX-_resX/16,_resY-_resY/8);
    _gameObjectManager.add("Watergirl",watergirl);

    Platform *platform2 = new Platform(nullptr,sf::Vector2f(100.0f,100.0f),sf::Vector2f(400.0f,_resY-100));
    _gameObjectManager.add("Plt2",platform2);

    _state=state::Playing;

    while(!isExiting()) {
        gameLoop(fireboy, watergirl);
    }
    if(isClient) {client.listenSocket.disconnect();delete(fireboy);}
    else {GameState::server.sendSocket.disconnect(); delete(watergirl);}
    _mainWindow.close();
} // play()

bool GameState::isExiting() {
    return _state==state::Exiting;
} // isExiting

void GameState::gameLoop(VisibleGameObject *fireboy, VisibleGameObject *watergirl) {
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
                bool res {false};
                bool res2 {false};
                std::thread t1(&Server::waitForClientSendSocket, &server, &res);
                std::thread t2(&Server::waitForClientListenSocket, &server, &res2);
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
                t2.join();
                while (!res || !res2); // Wait to get connection
                std::cout << "Connected to: " << server.sendSocket.getRemoteAddress() << std::endl;
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
                                if (client.listenSocket.connect(enter, GameState::port1) != sf::Socket::Done) {
                                    std::cerr << "Error in Client listen Socket!" << std::endl;
                                    enter = "";
                                }
                                else if(client.sendSocket.connect(enter, GameState::port2) != sf::Socket::Done){
                                    std::cerr << "Error in Client Send Socket!" << std::endl;
                                }
                                else {
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
                    _gameObjectManager.remove("Watergirl");

                    server.sendSocket.setBlocking(true);
                    _mainWindow.clear(sf::Color{255, 0, 0, 150});

                    float telap = _gameObjectManager._clock.restart().asSeconds();
                    if (_event.type == sf::Event::Closed) {
                        sf::Packet tDash;
                        tDash<<-1<<false<<0.f;
                        sf::Socket::Status st= server.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt send packet(1) to Server!"<<std::endl; }
                        _state = GameState::state::Exiting;
                        break;
                    }
                    else if(_event.type==sf::Event::KeyPressed || _event.type==sf::Event::KeyReleased){
                        sf::Packet tDash;
                        tDash<<_event.key.code<<(_event.type==sf::Event::KeyPressed) <<telap;
                        sf::Socket::Status st= server.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cerr<<"Couldnt upd packet"<<std::endl;}
                    }
                    else {
                        sf::Packet tDash;
                        tDash<<-2<<false<<fireboy->GetPosition().y;
                        sf::Socket::Status st= server.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt upd packet"<<std::endl; }
                    }

                    bool need_upd {false};
                    std::future<void> resa;
                    sf::Packet t;
                    if(server.listenSocket.receive(t)==sf::Socket::Done) {

                        int x; bool press; float telap;
                        t>>x>>press>>telap;
                        if(x<0) {
                            need_upd=false;
                            if(x==-2) watergirl->SetPosition(fireboy->GetPosition().x, telap);
                        }
                        else need_upd=true;
                        if(need_upd) resa = std::async(std::launch::async,
                                                      [](VisibleGameObject* watergirl,
                                                         int x, bool press, float telap
                                                      ){
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

                                                          watergirl->Update(telap, __event,_gameObjectManager._gameObjects);

                                                      }, watergirl, x, press, telap);
                    }

                    _gameObjectManager.updateAll(_event, telap);

                    _gameObjectManager.drawAll(_mainWindow);

                    if(need_upd){
                        resa.get();
                    }

                    watergirl->Draw(_mainWindow);
                    _mainWindow.display();


                }
                else{ // Client
                    //_gameObjectManager.remove("Fireboy");
                    bool need_upd {false};
                    std::future<void> res;
                    sf::Packet t;
                    if(GameState::client.listenSocket.receive(t)==sf::Socket::Done) {

                        int x; bool press; float telap;
                        t>>x>>press>>telap;
                        if(x<0) {
                            need_upd=false;
                            if(x==-2) fireboy->SetPosition(fireboy->GetPosition().x, telap);

                        }
                        else need_upd=true;
                        if(need_upd) res = std::async(std::launch::async,
                                                      [](VisibleGameObject* fireboy,
                                                      int x, bool press, float telap
                                                      ){

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

                                fireboy->Update(telap, __event,_gameObjectManager._gameObjects);

                        }, fireboy, x, press, telap);
                    }

                    float telap = _gameObjectManager._clock.restart().asSeconds();

                    if (_event.type == sf::Event::Closed) {
                        sf::Packet tDash;
                        tDash<<-1<<false<<0.f;
                        sf::Socket::Status st= client.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt send packet(1) to Server!"<<std::endl; }
                        _state = GameState::state::Exiting;
                        break;
                    }
                    else if(_event.type==sf::Event::KeyPressed || _event.type==sf::Event::KeyReleased){
                        sf::Packet tDash;
                        tDash<<_event.key.code<<(_event.type==sf::Event::KeyPressed) <<telap;
                        sf::Socket::Status st= client.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cerr<<"Couldnt send packet to Server!"<<std::endl;}
                    }
                    else{
                        sf::Packet tDash;
                        tDash<<-1<<false<<watergirl->GetPosition().y;
                        sf::Socket::Status st= client.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt send packet(1) to Server!"<<std::endl; }
                    }
                    _mainWindow.clear(sf::Color{255, 0, 0, 150});
                    _gameObjectManager.updateAll(_event, telap);
                    _gameObjectManager.drawAll(_mainWindow);


                    if(need_upd) {
                        //std::cout<<"Waiting for get!\n";
                        res.get();
                    }
                    fireboy->Draw(_mainWindow);
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


