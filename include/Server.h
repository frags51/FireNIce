/**
 * \brief A server over TCP to enable networking.
 */


#ifndef FIRENICE_SERVER_H
#define FIRENICE_SERVER_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <future>

class Server {
public:
    Server(unsigned short port);
    void waitForClient(bool *res);
    //~Server();
    sf::TcpSocket client;
    std::thread worker;
    void send(sf::Vector2f v);
    sf::Socket::Status sdrive(sf::Vector2f v);
    void checkSent();
    sf::Packet recd;
private:
    std::future<sf::Socket::Status> sentStatus;
    //! \brief The Client's IP address (Only 1 possible)
    sf::TcpListener listener;
    unsigned short port;
};


#endif //FIRENICE_SERVER_H
