#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

class Server {
private:
    SOCKET serverSocket;
    sockaddr_in serverAddr;
    int port;
    std::string clientName;

public:
    Server(int port);
    bool initialize();
    bool startListening();
    void acceptClients();
    void handleClient(SOCKET clientSocket);
    void cleanup();
};