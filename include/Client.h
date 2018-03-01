#ifndef FIRENICE_CLIENT_H
#define FIRENICE_CLIENT_H


#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <thread>
#include <future>

class Client {
public:
    Client();
    sf::TcpSocket sendSocket;
    sf::TcpSocket listenSocket;
    std::thread worker;
    sf::Packet recd;
    std::future<sf::Socket::Status> recdStatus;
    void receive();
    sf::Socket::Status rdr();
};


#endif //FIRENICE_CLIENT_H
