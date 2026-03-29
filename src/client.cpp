#include <iostream>
#include "../include/client.hpp"

using namespace std;

Client::Client(const string& ip, int port, const string& name) {
    this->ip = ip;
    this->port = port;
    this->name = name;

    clientSocket = INVALID_SOCKET;
}

bool Client::initialize() {
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Erro ao iniciar Winsock." << endl;
        return false;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Erro ao criar socket do cliente." << endl;
        WSACleanup();
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

    return true;
}

bool Client::connectToServer() {
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Erro ao conectar ao servidor." << endl;
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    string introMessage = "CLIENT_NAME:" + name;
    send(clientSocket, introMessage.c_str(), introMessage.size(), 0);
    cout << "Conectado ao servidor em " << ip << ":" << port << " como " << name << endl;
    return true;
}

void Client::sendMessages() {
    string message;
    char buffer[1024];

    while (true) {
        cout << "Digite uma mensagem (ou 'exit' para sair): ";
        getline(cin, message);

        if (message == "exit") {
            break;
        }

        send(clientSocket, message.c_str(), message.size(), 0);

        ZeroMemory(buffer, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived > 0) {
            cout << "Resposta do servidor: " << buffer << endl;
        }
    }
}

void Client::cleanup() {
    closesocket(clientSocket);
    WSACleanup();
}