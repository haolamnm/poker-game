/*
FILE: src/core/Card.cpp

DESCRIPTION: Implementation file for the card class. This file 
contains the implementation of the member functions of the card
class.

NOTE: Some functions here are just used for debugging purposes.

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Card.h"

std::string Card::suitToString() {
    std::string suitString = "Empty";
    switch (suit) {
        case CLUBS:
            suitString = "Clubs";
            break;
        case DIAMONDS:
            suitString = "Diamonds";
            break;
        case HEARTS:
            suitString = "Hearts";
            break;
        case SPADES:
            suitString = "Spades";
            break;
        default:
            suitString = "Empty";
    }
    return suitString;
}

std::string Card::rankToString() {
    std::string rankString = "Empty";
    switch (rank) {
        case ACE:
            rankString = "Ace";
            break;
        case TWO:
            rankString = "Two";
            break;
        case THREE:
            rankString = "Three";
            break;
        case FOUR:
            rankString = "Four";
            break;
        case FIVE:
            rankString = "Five";
            break;
        case SIX:
            rankString = "Six";
            break;
        case SEVEN:
            rankString = "Seven";
            break;
        case EIGHT:
            rankString = "Eight";
            break;
        case NINE:
            rankString = "Nine";
            break;
        case TEN:
            rankString = "Ten";
            break;
        case JACK:
            rankString = "Jack";
            break;
        case QUEEN:
            rankString = "Queen";
            break;
        case KING:
            rankString = "King";
            break;
        default:
            rankString = "Empty";
    }
    return rankString;
}