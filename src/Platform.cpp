#include "Platform.h"
#include "GameState.h"
#include <cmath>
Platform::Platform(const std::string &texture, sf::Vector2f size, sf::Vector2f position):
        vBarrierMoveDist{550.0f}
{
    Load(texture,size.x,size.y);
    _player.setSize(size);
    _player.setPosition(position);
    _player.setOutlineColor(sf::Color::Black);
    _player.setOutlineThickness(3.f);
    _player.setOrigin(_player.getSize()/2.f);
    if(texture.find("blue_fire_new")!=std::string::npos) {
        animation.create(&playerTexture, sf::Vector2u(3,2),0.3f);
    }
    if(texture.find("red_fire_new")!=std::string::npos) {
        animation.create(&playerTexture, sf::Vector2u(3,3),0.3f);
    }
}
Platform::~Platform() {

}
void Platform::Draw(sf::RenderWindow &window) {
    window.draw(_player);
}

void Platform::Update(float elapsedTime,sf::Event& _event,std::map<std::string, VisibleGameObject*>& _object)
{
    animation.update(1,elapsedTime,true);
    _player.setTextureRect(animation.uvRect);
    //for(auto it:_object){
        //if(it.first.find("vBarrier")!=std::string::npos){
         //   if(checkCollision(it.second, 0.0f)){}

        //}
        /*else if(it.first.find("vbSwitch")!=std::string::npos){

            if(checkCollision(it.second, 1.0f)){
                auto num = it.first.substr(8,1);
                GameState::race.lock();
                if(it.second->_stateOfObj==DEF){
                    // Assuming corresponding vBarrier is always found!
                    VisibleGameObject* bar = _object.find("vBarrier"+num)->second;
                    bar->SetPosition(bar->GetPosition().x, bar->GetPosition().y-vBarrierMoveDist);

                }
                GameState::race.unlock();
                //isCollide=true;
                //isJumping=false;
                //_velocity=0;
            }
            else if(std::find(GameState::_objToBeActed.begin(), GameState::_objToBeActed.end(), it.second)!=GameState::_objToBeActed.end()){
                GameState::race.lock();
                auto num = it.first.substr(8,1);
                VisibleGameObject* bar = _object.find("vBarrier"+num)->second;
                bar->SetPosition(bar->GetPosition().x, bar->GetPosition().y+vBarrierMoveDist);
                bar->_stateOfObj=DEF;
                it.second->_stateOfObj=DEF;
                GameState::_objToBeActed.erase(std::find(GameState::_objToBeActed.begin(), GameState::_objToBeActed.end(), it.second));

                GameState::race.unlock();
            } // Didnt collide, but earlier pressed the switch

        }*/





    } // for iterate over ObjMan

}

bool Platform::checkCollision(VisibleGameObject* other, float e){

    sf::Vector2f otherHalfSize = other->GetHalfSize();
    sf::Vector2f thisHalfSize = GetHalfSize();

    sf::Vector2f otherPosition = other->GetPosition();
    sf::Vector2f thisPosition = GetPosition();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
    if(intersectX<0.0f && intersectY<0.0f) {
        if(other->_filename.find("door")!=std::string::npos){
            return true;
        }
        e = std::min(std::max(e,0.0f),1.0f);
        if( intersectX > intersectY) {

            if(deltaX >0.0f){
                move(intersectX * (1.0f -e),0.0f);
                other->move((-intersectX*e),0.0f);

            }
            else{
                move(-intersectX * (1.0f -e),0.0f);
                other->move(intersectX*e,0.0f);

            }
        }
        else{

            if(deltaY >0.0f){
                move(0.0f,intersectY * (1.0f -e));
                other->move(0.0f,(-intersectY*e));

            }
            else{

                move(0.0f,-intersectY * (1.0f -e));
                other->move(0.0f,intersectY*e);
            }
        }

        return true;
    }


    return false;
}
