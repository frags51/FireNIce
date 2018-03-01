#include <iostream>
#include "Client.h"

Client::Client() {}

void Client::receive() {
    recdStatus = std::async(&Client::rdr, this);
}

sf::Socket::Status Client::rdr() {
    return this->listenSocket.receive(recd);
};


