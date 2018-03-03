#include "LevelMenu.h"
#include <iostream>
#include <GameState.h>

LevelMenu::LevelMenu(float width, float height) {
    std::string fontFileM;
    if(!GameState::filePath) fontFileM="../res/fonts/Phetsarath_OT.ttf";
    else fontFileM="res/fonts/Phetsarath_OT.ttf";
    if(!font.loadFromFile(fontFileM)){
        std::cerr<<"Error Loading Font LevelMenu!";
        return;
    }

    item.setFont(font);
    item.setFillColor(sf::Color::Black);
    item.setPosition(sf::Vector2f(width/2, height/(2)*1));


    curIndex=1;
    item.setString("Your choosen level"+std::to_string(curIndex));
} // Constructor

unsigned short LevelMenu::show(sf::RenderWindow &renderWindow) {
    renderWindow.draw(item);
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

                            renderWindow.draw(item);
                            renderWindow.display();
                            break;
                        }
                        case sf::Keyboard::Down:{
                            down();
                            renderWindow.draw(item);
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
                    return 0;
                    break;
                }
                default: break;
            } // switch type
        } // while
    }
} // show

void LevelMenu::up() {
    if (curIndex < N_LEVELS)
    {
        curIndex++;
    }
    item.setString("Your choosen level"+std::to_string(curIndex));
}

void LevelMenu::down(){
    if (curIndex > 0)
    {
        curIndex--;
    }
    item.setString("Your choosen level"+std::to_string(curIndex));
}
