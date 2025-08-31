#pragma once
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma voice

#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <thread>

#include "Client.hpp"

class Server {
private:
    std::vector<sf::TcpSocket> sockets;
    sf::IpAddress ip = sf::IpAddress::LocalHost;
    unsigned short port = 4171;
    std::size_t clients = 0ull;
    sf::Packet packet = sf::Packet();
public:
    Server(const std::string& ip, unsigned short port) {
        this->ip = *sf::IpAddress::resolve(ip);
        this->port = port;
    }

    bool accept_client() {
        sockets.push_back(sf::TcpSocket());
        sf::TcpListener listener = sf::TcpListener();
        listener.listen(port);
        if (listener.accept(sockets[sockets.size() - 1]) != sf::Socket::Status::Done) {
            std::cerr << "Error! (Server)" << std::endl;
            return false;
        }
        std::cout << "Connected! (Server)" << std::endl;
        sockets[sockets.size() - 1].setBlocking(false);
        ++clients;
        return true;
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

    void send(const std::string& message) {
        for (int i = 0; i < sockets.size(); i++) {
            packet.clear();
            packet << message;
            sockets[i].send(packet);
        }
    }

    std::size_t get_clients_count() {
        return clients;
    }
};