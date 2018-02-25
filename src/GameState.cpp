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
    fireboy.make_player("resources/images/tux.png",(double)_resX/12,(double)_resY/6);

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
            while(_mainWindow.pollEvent(_event)) {
                if (_event.type == sf::Event::Closed)
                    _mainWindow.close();
            } //while
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                fireboy.move_right(0.9f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                fireboy.move_left(0.9f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                fireboy.move_up(0.9f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                fireboy.move_down(0.9f);
            }
            _mainWindow.clear(sf::Color::White);
            _mainWindow.draw(fireboy.get_player());
            _mainWindow.display();
            break;
        } // Case Playing.
        default:
            break;
    } //switch
} //gameLoop()
