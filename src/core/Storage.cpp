#include "core/Storage.h"

/* ------------------Storage------------------ */
Storage::Storage(const std::string& fileName) {
    this->fileName = fileName;
    std::fstream file(fileName, std::ios::in);
    if (file.is_open()) {
        std::string data;
        while (getline(file, data)) {
            std::vector<std::string> str = split(data);
            if (str.size() == 16) {
                Player player;
                player.username = str[0];
                player.hashedPassword = str[1];
                player.gamesPlayed = std::stoi(str[2]);
                player.chips = std::stoi(str[3]);
                player.winrate = std::stof(str[4]);
                player.rank = std::stoi(str[5]);
                player.favoriteStrategy = str[6];
                for (int i = 0; i < 9; i++) {
                    player.winningStrategy[i] = std::stoi(str[7 + i]);
                }
                storage[player.username] = player;
            }
        }
        file.close();
    }
}

std::vector<std::string> Storage::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;
    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

bool Storage::usernameExists(const std::string& username) {
    return storage.count(username) > 0;
}

bool Storage::verify(const std::string& username, const std::string& password) {
    std::string hashedPassword = hashPassword(username + password);
    return storage[username].hashedPassword == hashedPassword;
}

void Storage::createNewPlayer(const std::string& username, const std::string& password, unsigned int gamesPlayed, unsigned int chips, float winrate, unsigned short rank, const std::string& favoriteStrategy, unsigned int winningStrategy[]) {
    Player player;
    player.username = username;
    player.hashedPassword = hashPassword(username + password);
    player.gamesPlayed = gamesPlayed;
    player.chips = chips;
    player.winrate = winrate;
    player.rank = rank;
    player.favoriteStrategy = favoriteStrategy;
    for (int i = 0; i < 9; i++) {
        player.winningStrategy[i] = winningStrategy[i];
    }
    storage[username] = player;

    std::fstream file(fileName, std::ios::app);
    if (file.is_open()) {
        file << player.username << ',' << player.hashedPassword << ',' << player.gamesPlayed << ',' << player.chips << ',' << player.winrate << ',' << player.rank << ',' << player.favoriteStrategy;
        for (int i = 0; i < 9; i++) {
            file << ',' << player.winningStrategy[i];
        }
        file << '\n';
        file.close();
    }
}

void Storage::assignPlayerData(const std::string& username, unsigned int gamesPlayed, unsigned int chips, float winrate, unsigned short rank, const std::string& favoriteStrategy, unsigned int winningStrategy[]) {
    if (storage.count(username) > 0) {
        Player& player = storage[username];
        player.gamesPlayed = gamesPlayed;
        player.chips = chips;
        player.winrate = winrate;
        player.rank = rank;
        player.favoriteStrategy = favoriteStrategy;
        for (int i = 0; i < 9; i++) {
            player.winningStrategy[i] = winningStrategy[i];
        }
    }
}

void Storage::savePlayerData(const std::string& username) {
    if (storage.count(username) > 0) {
        std::fstream file(fileName, std::ios::out | std::ios::trunc);
        if (file.is_open()) {
            for (const auto& entry : storage) {
                const Player& player = entry.second;
                file << player.username << ',' << player.hashedPassword << ',' << player.gamesPlayed << ',' << player.chips << ',' << player.winrate << ',' << player.rank << ',' << player.favoriteStrategy;
                for (int i = 0; i < 9; i++) {
                    file << ',' << player.winningStrategy[i];
                }
                file << '\n';
            }
            file.close();
        }
    }
}

std::vector<std::string> Storage::getPlayerData(const std::string& username) {
    std::vector<std::string> playerData;
    if (storage.count(username) > 0) {
        const Player& player = storage[username];
        playerData.push_back(player.username);
        playerData.push_back(std::to_string(player.gamesPlayed));
        playerData.push_back(std::to_string(player.chips));
        playerData.push_back(std::to_string(player.winrate));
        playerData.push_back(std::to_string(player.rank));
        playerData.push_back(player.favoriteStrategy);
        for (int i = 0; i < 9; i++) {
            playerData.push_back(std::to_string(player.winningStrategy[i]));
        }
    }
    return playerData;
}

std::vector<std::string> Storage::getAllUsernames() {
    std::vector<std::string> usernames;
    for (const auto& entry : storage) {
        usernames.push_back(entry.first);
    }
    return usernames;
}

std::string Storage::hashPassword(const std::string& password) {
    std::hash<std::string> stringHash;
    size_t hashedPassword = stringHash(password);
    return std::to_string(hashedPassword);
}
/* ------------------End of Storage------------------ */

/* ------------------Leaderboard------------------ */
void Leaderboard::loadPlayerData() {
    players.clear();
    std::vector<std::string> usernames = playerStorage.getAllUsernames();
    for (const auto& username : usernames) {
        std::vector<std::string> playerData = playerStorage.getPlayerData(username);
        if (!playerData.empty()) {
            Player player;
            player.username = username;
            player.gamesPlayed = std::stoi(playerData[1]);
            player.chips = std::stoi(playerData[2]);
            player.winrate = std::stof(playerData[3]);
            player.rank = std::stoi(playerData[4]);
            player.favoriteStrategy = playerData[5];
            for (int i = 0; i < 9; i++) {
                player.winningStrategy[i] = std::stoi(playerData[6 + i]);
            }
            players.push_back(player);
        }
    }
}

void Leaderboard::updateLeaderboard() {
    loadPlayerData();
    std::sort(players.begin(), players.end(), [&](Player& a, Player& b) {
        return a.winrate > b.winrate;
    });
    for (int i = 0; i < players.size(); i++) {
        players[i].rank = i + 1;
    }
    saveLeaderboard();
}

void Leaderboard::saveLeaderboard(const std::string& fileName) {
    std::fstream file(fileName, std::ios::out | std::ios::trunc);
    if (file.is_open()) {
        for (const auto& player : players) {
            file << player.rank << ',' << player.username << ',' << player.gamesPlayed << ',' << player.winrate << ',' << player.favoriteStrategy << ',' << player.chips;
            file << '\n';
        }
        file.close();
    }
}

void Leaderboard::showLeaderboard() {
    // Rank - Username - Chips - Winrate - Favorite Strategy set width to 15
    std::cout << std::left << std::setw(5) << "Rank" << std::setw(15) << "Username" << std::setw(10) << "Chips" << std::setw(10) << "Winrate" << std::setw(15) << "Favorite Strategy" << '\n';
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& player : players) {
        std::cout << std::left << std::setw(5) << player.rank << std::setw(15) << player.username << std::setw(10) << player.chips << std::setw(10) << player.winrate * 100 << std::setw(15) << player.favoriteStrategy << '\n';
    }
}
/* ------------------End of Leaderboard------------------ */