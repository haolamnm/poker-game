#include "core/Lobby.h"

void Lobby::assignUsername(std::string username) {
    for (const std::string& exist : usernames) {
        if (exist == username) {
            std::cout << exist << " already exists.\n";
            return;
        }
    }
    usernames.push_back(username);
}



void Lobby::start() {
    while (true) {
        showMenu();
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                // handleLogin();
                break;
            case 2:
                handleGame();
                break;
            case 3:
                handleLeaderboard();
                break;
            case 4:
                std::cout << "Exiting...\n";
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void Lobby::showMenu() {
    std::cout << "1. Login\n";
    std::cout << "2. Start Game\n";
    std::cout << "3. Show Leaderboard\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void Lobby::showUsernames() {
    for (int i = 0; i < (int) usernames.size(); i++)
        std::cout << usernames[i] << '\n';
}

void Lobby::handleLogin(std::string username, std::string password) {
    if (login.login(username, password)) {
        std::cout << login.show() << '\n';
        usernames.push_back(username);
    } else if (login.statusCode == NEW_ACCOUNT) {
        std::cout << login.show() << '\n';
        char choice;
        std::cout << "Do you want to create a new account? (y/n): ";
        std::cin >> choice;
        if (choice == 'y') {
            login.createNewPlayer(username, password);
            std::cout << login.show() << '\n';
        }
    } else {
        std::cout << login.show() << '\n';
    }
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