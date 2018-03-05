#include "MainMenu.h"
#include <iostream>
#include <GameState.h>

MainMenu::MainMenu(float width, float height) {
    std::string fontFileM;
    if(!GameState::filePath) fontFileM="../res/fonts/Phetsarath_OT.ttf";
    else fontFileM="res/fonts/Phetsarath_OT.ttf";
    if(!font.loadFromFile(fontFileM)){
        std::cerr<<"Error Loading Font MainMenu!";
        return;
    }






    items[0].setFont(font);
    items[0].setFillColor(sf::Color::White);
    items[0].setString("Create Server!");
    items[0].setCharacterSize(50);
    sf::FloatRect textRect = items[0].getLocalBounds();
    items[0].setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
    items[0].setPosition(sf::Vector2f(width/2, height/(N_ITEMS+1)*1));
    items[0].setOutlineColor(sf::Color::Black);
    items[0].setOutlineThickness(10.f);

    items[1].setFont(font);
    items[1].setFillColor(sf::Color::White);
    items[1].setString("Join Server!");
    textRect = items[1].getLocalBounds();
    items[1].setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
    items[1].setPosition(sf::Vector2f(width/2, height/(N_ITEMS+1)*2));
    items[1].setOutlineColor(sf::Color::Black);
    items[1].setOutlineThickness(0.f);

    items[2].setFont(font);
    items[2].setFillColor(sf::Color::White);
    items[2].setString("Exit!");
    textRect = items[2].getLocalBounds();
    items[2].setOrigin(textRect.left + textRect.width/2.0f,
                       textRect.top  + textRect.height/2.0f);
    items[2].setPosition(sf::Vector2f(width/2, height/(N_ITEMS+1)*3));
    items[2].setOutlineColor(sf::Color::Black);
    items[2].setOutlineThickness(0.f);

    curIndex=0;
} // Constructor

short MainMenu::show(sf::RenderWindow &renderWindow) {
    renderWindow.clear(sf::Color::White);
    sf::Texture texture;
    std::string splashName;
    if(!GameState::filePath) splashName="../res/img/main_menu.png";
    else splashName="res/img/main_menu.png";
    if(!texture.loadFromFile(splashName)){ // Arg: const string: the path to the image file
        std::cerr<<"Failed to load main_menu img!"<<std::endl;
        return -1; // Error handling here
    }
    sf::Sprite sprite(texture);
    sprite.setScale(GameState::_resX/sprite.getGlobalBounds().width, GameState::_resY/sprite.getGlobalBounds().height);
    renderWindow.draw(sprite);

    for (const auto &item : items) renderWindow.draw(item);
    renderWindow.display();

    sf::Event event;

    while(true){ // Event Handling loop
        while(renderWindow.pollEvent(event)){
            switch (event.type){
                case sf::Event::KeyPressed:{ // Not KeyReleased, since pollEvent (in GameState::gameLoop())
                    // would need another event to actually display something
                    switch (event.key.code){
                        case sf::Keyboard::Up:{
                            up();
                            renderWindow.clear(sf::Color::White);
                            renderWindow.draw(sprite);
                            for (const auto &item : items) renderWindow.draw(item);
                            renderWindow.display();
                            break;
                        }
                        case sf::Keyboard::Down:{
                            down();
                            renderWindow.clear(sf::Color::White);
                            renderWindow.draw(sprite);
                            for (const auto &item : items) renderWindow.draw(item);
                            renderWindow.display();
                            break;
                        }
                        case sf::Keyboard::Return:{
                            return curIndex;
                        }
                        default: break;
                    }
                    break;
                } // key released
                case sf::Event::Closed:{
                    renderWindow.close();
                    return -1;
                    break;
                }
                default: break;
            } // switch type
        } // while
    }
} // show

void MainMenu::up() {
    short nIdx=(curIndex-1+N_ITEMS)%N_ITEMS;
    //items[curIndex].setColor(sf::Color::Blue);
    items[curIndex].setOutlineThickness(0.f);
    items[curIndex].setCharacterSize(30);
    sf::FloatRect textRect = items[curIndex].getLocalBounds();
    items[curIndex].setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top  + textRect.height/2.0f);
    items[curIndex].setPosition(GameState::_resX/2, items[curIndex].getPosition().y);
    //items[nIdx].setColor(sf::Color::Black);
    items[nIdx].setOutlineThickness(10.f);
    items[nIdx].setCharacterSize(50);
    textRect = items[nIdx].getLocalBounds();
    items[nIdx].setOrigin(textRect.left + textRect.width/2.0f,
                          textRect.top  + textRect.height/2.0f);
    items[nIdx].setPosition(GameState::_resX/2, items[nIdx].getPosition().y);

    curIndex=nIdx;
}

void MainMenu::down(){

    short nIdx=(curIndex+1+N_ITEMS)%N_ITEMS;
    //items[curIndex].setColor(sf::Color::Blue);
    items[curIndex].setOutlineThickness(0.f);
    items[curIndex].setCharacterSize(30);
    sf::FloatRect textRect = items[curIndex].getLocalBounds();
    items[curIndex].setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top  + textRect.height/2.0f);
    items[curIndex].setPosition(GameState::_resX/2, items[curIndex].getPosition().y);
    //items[nIdx].setColor(sf::Color::Black);
    items[nIdx].setOutlineThickness(10.f);
    items[nIdx].setCharacterSize(50);
    textRect = items[nIdx].getLocalBounds();
    items[nIdx].setOrigin(textRect.left + textRect.width/2.0f,
                              textRect.top  + textRect.height/2.0f);
    items[nIdx].setPosition(GameState::_resX/2, items[nIdx].getPosition().y);
    curIndex=nIdx;
}
