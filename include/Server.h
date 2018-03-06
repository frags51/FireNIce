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
    Server(unsigned short _port1, unsigned short _port2);
    void waitForClientSendSocket(bool *res);
    void waitForClientListenSocket(bool *res);
    //~Server();
    sf::TcpSocket sendSocket;
    sf::TcpSocket listenSocket;
    sf::TcpListener listener;
    sf::TcpListener listener2;
private:
    //! \brief Port for sendSocket.
    unsigned short port1;
    //! \brief Port for listenSocket.
    unsigned short port2;
};


#endif //FIRENICE_SERVER_H
