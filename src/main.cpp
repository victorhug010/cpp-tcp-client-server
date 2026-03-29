#include "../include/server.hpp"

int main() {
    Server server(8080);

    if (!server.initialize()) {
        return 1;
    }

    if (!server.startListening()) {
        return 1;
    }

    server.acceptClients();
    server.cleanup();

    return 0;
}