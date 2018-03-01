#include "Server.h"
#include <iostream>

Server::Server(unsigned short _port1, unsigned short _port2): port1{_port1}, port2{_port2} {std::thread worker;};

void Server::waitForClientSendSocket(bool *res) {
    if(listener.listen(this->port1)!=sf::Socket::Done){
        std::cerr<<"Server error while listening @ the port1"<<std::endl;
    }
    if(listener.accept(sendSocket) != sf::Socket::Done){
        std::cerr<<"Error while accepting sendSocket conection"<<std::endl;
    }
    listener.close();
    *res=true;
}


void Server::waitForClientListenSocket(bool *res) {
    if(listener2.listen(this->port2)!=sf::Socket::Done){
        std::cerr<<"Server error while listening @ the port2"<<std::endl;
    }
    if(listener2.accept(listenSocket) != sf::Socket::Done){
        std::cerr<<"Error while accepting listenSocket conection"<<std::endl;
    }
    listener2.close();
    *res=true;
}

void Server::send(sf::Vector2f v) {
    worker=std::thread(&Server::sdrive, this, v);
}

void Server::checkSent() {
    if(worker.joinable()) worker.join();
}

sf::Socket::Status Server::sdrive(sf::Vector2f v) {
    sf::Packet p;
    p << v.x<<v.x;
    return this->sendSocket.send(p);
}
