/*
FILE: include/core/Lobby.h

DESCRIPTION: Header file for the lobby class. This file contains 
the class declaration for the lobby of the game. In lobby class, 
we handle the username of the players being added or removed 
from the lobby.

NOTE: The lobby is where the players wait for the game to start.

AUTHOR: Le Nguyen Anh Tri.
*/

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
    void assignUsername(const std::string& username);
    void removeUsername(const std::string& username);
    std::vector<std::string> getUsernames();
    std::vector<std::vector<std::string>> handleLeaderboard();
};

#endif