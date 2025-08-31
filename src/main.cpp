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
        client.send("\xff\xff");

        while (true) {
            static std::string msg = "";

            std::cout << "<" << name << "> ";
            std::getline(std::cin, msg);

            client.send("<" + name + "> " + msg);

            // auto msg_recv = client.receive();
            // static std::string last = "";

            // if (msg_recv == "" || msg_recv == last || msg_recv == "\xffvoid\xff") continue;
            // last = msg_recv;
            // std::cout << msg_recv << std::endl;
        }
    }



    return 0;   
}