#include "core/Deck.h"

/* ------------------Deck------------------ */
void Deck::setup() {
    for (int row = Suits::CLUBS; row <= Suits::SPADES; row++) {
        for (int col = Ranks::ACE; col <= Ranks::KING; col++) {
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
/* ------------------End of Deck------------------ */