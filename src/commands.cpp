#include "../include/commands.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

Commands::Commands(Server& server, bool& running) : server(server), running(running) {
    registerCommands();
}

void Commands::registerCommands() {
    commandMap["online"] = [&]() {
        cout << "Clientes online: " << server.getConnectedClients() << endl;
    };

    commandMap["clear"] = [&]() {
        system("cls");
    };
}

void Commands::execute(const string& command) {

    if (commandMap.find(command) != commandMap.end()) {
        commandMap[command]();
    } else {
        cout << "Comando desconhecido." << endl;
    }
}