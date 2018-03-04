#include "Player.h"
#include "GameState.h"
#include <cmath>

Player::Player(const std::string &fName, sf::Keyboard::Key _u, sf::Keyboard::Key _l, sf::Keyboard::Key _r) :
        _velocity(0),
        _maxVelocity(600.0f),
        dJump {0.f},
        isRPressed{false},
        isLPressed{false},
        isUpPressed{false},
        u{_u},
        l{_l},
        r{_r},
        _xVal {550.f},
        _upVel {550.f},
        vBarrierMoveDist{105.f}


{
    Load(fName, GameState::_resX/16,GameState::_resY/8);
    animation.create(&playerTexture,sf::Vector2u(3,9),0.3f);
    isJumping=false;
    _player.setOutlineColor(sf::Color::Black);
    _player.setOutlineThickness(3.f);
    _player.setOrigin(_player.getSize()/2.f);
}


Player::~Player() {

}



void Player::Update(float elapsedTime,sf::Event& _event,std::map<std::string, VisibleGameObject*>& _object)
{
    bool isCollide = false;
    bool isThisFireboy = this->_filename.find("red_tux")!=std::string::npos;
    int row =0;
    bool toRight = true;
    for(auto it:_object){
        //std::cout<<it.first<<" "<<it.second->GetPosition().x<<std::endl;

            if(it.first.find("Plt")!=std::string::npos){ // Check collision with platforms
                if(checkCollision(it.second,0.0f)){
                    //std::cout<<this->GetPosition().x<<" "<<this->GetPosition().y<<"; "<<it.second->GetPosition().x<<" "<<it.second->GetPosition().y<<"\n";
                    //std::cout<<this->GetHalfSize().x*2<<" "<<this->GetHalfSize().y*2<<"; "<<it.second->GetHalfSize().x*2<<" "<<it.second->GetHalfSize().y*2<<"\n";

                    isCollide = true;
                    isJumping = false;
                    _velocity=0;
                }
            }

            else if(it.first.find("vbSwitch")!=std::string::npos){

                if(checkCollision(it.second, 0.0f)){
                    auto num = it.first.substr(8,1);
                    GameState::race.lock();
                    if(it.second->_stateOfObj==DEF){
                        // Assuming corresponding vBarrier is always found!
                        VisibleGameObject* bar = _object.find("vBarrier"+num)->second;
                        {bar->SetPosition(bar->GetPosition().x, bar->GetPosition().y-vBarrierMoveDist); std::cout<<"Moved!\n";}
                        bar->_stateOfObj=VBMOVED;
                        it.second->_stateOfObj=isThisFireboy? VBSPRESSED_F:VBSPRESSED_W;
                        GameState::_objToBeActed.push_back(it.second);
                    }
                    GameState::race.unlock();
                }
                else if(std::find(GameState::_objToBeActed.begin(), GameState::_objToBeActed.end(), it.second)!=GameState::_objToBeActed.end()){
                    GameState::race.lock();
                    if(isThisFireboy && it.second->_stateOfObj==VBSPRESSED_F){
                        auto num = it.first.substr(8,1);
                        VisibleGameObject* bar = _object.find("vBarrier"+num)->second;
                        bar->SetPosition(bar->GetPosition().x, bar->GetPosition().y+vBarrierMoveDist);
                        std::cout<<"Back!\n";
                        bar->_stateOfObj=DEF;
                        it.second->_stateOfObj=DEF;
                        GameState::_objToBeActed.erase(std::find(GameState::_objToBeActed.begin(), GameState::_objToBeActed.end(), it.second));
                    }
                    else if(!isThisFireboy && it.second->_stateOfObj==VBSPRESSED_W){
                        auto num = it.first.substr(8,1);
                        VisibleGameObject* bar = _object.find("vBarrier"+num)->second;
                        bar->SetPosition(bar->GetPosition().x, bar->GetPosition().y+vBarrierMoveDist);
                        std::cout<<"Back!\n";
                        bar->_stateOfObj=DEF;
                        it.second->_stateOfObj=DEF;
                        GameState::_objToBeActed.erase(std::find(GameState::_objToBeActed.begin(), GameState::_objToBeActed.end(), it.second));
                    }
                    GameState::race.unlock();
                } // Didnt collide, but earlier pressed the switch

            }
            else if(isThisFireboy && (it.first.find("Blue_fire") != std::string::npos || it.first.find("Green_fire") != std::string::npos)){
                if(checkCollision(it.second,0.0f)) {
                    isCollide=true;
                    GameState::_state = GameState::state::GameOver;

                }
            }
            else if(!isThisFireboy && (it.first.find("Red_fire") != std::string::npos || it.first.find("Green_fire") != std::string::npos)){
                if(checkCollision(it.second, 0.0f)){
                    isCollide=true;
                    GameState::_state = GameState::state::GameOver;
                }
            }
            else if(isThisFireboy && it.first.find("Red_gem")!=std::string::npos){
                if(checkCollision(it.second, 0.0f)){
                    GameState::_objToBeActed.push_back(it.second);
                }
            }
    } // for iterate over ObjMan
    if(isCollide) return ;

    if((_event.type==sf::Event::KeyPressed && _event.key.code==l) || isLPressed)
    {
        isLPressed=true;
        _player.move(-_xVal*elapsedTime,0);
        row =1;
        toRight = false;
    }
    if((_event.type==sf::Event::KeyPressed && _event.key.code==r) || isRPressed)
    {
        isRPressed=true;
        _player.move(_xVal*elapsedTime,0);
        row =1;
    }
    if(((_event.type==sf::Event::KeyPressed && _event.key.code==u) || isUpPressed) && !isJumping)
    {
        isUpPressed=true;
        row = 2;
        //_player.move(0, -2.f);
        _player.move(0, -_upVel*elapsedTime);
    }
    if((_event.type==sf::Event::KeyReleased && _event.key.code==l)) isLPressed=false;
    if((_event.type==sf::Event::KeyReleased && _event.key.code==r)) isRPressed=false;
    if((_event.type==sf::Event::KeyReleased && _event.key.code==u)) {isUpPressed=false;isJumping=true;}


    // Simulate Gravity -> Add Collision platform detection here
    if(isJumping && _player.getPosition().y < GameState::_resY-GameState::_resY/8) {
        _velocity+=1.f;
        _player.move(0,_velocity*elapsedTime);
        dJump=0.f;
    }
    else if(!isJumping){
        dJump+=_upVel*elapsedTime;
        if(dJump>=150.f) isJumping=true;
    }
    else {_velocity=0;isJumping=false;}

    if(_velocity > _maxVelocity)
        _velocity = _maxVelocity;

    if(_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;
    animation.update(row,elapsedTime,toRight);
    _player.setTextureRect(animation.uvRect);


}

bool Player::checkCollision(VisibleGameObject* other, float e){
    sf::Vector2f otherHalfSize = other->GetHalfSize();
    sf::Vector2f thisHalfSize = GetHalfSize();

    sf::Vector2f otherPosition = other->GetPosition();
    sf::Vector2f thisPosition = GetPosition();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);
    if(intersectX<0.0f && intersectY<0.0f) {
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





