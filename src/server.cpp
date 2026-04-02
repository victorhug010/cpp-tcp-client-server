#include <iostream>
#include <thread>
#include "../include/server.hpp"

using namespace std;

Server::Server(int port) {
    this->port = port;
    serverSocket = INVALID_SOCKET;
    // clientName = "";
}

bool Server::initialize() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Erro ao iniciar Winsock." << endl;
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Erro ao criar socket." << endl;
        WSACleanup();
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Erro no bind." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    return true;
}

bool Server::startListening() {
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Erro no listen." << endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    cout << "Servidor TCP rodando na porta " << port << "..." << endl;
    cout << "Aguardando conexoes..." << endl;

    return true;
}

void Server::acceptClients() {
    while (true) {
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);

        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);

        if (clientSocket == INVALID_SOCKET) {
            cout << "Erro ao aceitar cliente." << endl;
            continue;
        }

        cout << "Novo cliente conectado!" << endl;
        connectedClients++;

        thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();
    }
}

void Server::handleClient(SOCKET clientSocket) {
    char buffer[1024];
    string clientName = "Desconhecido";

    while (true) {
        ZeroMemory(buffer, sizeof(buffer));

        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived <= 0) {
            cout << "[" << clientName << "] desconectou." << endl;
            break;
        }

        buffer[bytesReceived] = '\0';
        string message(buffer, bytesReceived);

        if (message.rfind("CLIENT_NAME:", 0) == 0) {
            clientName = message.substr(12);
            cout << "Cliente identificado: " << clientName << endl;
            continue;
        }

        cout << "[" << clientName << "] Mensagem recebida: " << message << endl;

        string response = "ACK: ";
        response += message;

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    connectedClients--;
    closesocket(clientSocket);
}

void Server::cleanup() {
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }

    WSACleanup();
}

int Server::getConnectedClients() {
    return connectedClients;
}