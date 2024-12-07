/*
FILE: include/core/Deck.h

DESCRIPTION: Header file for the deck class. This file contains 
the class declaration for a deck of cards in our game. In this
class, we handle things like setting up the deck, shuffling the
deck, and resetting the deck. We also keep track of the number of
cards remaining in the deck.

AUTHOR: Le Nguyen Anh Tri.
*/

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
    unsigned int remainCards = DECK_SIZE;

    void setup();
    void shuffle();
    void reset();
};

#endif