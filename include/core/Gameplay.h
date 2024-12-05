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
    int totalChipsBetted;

    std::vector<Player> players;
    void init(const std::vector<std::string>& usernames, int numberOfBots = 0);
    void dealCards(int numberOfCards);
    void drawPlayerCards(Player& player);
    void whoWins();
    void savePlayerData(Player& player);
    void saveAllPlayerData();
    std::vector<std::vector<std::string>> showLeaderboard();
    void resetDeck();
    int countSelectedCards(int id);
};

#endif // GAMEPLAY_H