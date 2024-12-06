/*
FILE: src/core/Deck.cpp

DESCRIPTION: Implementation file for the deck class. This file
contains the implementation of the member functions of the deck
class. Handle things like setting up the deck, shuffling the 
deck and resetting the deck.

NOTE: We're using a random number generator provided by the C++
standard library to shuffle the deck. It is a Mersenne Twister
engine, which is a very popular and high-quality random number 
generator.

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Deck.h"

void Deck::setup() {
    for (int row = Suits::CLUBS; row <= Suits::SPADES; row++) {
        for (int col = Ranks::TWO; col <= Ranks::ACE; col++) {
            Card &card = cards[row * Deck::RANKS_SIZE + col];
            card.suit = static_cast<Suits>(row);
            card.rank = static_cast<Ranks>(col);
        }
    }
}

void Deck::shuffle() {
    std::mt19937 seed(static_cast<unsigned long>(std::time(0)));
    std::shuffle(cards, cards + DECK_SIZE, seed);
}

void Deck::reset() {
    setup();
    shuffle();
    remainCards = DECK_SIZE;
}
/* ------------------End of Deck------------------ */