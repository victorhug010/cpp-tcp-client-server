#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <atomic>

#pragma comment(lib, "ws2_32.lib")

class Server {
private:
    SOCKET serverSocket;
    sockaddr_in serverAddr;
    int port;
    std::string clientName;
    std::atomic<int> connectedClients = 0;

public:
    Server(int port);
    bool initialize();
    bool startListening();
    void acceptClients();
    void handleClient(SOCKET clientSocket);
    void cleanup();
    int getConnectedClients();
};