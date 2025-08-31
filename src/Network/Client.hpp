#pragma once
#pragma GCC diagnostic ignored "-Wunused-result"

#include <SFML/Network.hpp>
#include <iostream>

class Client {
private:
    sf::TcpSocket socket = sf::TcpSocket();
    sf::IpAddress ip = sf::IpAddress::LocalHost;
    unsigned short port = 4171;
    sf::Packet packet = sf::Packet();
public:
    void connect(const std::string& ip, const unsigned short& port) {
        this->ip = *sf::IpAddress::resolve(ip);
        this->port = port;
        if (socket.connect(this->ip, this->port) != sf::Socket::Status::Done) {
            std::cout << "Error! (Client)" << std::endl;
            return;
        }
        std::cout << "Connected! (Client)" << std::endl;
        socket.setBlocking(false);
    }

    void send(const std::string& message) {
        packet.clear();
        packet << message;
        socket.send(packet);
    }

    std::string receive() {
        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::string message;
            packet >> message;
            return message;
        } else return "";
    }
};