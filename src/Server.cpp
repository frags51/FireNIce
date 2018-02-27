#include "Server.h"
#include <iostream>

Server::Server(unsigned short port): port{port} {};

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
