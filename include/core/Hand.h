/*
FILE: include/core/Hand.h

DESCRIPTION: Header file for the hand class. This file contains 
the class declaration for a hand of cards and strength of the hand in our game. In the class, there are functions to show the 
hand, sort the hand, and evaluate the hand.

NOTE: A hand is a set of cards held by a player during a game. 
The strength of a hand is determined by the combination of cards 
it contains.

AUTHOR: Le Nguyen Anh Tri.
*/

#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

class Hand {
private:

public:
    // Variables to store the hand information
    int numberOfOnHandCards;
    int handStrength;
    std::string handName;
    Card cards[5];
    Card sortedCards[5];
    bool removedCards[5];
    std::vector<Card> strengthCards;

    // Functions for hand operations
    void show();
    void sortCards();
    void evaluateHand();
};

class Strength {
private:

public:
    bool isStraightFlush(Hand& hand);
    bool isFourOfAKind(Hand& hand);
    bool isFullHouse(Hand& hand);
    bool isFlush(Hand& hand);
    bool isStraight(Hand& hand);
    bool isThreeOfAKind(Hand& hand);
    bool isTwoPair(Hand& hand);
    bool isOnePair(Hand& hand);

    int evaluateHand(Hand& hand);
    int compareHands(Hand& hand1, Hand& hand2);
    int compareFourOfAKind(Hand& hand1, Hand& hand2);
    int compareFullHouse(Hand& hand1, Hand& hand2);
    int compareThreeOfAKind(Hand& hand1, Hand& hand2);
    int compareTwoPair(Hand& hand1, Hand& hand2);
    int compareOnePair(Hand& hand1, Hand& hand2);
    int compareHighCard(Hand& hand1, Hand& hand2);
};

#endif