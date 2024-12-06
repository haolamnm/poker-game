/*
FILE: src/core/Lobby.cpp

DESCRIPTION: Implementation file for the lobby class. This file
contains the implementation of the member functions of the lobby
class. Handle things like assigning and removing username from the
lobby.

NOTE: The lobby is where the players wait for the game to start.

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Lobby.h"

void Lobby::assignUsername(const std::string& username) {
    for (const std::string& exist : usernames) {
        if (exist == username) {
            std::cout << exist << " already exists.\n";
            return;
        }
    }
    usernames.push_back(username);
}

void Lobby::removeUsername(const std::string& username) {
    std::vector<std::string>::iterator it = std::find(usernames.begin(), usernames.end(), username);
    if (it == usernames.end()) return;
    usernames.erase(it);
}

std::vector<std::string> Lobby::getUsernames() {
    return usernames;
}

std::vector<std::vector<std::string>> Lobby::handleLeaderboard() {
    return game.showLeaderboard();
}