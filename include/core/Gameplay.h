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
    void init(int numberOfPlayers, const std::vector<std::string>& usernames);
    void dealCards(int numberOfCards);
    void whoWins();
    void savePlayerData(Player& player);
    void saveAllPlayerData();
    void showLeaderboard();
};

#endif // GAMEPLAY_H