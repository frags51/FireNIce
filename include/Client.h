#ifndef FIRENICE_CLIENT_H
#define FIRENICE_CLIENT_H


#include <SFML/Network/TcpSocket.hpp>

class Client {
public:
    Client();
    sf::TcpSocket socket;
};


#endif //FIRENICE_CLIENT_H
