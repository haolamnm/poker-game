#ifndef LOBBY_H
#define LOBBY_H

#include "Login.h"
#include "Gameplay.h"
#include <vector>
#include <string>
#include <iostream>

class Lobby {
private:
    Login login;
    Gameplay game;
    std::vector<std::string> usernames;

public:
    // Getter for usernames
    void assignUsername(std::string username);
    std::vector<std::string> getUsernames();
    void handleGame();
    std::vector<std::vector<std::string>> handleLeaderboard();
};

#endif