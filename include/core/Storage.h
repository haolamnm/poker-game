/*
FILE: include/core/Storage.h

DESCRIPTION: Header file for the storage class. This file contains
the class declaration for the storage of player data in the game
and the leaderboard of the game. In the class, we handle the player
data, such as username, password, games played, chips, winrate,
rank, favorite strategy. We also handle the leaderboard of the game
based on the winrate of the players.

NOTE: We use file handling techniques to store, retrieve, update 
player data and leaderboard data.

AUTHOR: Le Nguyen Anh Tri.

INDEX: 1
*/

#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>

const std::string STORAGE_FILE_NAME = "include/storage/storage.csv";
const std::string LEADER_BOARD_FILE_NAME = "include/storage/leaderboard.csv";

class Storage {
private:
    struct Player {
        std::string username;
        std::string hashedPassword;
        std::string favoriteStrategy;
        unsigned int gamesPlayed;
        unsigned int chips;
        unsigned int winningStrategy[9];
        float winrate;
        unsigned short rank;
    };

    std::map<std::string, Player> storage;
    std::string fileName;
public:
    // Constructor
    Storage(const std::string& fileName = STORAGE_FILE_NAME);

    std::vector<std::string> split(const std::string& str, char delimiter = ',');

    // Functions to handle login and player data
    bool usernameExists(const std::string& username);
    bool verify(const std::string& username, const std::string& password);
    void createNewPlayer(const std::string& username, const std::string& password, unsigned int gamesPlayed, unsigned int chips, float winrate, unsigned short rank, const std::string& favoriteStrategy, unsigned int winningStrategy[]);
    void assignPlayerData(const std::string& username, unsigned int gamesPlayed, unsigned int chips, float winrate, unsigned short rank, const std::string& favoriteStrategy, unsigned int winningStrategy[]);
    void savePlayerData(const std::string& username);
    std::vector<std::string> getPlayerData(const std::string& username);
    std::vector<std::string> getAllUsernames();
    std::string hashPassword(const std::string& password);
    void updatePlayerStorage();
};

class Leaderboard {
private:
    struct Player {
        std::string username;
        std::string favoriteStrategy;
        unsigned int gamesPlayed;
        unsigned int chips;
        unsigned int winningStrategy[9];
        float winrate;
        unsigned short rank;
    };

    Storage playerStorage;
public:
    std::vector<Player> players;

    void updateLeaderboard();
    void saveLeaderboard(const std::string& fileName = LEADER_BOARD_FILE_NAME);
    std::vector<std::vector<std::string>> showLeaderboard();
    void loadPlayerData();
};

#endif