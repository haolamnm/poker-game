#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <algorithm>
#include <random>
#include <ctime>

class Deck {
private:
    static constexpr unsigned short DECK_SIZE = 52;
    static constexpr unsigned short SUITS_SIZE = 4;
    static constexpr unsigned short RANKS_SIZE = 13;
public:
    Card cards[DECK_SIZE];
    int remainCards = DECK_SIZE;

    void setup();
    void shuffle();
};

#endif