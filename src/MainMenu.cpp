#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(float width, float height) {
    if(!font.loadFromFile("../res/fonts/Phetsarath_OT.ttf")){
        std::cerr<<"Error Loading Font MainMenu!";
        return;
    }

    items[0].setFont(font);
    items[0].setFillColor(sf::Color::Black);
    items[0].setString("Create Server!");
    items[0].setPosition(sf::Vector2f(width/2, height/(N_ITEMS+1)*1));

    items[1].setFont(font);
    items[1].setFillColor(sf::Color::Blue);
    items[1].setString("Join Server!");
    items[1].setPosition(sf::Vector2f(width/2, height/(N_ITEMS+1)*2));

    items[2].setFont(font);
    items[2].setFillColor(sf::Color::Blue);
    items[2].setString("Exit!");
    items[2].setPosition(sf::Vector2f(width/2, height/(N_ITEMS+1)*3));

    curIndex=0;
} // Constructor

short MainMenu::show(sf::RenderWindow &renderWindow) {
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

                            for (const auto &item : items) renderWindow.draw(item);
                            renderWindow.display();
                            break;
                        }
                        case sf::Keyboard::Down:{
                            down();
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
    items[curIndex].setColor(sf::Color::Blue);
    items[nIdx].setColor(sf::Color::Black);
    curIndex=nIdx;
}

void MainMenu::down(){
    short nIdx=(curIndex+1)%N_ITEMS;
    items[curIndex].setColor(sf::Color::Blue);
    items[nIdx].setColor(sf::Color::Black);
    curIndex=nIdx;
}
