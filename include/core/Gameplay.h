/*
FILE: include/core/Gameplay.h

DESCRIPTION: Header file for the gameplay class. This file 
contains class declaration for the gameplay of the game.

NOTE: Gameplay means the game mechanics, such as dealing cards, resetting the deck, determining the winner, etc. There are also
some functions for DRAW POKER game mode.

AUTHOR: Le Nguyen Anh Tri & Lam Chi Hao.
*/

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
    unsigned int totalChipsBetted;
    unsigned int highestBet;
    std::vector<Player> players;

    // Functions to initialize the gameplay
    void init(const std::vector<std::string>& usernames, int numberOfBots = 0);

    // Functions to handle the gameplay
    void dealCards(int numberOfCards);
    void drawPlayerCards(Player& player);
    void whoWins();
    void savePlayerData(Player& player);
    void saveAllPlayerData();
    std::vector<std::vector<std::string>> showLeaderboard();
    void resetDeck();
    int countSelectedCards(int id);
};

#endif