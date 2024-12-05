#ifndef PLAYER_H
#define PLAYER_H

#include "Login.h"
#include "Hand.h"
#include <iostream>

class Player {
public:
    std::string username = "BOT";
    int id = -1;
    Hand hand;
    unsigned int chipsBetted = 0;

    unsigned int gamesPlayed = 0;
    unsigned int chips = 200;
    float winrate = 0.0;
    unsigned short rank = 0;
    std::string favoriteStrategy = "Not have favorite strategy yet";
    unsigned int winningStrategy[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    /*
        winningStrategy: array
            0 - High card           1 - One pair
            2 - Two pair            3 - Three of a kind
            4 - Straight            5 - Flush
            6 - Full house          7 - Four of a kind
            8 - Straight flush
    */

    void show();
};

#endif