/**
 * \brief A server over TCP to enable networking.
 */


#ifndef FIRENICE_SERVER_H
#define FIRENICE_SERVER_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <thread>
#include <future>
/*!
 * @class Server
 * @brief Contains information regarding the network connection with another "Client"
 */
class Server {
public:
    /*!
     * @brief The constructor
     * @param _port1 The port used by this to send info to the client.
     * @param _port2 The port used by this to receive info from the client.
     */
    Server(unsigned short _port1, unsigned short _port2);
    /*!
     * @brief Listen to and accept connections from the client at _port1.
     * @param res Store the success/failure of this function in this location.
     */
    void waitForClientSendSocket(bool *res);
    /*!
     * @brief Listen to and accept connections from the client at _port2.
     * @param res Store the success/failure of this function in this location.
     */
    void waitForClientListenSocket(bool *res);
    //~Server();
    /*!
     * @brief TcpSocket used by server to send info to the client.
     */
    sf::TcpSocket sendSocket;
    /*!
     * @brief TcpSocket used by server to receive info from the client.
     */
    sf::TcpSocket listenSocket;

    /*!
     * @brief This listens to connections at _port1.
     */
    sf::TcpListener listener;
    /*!
     * @brief This listens to connections at _port2.
     */
    sf::TcpListener listener2;
private:
    //! \brief Port for sendSocket.
    unsigned short port1;
    //! \brief Port for listenSocket.
    unsigned short port2;
};


#endif //FIRENICE_SERVER_H
