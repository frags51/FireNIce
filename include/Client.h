#ifndef FIRENICE_CLIENT_H
#define FIRENICE_CLIENT_H


#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <thread>
#include <future>
/*!
 * @class Client
 * @brief Stores info reg. the connection with another "server".
 */
class Client {
public:
    /*!
     * @brief The default constructor.
     */
    Client() = default;
    /*!
     * @brief TcpSocket used by client to send info to the server.
     */
    sf::TcpSocket sendSocket;
    /*!
     * @brief TcpSocket used by client to receive info from the server.
     */
    sf::TcpSocket listenSocket;
};


#endif //FIRENICE_CLIENT_H
