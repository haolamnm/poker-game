#ifndef CARD_H
#define CARD_H

#include <string>

// Enumerations for suits and ranks
enum Suits {
    SUIT_EMPTY = -1,
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

// Enumerations for ranks
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

// Card class: Represents a card in a deck of cards
class Card {
public:
    Suits suit = SUIT_EMPTY;
    Ranks rank = RANK_EMPTY;
    unsigned short value;

    std::string suitToString();
    std::string rankToString();
};

#endif