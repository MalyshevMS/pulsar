#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include "Network/Client.hpp"
#include "Network/Server.hpp"
#include <chrono>

#include <SFML/Graphics.hpp>

#pragma voice
#pragma stagnant

bool isServer = false;

Server server("127.0.0.1", 4171);

Client client;

std::string name = "server";

void accept_cls() {
    while (true)
    server.accept_client();
}

void window_func() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Pulsar Client (name: " + name + ")");
    sf::Font font("res/arial.ttf");
    sf::Text text(font);

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        for (auto event = window.pollEvent(); event; event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        auto msg_recv = client.receive();
        static std::string last = "";

        if (msg_recv == "" || msg_recv == last || msg_recv == "\xffvoid\xff") continue;
        last = msg_recv;
        text.setString(msg_recv);
        text.setFillColor(sf::Color::Red);

        window.draw(text);

        window.display();
    }
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    if (argc > 1) {
        if (std::string(argv[1]) == "server") {
            isServer = true;
        }

        if (std::string(argv[1]) == "client") {
            isServer = false;
            name = std::string(argv[2]);
        }
    }
    
    if (isServer) {
        std::thread t(accept_cls);
        t.detach();

        while (true) {
            auto msg = server.receive();
            static std::string last = "";
            static bool isfixed = false;

            if (msg == "" || msg == last) continue;
            std::cout << msg << std::endl;
            server.send(msg);
            last = msg;
        }
    } else {
        client.connect("127.0.0.1", 4171);
        client.send("\xffvoid\xff");

        std::thread t(window_func);
        t.detach();

        while (true) {
            static std::string msg = "";

            std::cout << "<" << name << "> ";
            std::getline(std::cin, msg);

            client.send("<" + name + "> " + msg);            
        }
    }



    return 0;   
}