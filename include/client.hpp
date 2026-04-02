#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

class Client
{
private:
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    std::string ip;
    int port;
    std::string name;

public:
    Client(const std::string &ip, int port, const std::string &name);
    bool initialize();
    bool connectToServer();
    void sendMessages();
    void cleanup();
};