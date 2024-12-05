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