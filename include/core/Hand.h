#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <string>
#include <algorithm>
#include <iostream>

class Hand {
private:

public:
    int numberOfOnHandCards;
    int handStrength;
    std::string handName;

    Card cards[5];
    std::vector<Card> strengthCards;
    void show();
    void sortCards();
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