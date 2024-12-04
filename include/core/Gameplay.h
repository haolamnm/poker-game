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
    void drawPlayerCards(Player& player, bool removedCards[5]);
    void whoWins();
    void savePlayerData(Player& player);
    void saveAllPlayerData();
    std::vector<std::vector<std::string>> showLeaderboard();
    void resetDeck();
};

#endif // GAMEPLAY_H