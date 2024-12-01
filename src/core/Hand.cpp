#include "core/Hand.h"

/* ------------------Hand------------------ */
void Hand::show() {
    for (int i = 0; i < numberOfOnHandCards; i++) {
        std::cout << cards[i].rankToString() << " of " << cards[i].suitToString() << '\n';
    }
}

void Hand::sortCards() {
    std::sort(cards, cards + numberOfOnHandCards, [&](Card &a, Card &b) {
        return a.rank < b.rank;
    });
}

bool Strength::isStraightFlush(Hand& hand) {
    for (int i = 0; i < 4; i++) {
        if (hand.cards[i].suit != hand.cards[i + 1].suit) return false;
        else if (hand.cards[i + 1].rank - hand.cards[i].rank != 1) return false;
    }
    return true;
}

bool Strength::isFourOfAKind(Hand& hand) {
    return (hand.cards[0].rank == hand.cards[1].rank &&
            hand.cards[1].rank == hand.cards[2].rank &&
            hand.cards[2].rank == hand.cards[3].rank) ||
           (hand.cards[1].rank == hand.cards[2].rank &&
            hand.cards[2].rank == hand.cards[3].rank &&
            hand.cards[3].rank == hand.cards[4].rank);
}

bool Strength::isFullHouse(Hand& hand) {
    for (int i = 0; i < 2; i++)
        if (hand.cards[i].rank != hand.cards[i + 1].rank) return false;
    return hand.cards[3].rank == hand.cards[4].rank;
}

bool Strength::isFlush(Hand& hand) {
    for (int i = 0; i < 4; i++) {
        if (hand.cards[i].suit != hand.cards[i + 1].suit) return false;
    }
    return true;
}

bool Strength::isStraight(Hand& hand) {
    for (int i = 0; i < 4; i++)
        if (hand.cards[i + 1].rank - hand.cards[i].rank != 1) return false;
    return true;
}

bool Strength::isThreeOfAKind(Hand& hand) {
    for (int i = 0; i < 3; i++)
        if (hand.cards[i].rank == hand.cards[i + 1].rank && 
            hand.cards[i + 1].rank == hand.cards[i + 2].rank) return true;
    return false;
}

bool Strength::isTwoPair(Hand& hand) {
    for (int i = 0; i < 3; i++)
        if (hand.cards[i].rank == hand.cards[i + 1].rank)
            for (int j = i + 2; j < 4; j++)
                if (hand.cards[j].rank == hand.cards[j + 1].rank) return true;
    return false;
}

bool Strength::isOnePair(Hand& hand) {
    for (int i = 0; i < 4; i++)
        if (hand.cards[i].rank == hand.cards[i + 1].rank) return true;
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
    for (int i = 4; i >= 0; i--) {
        if (hand1.cards[i].rank > hand2.cards[i].rank) return 1;
        if (hand1.cards[i].rank < hand2.cards[i].rank) return -1;
    }
    return 0;
}
/* ------------------End of Hand------------------ */