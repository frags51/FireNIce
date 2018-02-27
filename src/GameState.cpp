#include "GameState.h"
#include <iostream>

GameState::state GameState::_state = Not_init; // Need to initialize these
sf::RenderWindow GameState::_mainWindow;
task_player fireboy;

void GameState::play() {
    static_assert(_resX <= 1920 && _resY <= 1080, "Invalid Screen Resolution!");
    if(_state!=Not_init) return;

    _mainWindow.create(sf::VideoMode(_resX, _resY, 32), "Fire & Ice");
    _state=state::Playing;
    fireboy.make_player("../res/img/tux.png",(double)_resX/12,(double)_resY/6);

    while(!isExiting()) gameLoop();

    _mainWindow.close();
}

bool GameState::isExiting() {
    return _state==state::Exiting;
}

void GameState::gameLoop() {
    sf::Event _event;
    switch (_state){
        case GameState::state::Playing:{
            const int groundheight = 700;
            while(_mainWindow.pollEvent(_event)) {
                if (_event.type == sf::Event::Closed)
                    _mainWindow.close();
                if(_event.type == sf::Event::KeyReleased)
                    fireboy.isjumping = false;
            } //while
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                fireboy.move_right(5.8f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                fireboy.move_left(5.8f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                if(!fireboy.isjumping)fireboy.move_up(60.8f);
                fireboy.isjumping = true;
            }
            if(fireboy.isjumping == false && groundheight>fireboy.getY()) fireboy.move_down(1.8f);
            _mainWindow.clear(sf::Color::Cyan);
            _mainWindow.draw(fireboy.get_player());
            _mainWindow.display();
            break;
        } // Case Playing.
        default:
            break;
    } //switch
} //gameLoop()
