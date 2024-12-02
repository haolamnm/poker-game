#ifndef LOBBY_H
#define LOBBY_H

#include "Login.h"
#include "Gameplay.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Lobby {
private:
    Login login;
    Gameplay game;
    std::vector<std::string> usernames;

public:
    // Getter for usernames
    void assignUsername(const std::string& username);
    void removeUsername(const std::string& username);
    std::vector<std::string> getUsernames();
    void handleGame();
    std::vector<std::vector<std::string>> handleLeaderboard();
};

#endif