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

void Lobby::handleGame() {
    if (usernames.empty()) {
        std::cout << "Please login first.\n";
        return;
    }

    game.init(3, usernames); // Pass usernames to init method
    game.dealCards(5);
    game.whoWins();

    for (int i = 0; i < game.numberOfPlayers; i++) {
        std::cout << "Player's id: " << game.players[i].id << " (" << game.players[i].username << ")" << '\n';
        game.players[i].hand.show();
        std::cout << "Hand strength: " << game.players[i].hand.handStrength << " (" << game.players[i].hand.handName << ")" << '\n';
        std::cout << '\n';
    }

    std::cout << "Winner: " << game.winner << '\n';

    // Update the current logged-in player's data if they won
    for (auto& player : game.players) {
        if (std::find(usernames.begin(), usernames.end(), player.username) != usernames.end()) {
            game.savePlayerData(player);
        }
    }

    // Save player data before exiting
    game.saveAllPlayerData();
}

std::vector<std::vector<std::string>> Lobby::handleLeaderboard() {
    return game.showLeaderboard();
}