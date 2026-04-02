#include <string>
#include <unordered_map>
#include <functional>
#include "server.hpp"

class Commands {
private:
    Server& server;
    bool& running;

    std::unordered_map<std::string, std::function<void()>> commandMap;

    void registerCommands();

public:
    Commands(Server& server, bool& running);
    void execute(const std::string& command);
};