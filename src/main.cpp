#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <random>
#include <thread>
#include "Network/Client.hpp"
#include "Network/Server.hpp"
#include <chrono>

#pragma voice

// //randomizer)))
// unsigned long long generate_key(){
//     //return 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFULL;
// }



Server server("127.0.0.1", 4171);

Client client1;
Client client2;

void klyde1() {
    client1.connect("127.0.0.1", 4171);
}

void klyde2() {
    client2.connect("127.0.0.1", 4171);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    std::thread klyde1Thread(klyde1);
    klyde1Thread.detach();
    server.add_client();

    std::thread klyde2Thread(klyde2);
    klyde2Thread.detach();
    server.add_client();

    client1.send("aorta2))))))");
    std::cout << server.receive() << std::endl;

    return 0;
}
