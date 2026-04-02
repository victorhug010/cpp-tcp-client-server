#include "../include/server.hpp"
#include "../include/commands.hpp"
#include <thread>
#include <iostream>

int main() {
    Server server(8080);

    
    if (!server.initialize()) {
        return 1;
    }
    
    if (!server.startListening()) {
        return 1;
    }
    
    bool running = true;
    Commands commands(server, running);

    std::thread serverThread(&Server::acceptClients, &server);
    serverThread.detach();
    
    std::string command;
    while (true) {
        std::getline(std::cin, command);

        commands.execute(command);
    }
    // server.acceptClients();
    server.cleanup();
    return 0;
}