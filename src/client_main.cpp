#include "../include/client.hpp"
#include <vector>
#include <string>
#include <ctime>

using namespace std;
int main() {
    vector<string> clientNames = {
        "Victor-PC",
        "Notebook-Gamer",
        "ESP32_01",
        "Sensor-Temp",
        "Device-A",
        "Client-Test",
        "Terminal-01",
        "Desktop-Office",
        "Raspberry-Node",
        "IoT-Unit-07"
    };

    srand(time(NULL));
    string randomName = clientNames[rand() % clientNames.size()];
    Client client("127.0.0.1", 8080, randomName);

    if (!client.initialize()) {
        return 1;
    }

    if (!client.connectToServer()) {
        return 1;
    }

    client.sendMessages();
    client.cleanup();

    return 0;
}