#pragma once
#pragma GCC diagnostic ignored "-Wunused-result"

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

class Server {
private:
    std::vector<sf::TcpSocket> sockets;
    sf::IpAddress ip = sf::IpAddress::LocalHost;
    unsigned short port = 4171;
    sf::Packet packet = sf::Packet();
public:
    Server(const std::string& ip, unsigned short port) {
        this->ip = *sf::IpAddress::resolve(ip);
        this->port = port;
    }

    void add_client() {
        sockets.push_back(sf::TcpSocket());
        sf::TcpListener listener = sf::TcpListener();
        listener.listen(port);
        if (listener.accept(sockets[sockets.size() - 1]) != sf::Socket::Status::Done) {
            std::cerr << "Error! (Server)" << std::endl;
            return;
        }
        std::cout << "Connected! (Server)" << std::endl;
        sockets[sockets.size() - 1].setBlocking(true);
    }

    std::string receive() {
        for (int i = 0; i < sockets.size(); i++) {
            if (sockets[i].receive(packet) == sf::Socket::Status::Done) {
                std::string message;
                packet >> message;
                return message;
            }
        }

        return "";
    }
};