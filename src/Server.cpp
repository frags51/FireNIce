#include "Server.h"
#include <iostream>

Server::Server(unsigned short port): port{port} {std::thread worker;};

void Server::waitForClient(bool *res) {
    if(listener.listen(this->port)!=sf::Socket::Done){
        std::cerr<<"Server error while listening @ the port"<<std::endl;
    }
    if(listener.accept(client) != sf::Socket::Done){
        std::cerr<<"Error while accepting conection"<<std::endl;
    }
    listener.close();
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
    return this->client.send(p);
}
