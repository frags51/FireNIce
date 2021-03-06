#include "MainMenu.h"
#include "GameState.h"
#include "Splash.h"
#include <fstream>
#include "LevelMenu.h"
#include <thread>

GameState::state GameState::_state = Not_init; // Need to initialize these
sf::RenderWindow GameState::_mainWindow;

unsigned short GameState::port1 {52977};
unsigned short GameState::port2 {18300};


Server GameState::server{GameState::port1, GameState::port2};
Client GameState::client{};

ObjMan GameState::_gameObjectManager;

bool GameState::filePath {true}; // false for linux, true for OSX

bool GameState::isClient;

unsigned short GameState::_curLevel {0};

Player* GameState::fireboy= nullptr;
Player* GameState::watergirl= nullptr;

std::mutex GameState::race;
std::vector<VisibleGameObject *> GameState::_objToBeActed;

unsigned short GameState::redGemsCollected {0};
unsigned short GameState::blueGemsCollected {0};
unsigned short GameState::maxRedGems {0};
unsigned short GameState::maxBlueGems {0};

bool GameState::_winF {false};
bool GameState::_winI {false};

sf::Texture texture;
std::string splashName;
sf::Sprite sprite;

void GameState::play() {
    //LoadFromFile(1);
    if(!GameState::filePath) splashName="../res/img/levelbg.png";
    else splashName="res/img/levelbg.png";
    if(!texture.loadFromFile(splashName)){ // Arg: const string: the path to the image file
        std::cerr<<"Failed to load level bg splash img!"<<std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(GameState::_resX/sprite.getGlobalBounds().width, GameState::_resY/sprite.getGlobalBounds().height);

    static_assert(_resX <= 1920 && _resY <= 1080, "Invalid Screen Resolution!");
    if(_state!=Not_init) return;
    _mainWindow.create(sf::VideoMode(_resX, _resY, 32), "Fire & Ice");
    // Warning: Do not change name of textures of fireboy/watergirl -> Used in Player::Update to check if
    // Object is fireboy or not

    _state=state::AtSplash;

    while(!isExiting()) {
        gameLoop();
    }
    if(isClient){
        client.sendSocket.disconnect();
        client.listenSocket.disconnect();
    }
    else{
        server.listener.close();
        server.listener2.close();
    }
    _mainWindow.close();
} // play()

bool GameState::isExiting() {
    return _state==state::Exiting;
} // isExiting

void GameState::gameLoop() {
    sf::Event _event;
    _mainWindow.pollEvent(_event);
    Stater: switch (_state) {
            case GameState::state::AtSplash: {
                showSplashScreen();
            }
                break; // Showing Splash screen

            case GameState::state::LevelCheck: {
                showLevelScreen();
            }
                break;
            case GameState::state::AtMenu: {
                showMainMenu();
            }
                break; // Showing Main Menu
            case GameState::state::WaitForClient: {
                bool res {false};
                bool res2 {false};
                //std::future<void> g1, g2;
                //g1 = std::async(std::launch::async, &Server::waitForClientSendSocket, &server, &res);
                //g2 = std::async(std::launch::async, &Server::waitForClientListenSocket, &server, &res2)
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
                while (!res || !res2){
                    _mainWindow.pollEvent(_event);
                    if(_event.type==sf::Event::Closed){
                        std::cout<<"Clsoe!\n";
                        _state=Exiting;
                        //server.listener2.close();
                        //server.listener.close();
                        goto Stater;
                    }
                } // Wait to get connection
                t1.join();
                t2.join();

                std::cout << "Connected to: " << server.sendSocket.getRemoteAddress() << std::endl;
                isClient = false;
                sf::Packet selected_level;
                selected_level<<GameState::_curLevel;
                // Destroy already existing things and load here.
                if(!_gameObjectManager._gameObjects.empty())for(auto v:_gameObjectManager._gameObjects){
                    _gameObjectManager.removeAndDelete(v.first);
                }

                std::cout<<_curLevel<<"\n";
                LoadFromFile(_curLevel);


                redGemsCollected=0;
                blueGemsCollected=0;

                _winF=false;
                _winI=false;

                server.sendSocket.send(selected_level);
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
                            if (_event.text.unicode != 13 && _event.text.unicode != 10 && _event.text.unicode!=8)
                                enter += static_cast<char>(_event.text.unicode);
                            else if(_event.text.unicode==8){
                                if(enter.length()>0)
                                enter = enter.substr(0, enter.length()-1);
                                dmsg.setString(enter);
                                _mainWindow.draw(dmsg);
                                _mainWindow.display();
                            }
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

                                    std::cout<<"Connected@\n";
                                    isClient = true;
                                    sf::Packet selected_level;
                                    client.listenSocket.receive(selected_level);
                                    selected_level>>GameState::_curLevel;

                                    // Destroy already existing things and load here.
                                    if(!_gameObjectManager._gameObjects.empty())for(auto v:_gameObjectManager._gameObjects){
                                        _gameObjectManager.removeAndDelete(v.first);
                                    }

                                    LoadFromFile(_curLevel);


                                    redGemsCollected=0;
                                    blueGemsCollected=0;

                                    _winF=false;
                                    _winI=false;

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
                _mainWindow.clear(sf::Color::White);
                _mainWindow.draw(sprite); // Draw level bg.

                if(!isClient){ // Server
                    _gameObjectManager.remove("Watergirl");

                    server.sendSocket.setBlocking(true);
                    //_mainWindow.clear(sf::Color{255, 0, 0, 150});

                    float telap = _gameObjectManager._clock.restart().asSeconds();
                    if (_event.type == sf::Event::Closed) {
                        sf::Packet tDash;
                        tDash<<-1<<false<<0.f;
                        sf::Socket::Status st= server.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt send packet(1) to Server!"<<std::endl; }
                        _state = GameState::state::Exiting;
                        server.sendSocket.disconnect();
                        GameState::server.listenSocket.disconnect(); delete(watergirl);
                        break;
                    }
                    else if(_event.type==sf::Event::KeyPressed || _event.type==sf::Event::KeyReleased){
                        sf::Packet tDash;
                        tDash<<_event.key.code<<(_event.type==sf::Event::KeyPressed) <<telap<<fireboy->GetPosition().x<<fireboy->GetPosition().y;
                        sf::Socket::Status st= server.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cerr<<"Couldnt upd packet"<<std::endl;}
                    }
                    else {
                        sf::Packet tDash;
                        tDash<<-2<<false<<fireboy->GetPosition().y<<fireboy->GetPosition().x;
                        sf::Socket::Status st= server.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt upd packet"<<std::endl; }
                    }

                    bool need_upd {false};
                    std::future<void> resa;
                    sf::Packet t;
                    if(server.listenSocket.receive(t)==sf::Socket::Done) {

                        int x; bool press; float telap, XX, YY;
                        t>>x>>press>>telap;
                        if(x<0) {
                            need_upd=false;
                            if(x==-2) {
                                float xP;
                                t>>xP;
                                watergirl->SetPosition(watergirl->GetPosition().x, telap);
                            }
                            else if(x==-3){
                                _state=GameState::GameOver;
                            }
                            else if(x==-4){
                                _state=GameState::GameWon;
                            }
                        }
                        else {need_upd=true;t>>XX>>YY;}
                        if(need_upd) resa = std::async(std::launch::async,
                                                      [=](VisibleGameObject* watergirl,
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
                                                          watergirl->SetPosition(XX, YY);
                                                          watergirl->Update(telap, __event,_gameObjectManager._gameObjects);

                                                      }, watergirl, x, press, telap);
                    }

                    _gameObjectManager.updateAll(_event, telap);

                    _gameObjectManager.drawAll(_mainWindow);

                    if(need_upd){
                        resa.get();
                    }
                    else{
                        sf::Event::KeyEvent data;
                        data.code = (sf::Keyboard::Num4);
                        data.alt = false;
                        data.control = false;
                        data.shift = false;
                        data.system = false;

                        sf::Event __event;
                        __event.type = sf::Event::KeyPressed;
                        __event.key = data;
                        watergirl->Update(telap,__event,_gameObjectManager._gameObjects);
                    }
                    /*for(auto v: _objToBeActed){
                        if(v->getFileName()=="Red_gem"){
                            redGemsCollected++;

                        }
                    }*/
                    watergirl->Draw(_mainWindow);
                    _mainWindow.display();


                }
                else{ // Client
                    _gameObjectManager.remove("Fireboy");
                    bool need_upd {false};
                    std::future<void> res;
                    sf::Packet t;
                    if(GameState::client.listenSocket.receive(t)==sf::Socket::Done) {

                        int x; bool press; float telap, XX, YY;
                        t>>x>>press>>telap;
                        if(x<0) {
                            need_upd=false;
                            if(x==-2) {
                                float xP;
                                t>>xP;

                                fireboy->_player.setTextureRect(fireboy->animation.uvRect);
                                fireboy->SetPosition(xP, telap);

                            }
                            else if(x==-3){
                                _state=GameState::GameOver;
                            }
                            else if(x==-4){
                                _state=GameState::GameWon;
                            }
                        }
                        else {need_upd=true; t>>XX>>YY;}
                        if(need_upd) res = std::async(std::launch::async,
                                                      [=](VisibleGameObject* fireboy,
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
                                                          fireboy->SetPosition(XX,YY);

                        }, fireboy, x, press, telap);
                    }

                    float telap = _gameObjectManager._clock.restart().asSeconds();

                    if (_event.type == sf::Event::Closed) {
                        sf::Packet tDash;
                        tDash<<-1<<false<<0.f;
                        sf::Socket::Status st= client.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt send packet(1) to Server!"<<std::endl; }
                        client.sendSocket.disconnect();
                        client.listenSocket.disconnect();delete(fireboy);
                        _state = GameState::state::Exiting;
                        //client.listenSocket.disconnect();delete(fireboy);
                        break;
                    }
                    else if(_event.type==sf::Event::KeyPressed || _event.type==sf::Event::KeyReleased){
                        sf::Packet tDash;
                        tDash<<_event.key.code<<(_event.type==sf::Event::KeyPressed) <<telap<<watergirl->GetPosition().x<<watergirl->GetPosition().y;
                        sf::Socket::Status st= client.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cerr<<"Couldnt send packet to Server!"<<std::endl;}
                    }
                    else{
                        sf::Packet tDash;
                        tDash<<-1<<false<<watergirl->GetPosition().y<<watergirl->GetPosition().x;
                        sf::Socket::Status st= client.sendSocket.send(tDash);
                        if(st!=sf::Socket::Done) {std::cout<<"Couldnt send packet(1) to Server!"<<std::endl; }
                    }
                    //_mainWindow.clear(sf::Color{255, 0, 0, 150});
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

            case GameState::state ::GameOver:{
                if(!isClient){
                    sf::Packet y;
                    y<<-3<<false<<0;
                    server.sendSocket.send(y);
                }
                else{
                    sf::Packet y;
                    y<<-3<< false<<0;
                    client.sendSocket.send(y);
                }
                sf::Text gT;
                gT.setString("Game OVER! Press any Key to Continue!");
                gT.setCharacterSize(42);
                gT.setPosition(GameState::_resX/2-400, GameState::_resY/2);
                gT.setFillColor(sf::Color::Black);
                gT.setOutlineThickness(10.f);
                gT.setFillColor(sf::Color::White);
                gT.setOutlineColor(sf::Color::Black);
                sf::Font font;
                std::string fontFileM;
                if(!GameState::filePath) fontFileM="../res/fonts/Phetsarath_OT.ttf";
                else fontFileM="res/fonts/Phetsarath_OT.ttf";
                if(!font.loadFromFile(fontFileM)){
                    std::cerr<<"Error Loading Font MainMenu!";
                    return;
                }
                gT.setFont(font);

                int row = 8;
                bool toRight = true;
                for(int i=0;i<500;i++){
                    _mainWindow.pollEvent(_event);
                    _mainWindow.clear(sf::Color::Red);
                    _mainWindow.draw(sprite); // Level Bg
                    float telap = _gameObjectManager._clock.restart().asSeconds();
                    fireboy->animation.update(row, telap, toRight);
                    fireboy->_player.setTextureRect(fireboy->animation.uvRect);
                    watergirl->animation.update(row, telap, toRight);
                    watergirl->_player.setTextureRect(watergirl->animation.uvRect);
                    _gameObjectManager.drawAll(_mainWindow);
                    if(!isClient) watergirl->Draw(_mainWindow);
                    else fireboy->Draw(_mainWindow);
                    _mainWindow.display();
                    _mainWindow.draw(gT);
                }
                _mainWindow.display();
                sf::Event event;
                while(!_mainWindow.pollEvent(event) || event.type!=sf::Event::KeyPressed);

                if(!isClient) {
                    _state=GameState::state::AtMenu;server.sendSocket.disconnect();
                    server.listenSocket.disconnect();}
                else {
                    _state=GameState::state::AtMenu;client.sendSocket.disconnect();client.listenSocket.disconnect();
                }
            }
            break;

            case GameState::state::GameWon:{
                if(!isClient){
                    sf::Packet y;
                    y<<-4<<false<<0;
                    server.sendSocket.send(y);
                }
                else{
                    sf::Packet y;
                    y<<-4<< false<<0;
                    client.sendSocket.send(y);
                }
                sf::Text gT;
                gT.setString("Game Won! Press any key to continue!");
                gT.setPosition(500, 450);
                gT.setCharacterSize(42);
                gT.setOutlineThickness(10.f);
                gT.setFillColor(sf::Color::White);
                gT.setOutlineColor(sf::Color::Black);
                sf::Font font;
                std::string fontFileM;
                if(!GameState::filePath) fontFileM="../res/fonts/Phetsarath_OT.ttf";
                else fontFileM="res/fonts/Phetsarath_OT.ttf";
                if(!font.loadFromFile(fontFileM)){
                    std::cerr<<"Error Loading Font MainMenu!";
                    return;
                }
                gT.setFont(font);

                int row = 6;
                bool toRight = false;
                for(int i=0;i<600;i++){
                    _mainWindow.pollEvent(_event);
                    _mainWindow.clear(sf::Color::Red);
                    _mainWindow.draw(sprite); // Level Bg
                    float telap = _gameObjectManager._clock.restart().asSeconds();
                    fireboy->animation.update(row, telap, toRight);
                    fireboy->_player.setTextureRect(fireboy->animation.uvRect);
                    watergirl->animation.update(row, telap, toRight);
                    watergirl->_player.setTextureRect(watergirl->animation.uvRect);
                    _gameObjectManager.drawAll(_mainWindow);
                    if(!isClient) watergirl->Draw(_mainWindow);
                    else fireboy->Draw(_mainWindow);
                    _mainWindow.display();
                }
                _mainWindow.draw(gT);
                _mainWindow.display();
                sf::Event event;
                while(!_mainWindow.pollEvent(event) || event.type!=sf::Event::KeyPressed);
                _state = GameState::state ::AtMenu;
                if(!isClient) {
                    _state=GameState::state::AtMenu;server.sendSocket.disconnect();
                    server.listenSocket.disconnect();}
                else {
                    client.sendSocket.disconnect();client.listenSocket.disconnect();
                }
            }
            break;

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
    else if(res==0) GameState::_state=LevelCheck;
    else if(res==1) _state=WaitForServer;
}

void GameState::LoadFromFile(unsigned int level) {
    std::string s = "Level";
    s = "res/" + s + std::to_string(level) + ".txt";
    std::ifstream infile;
    if(!filePath) s = "../"+s;
    infile.open(s);
    infile>>maxRedGems>>maxBlueGems;
    std::string t;
    while (infile >> t) {
        std::string header;
        header = t;
        infile >> t;
        std::string src;
        if (!filePath) src = "../" + t;
        else src = t;
        infile >> t;
        float x = std::stof(t);
        infile >> t;
        float y = std::stof(t);
        infile >> t;
        float size_x = std::stof(t);
        infile >> t;
        float size_y = std::stof(t);
        if(header=="Fireboy"){
            GameState::fireboy=new Player(src, sf::Keyboard::Up,sf::Keyboard::Left, sf::Keyboard::Right);
            fireboy->SetPosition(x+size_x/2.f, y+size_y/2.f);
            _gameObjectManager.add(header, fireboy);
        }
        else if(header=="Watergirl"){
            GameState::watergirl=new Player(src, sf::Keyboard::Up,sf::Keyboard::Left, sf::Keyboard::Right);
            watergirl->SetPosition(x+size_x/2.f, y+size_y/2.f);
            _gameObjectManager.add(header, watergirl);
        }
        else{
            Platform *platform2 = new Platform(src, sf::Vector2f(size_x, size_y), sf::Vector2f(x+size_x/2.f, y+size_y/2.f));
            _gameObjectManager.add(header, platform2);
        }
    }
    infile.close();
}




void GameState::showLevelScreen(){
    LevelMenu mm(_mainWindow.getSize().x, _mainWindow.getSize().y);
    short res = mm.show(_mainWindow);
    if(res==0) _state=Exiting;
    else{
        _curLevel = res;
        _state=WaitForClient;
    }
}


