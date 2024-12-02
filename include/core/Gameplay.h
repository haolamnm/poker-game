#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Deck.h"
#include "Player.h"
#include "Storage.h"
#include <vector>

class Gameplay {
private:
    Deck deck;
    Storage storage;
    Leaderboard leaderboard;

public:
    int numberOfPlayers;
    int winner;

    std::vector<Player> players;
    void init(const std::vector<std::string>& usernames, int numberOfBots = 0);
    void dealCards(int numberOfCards);
    void whoWins();
    void savePlayerData(Player& player);
    void saveAllPlayerData();
    std::vector<std::vector<std::string>> showLeaderboard();
};

#endif // GAMEPLAY_H