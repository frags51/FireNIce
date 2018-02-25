#include "GameState.h"

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
    while(_mainWindow.pollEvent(_event)){
        switch (_state){
            case GameState::state::Playing:{
                _mainWindow.clear(sf::Color::White);
                _mainWindow.draw(fireboy.get_player());
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
