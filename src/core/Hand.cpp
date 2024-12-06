/*
FILE: src/core/Hand.cpp

DESCRIPTION: Implementation file for the both hand and strenght 
class. This file contains the implementation of the member 
functions of the hand and strength class. Handle things like 
showing the hand, sorting the hand, and evaluating the hand. 
Also, there are functions to determine the strength of the hand 
and compare two hands.

NOTE: A hand is a set of cards held by a player during a game. 
And the strength of a hand is determined by the combination of 
cards

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Hand.h"

/* ------------------Hand------------------ */
void Hand::show() {
    for (int i = 0; i < numberOfOnHandCards; i++) {
        std::cout << cards[i].rankToString() << " of " << cards[i].suitToString() << '\n';
    }
}

void Hand::sortCards() {
    for (int i = 0; i < 5; i++) {
        sortedCards[i] = cards[i];
    }
    std::sort(sortedCards, sortedCards + numberOfOnHandCards, [&](Card& a, Card& b) {
        return a.rank < b.rank;
    });
}

void Hand::evaluateHand() {
    Strength strength;
    sortCards();
    handStrength = strength.evaluateHand(*this);
}
/* ------------------End of Hand------------------ */

bool Strength::isStraightFlush(Hand& hand) {
    for (int i = 0; i < 4; i++) {
        if (hand.sortedCards[i].suit != hand.sortedCards[i + 1].suit) return false;
        else if (hand.sortedCards[i + 1].rank - hand.sortedCards[i].rank != 1) return false;
    }
    hand.strengthCards.clear();
    hand.strengthCards = {
        hand.sortedCards[0],
        hand.sortedCards[1],
        hand.sortedCards[2],
        hand.sortedCards[3],
        hand.sortedCards[4]
    };
    return true;
}

bool Strength::isFourOfAKind(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank &&
        hand.sortedCards[1].rank == hand.sortedCards[2].rank &&
        hand.sortedCards[2].rank == hand.sortedCards[3].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3]
        };
        return true;
    } else if (hand.sortedCards[1].rank == hand.sortedCards[2].rank &&
        hand.sortedCards[2].rank == hand.sortedCards[3].rank &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

bool Strength::isFullHouse(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank &&
        hand.sortedCards[1].rank == hand.sortedCards[2].rank &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    } else if (hand.sortedCards[0].rank == hand.sortedCards[1].rank &&
        hand.sortedCards[2].rank == hand.sortedCards[3].rank &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

bool Strength::isFlush(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].suit == hand.sortedCards[1].suit &&
        hand.sortedCards[1].suit == hand.sortedCards[2].suit &&
        hand.sortedCards[2].suit == hand.sortedCards[3].suit &&
        hand.sortedCards[3].suit == hand.sortedCards[4].suit) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

bool Strength::isStraight(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank - 1 &&
        hand.sortedCards[1].rank == hand.sortedCards[2].rank - 1 &&
        hand.sortedCards[2].rank == hand.sortedCards[3].rank - 1 &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank - 1) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

bool Strength::isThreeOfAKind(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank &&
        hand.sortedCards[1].rank == hand.sortedCards[2].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2]
        };
        return true;
    } else if (hand.sortedCards[1].rank == hand.sortedCards[2].rank &&
        hand.sortedCards[2].rank == hand.sortedCards[3].rank) {
        hand.strengthCards = {
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3]
        };
        return true;
    } else if (hand.sortedCards[2].rank == hand.sortedCards[3].rank &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

bool Strength::isTwoPair(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank &&
        hand.sortedCards[2].rank == hand.sortedCards[3].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3]
        };
        return true;
    }
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    if (hand.sortedCards[1].rank == hand.sortedCards[2].rank &&
        hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[1],
            hand.sortedCards[2],
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

bool Strength::isOnePair(Hand& hand) {
    hand.strengthCards.clear();
    if (hand.sortedCards[0].rank == hand.sortedCards[1].rank) {
        hand.strengthCards = {
            hand.sortedCards[0],
            hand.sortedCards[1]
        };
        return true;
    }
    if (hand.sortedCards[1].rank == hand.sortedCards[2].rank) {
        hand.strengthCards = {
            hand.sortedCards[1],
            hand.sortedCards[2]
        };
        return true;
    }
    if (hand.sortedCards[2].rank == hand.sortedCards[3].rank) {
        hand.strengthCards = {
            hand.sortedCards[2],
            hand.sortedCards[3]
        };
        return true;
    }
    if (hand.sortedCards[3].rank == hand.sortedCards[4].rank) {
        hand.strengthCards = {
            hand.sortedCards[3],
            hand.sortedCards[4]
        };
        return true;
    }
    return false;
}

int Strength::evaluateHand(Hand& hand) {
    hand.handStrength = 0;
    if (isStraightFlush(hand)) {
        hand.handStrength = 8, hand.handName = "Straight Flush";
    } else if (isFourOfAKind(hand)) {
        hand.handStrength = 7, hand.handName = "Four of a Kind";
    } else if (isFullHouse(hand)) {
        hand.handStrength = 6, hand.handName = "Full House";
    } else if (isFlush(hand)) {
        hand.handStrength = 5, hand.handName = "Flush";
    } else if (isStraight(hand)) {
        hand.handStrength = 4, hand.handName = "Straight";
    } else if (isThreeOfAKind(hand)) {
        hand.handStrength = 3, hand.handName = "Three of a Kind";
    } else if (isTwoPair(hand)) {
        hand.handStrength = 2, hand.handName = "Two Pair";
    } else if (isOnePair(hand)) {
        hand.handStrength = 1, hand.handName = "One Pair";
    } else {
        hand.handStrength = 0, hand.handName = "High Card";
    }
    return hand.handStrength;
}

int Strength::compareHands(Hand& hand1, Hand& hand2) {
    if (hand1.handStrength > hand2.handStrength) return 1;
    else if (hand1.handStrength < hand2.handStrength) return -1;
    else {
        // Compare hands with the same strength using strengCards
        for (int i = hand1.strengthCards.size() - 1; i >= 0; i--) {
            if (hand1.strengthCards[i].rank > hand2.strengthCards[i].rank) return 1;
            else if (hand1.strengthCards[i].rank < hand2.strengthCards[i].rank) return -1;
        }
        for (int i = 4; i >= 0; i--) {
            if (hand1.cards[i].rank > hand2.cards[i].rank) return 1;
            else if (hand1.cards[i].rank < hand2.cards[i].rank) return -1;
        }
    }
    return 0;
}