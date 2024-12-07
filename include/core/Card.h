/*
FILE: include/core/Card.h

DESCRIPTION: Header file for the card class. This file contains 
the. This file contains the class declaration for a single card 
in our game.

AUTHOR: Le Nguyen Anh Tri.
*/

#ifndef CARD_H
#define CARD_H

#include <string>

enum Suits {
    SUIT_EMPTY = -1,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum Ranks {
    RANK_EMPTY = -1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

class Card {
public:
    Suits suit = SUIT_EMPTY;
    Ranks rank = RANK_EMPTY;

    std::string suitToString();
    std::string rankToString();
};

#endif