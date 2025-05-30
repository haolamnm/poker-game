/*
FILE: src/core/Gameplay.cpp

DESCRIPTION: Implementation file for the gameplay class. This file
contains the implementation of the member functions of the gameplay
class. Handle things like initializing the gameplay, dealing cards,
determining the winner, etc.

NOTE: Gameplay means the game mechanics, such as dealing cards, resetting the deck, determining the winner, etc. There are also
some functions for all poker game mode.

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Gameplay.h"

void Gameplay::init(const std::vector<std::string>& usernames, int numberOfBots) {
    totalChipsBetted = 0;
    highestBet = 0;
    this->numberOfPlayers = usernames.size() + numberOfBots;
    players.assign(numberOfPlayers, Player());
    for (int i = 0; i < numberOfPlayers; i++) {
        players[i].id = i;
        if (i < static_cast<int>(usernames.size())) {
            players[i].username = usernames[i];
            players[i].isBot = false;
            std::vector<std::string> playerData = storage.getPlayerData(usernames[i]);
            if (!playerData.empty()) {
                players[i].gamesPlayed = std::stoi(playerData[1]);
                players[i].chips = std::stoi(playerData[2]);
                players[i].winrate = std::stof(playerData[3]);
                players[i].rank = std::stoi(playerData[4]);
                players[i].favoriteStrategy = playerData[5];
                for (int j = 0; j < 9; j++) {
                    players[i].winningStrategy[j] = std::stoi(playerData[6 + j]);
                }
            }
            if (players[i].chips - entryFee >= 0) {
                players[i].chips -= entryFee;
                totalEntryFee += entryFee;
            }
        } else {
            players[i].username = "BOT " + std::to_string(i - usernames.size() + 1);
        }
    }
    std::mt19937 seed(static_cast<unsigned long>(std::time(0)));
    shuffle(players.begin(), players.end(), seed);
    deck.setup();
    deck.shuffle();
}

void Gameplay::dealCards(int numberOfCards) {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < numberOfCards; j++) {
            Card& currentPlayerCard = players[i].hand.cards[j];
            int& currentNumberOfOnHandCards = players[i].hand.numberOfOnHandCards;
            Suits& currentCardSuit = currentPlayerCard.suit;
            Ranks& currentCardRank = currentPlayerCard.rank;

            if (currentCardSuit == SUIT_EMPTY && currentCardRank == RANK_EMPTY) {
                currentPlayerCard = deck.cards[deck.remainCards - 1];
                deck.remainCards--;
                currentNumberOfOnHandCards++;
            }
        }
    }
    std::cout << "Remaining cards in the deck: " << deck.remainCards << '\n';
}

void Gameplay::drawPlayerCards(Player& player) {
    for (int i = 0; i < 5; i++) {
        if (player.hand.removedCards[i]) {
            player.hand.cards[i] = deck.cards[deck.remainCards - 1];
            deck.remainCards--;
        }
    }
    std::cout << "Remaining cards in the deck: " << deck.remainCards << '\n';
}

void Gameplay::whoWins() {
    Strength strength;
    for (int i = 0; i < numberOfPlayers; i++) {
        if (players[i].isFolded == false) players[i].hand.evaluateHand();
    }
    winner = 0;
    bool isTie = false;
    int tiePlayer = 0;
    for (int i = 1; i < numberOfPlayers; i++) {
        if (players[i].isFolded) continue;
        if (strength.compareHands(players[i].hand, players[winner].hand) == 1) {
            winner = i;
        } else if (strength.compareHands(players[i].hand, players[winner].hand) == 0) {
            isTie = true;
            winner = tiePlayer = i;
        }
    }
    if (isTie && winner == tiePlayer) {
        winner = -1;
    }
}

void Gameplay::savePlayerData(Player& player) {
    player.gamesPlayed++;
    if (player.id == players[winner].id) {
        player.winningStrategy[player.hand.handStrength]++;
        player.chips += totalChipsBetted + totalEntryFee;
    }
    int gamesWon = 0;
    for (int i = 0; i < 9; i++) {
        gamesWon += player.winningStrategy[i];
        unsigned int mostWinningStrategy = 0;
        if (player.winningStrategy[i] >= mostWinningStrategy) {
            mostWinningStrategy = player.winningStrategy[i];
            player.favoriteStrategy = player.hand.handName;
        }
    }
    player.winrate = (float) gamesWon / player.gamesPlayed;
}

void Gameplay::saveAllPlayerData() {
    for (auto& player : players) {
        storage.assignPlayerData(player.username, player.gamesPlayed, player.chips, player.winrate, player.rank, player.favoriteStrategy, player.winningStrategy);
        storage.savePlayerData(player.username);
    }
    leaderboard.updateLeaderboard();
}

std::vector<std::vector<std::string>> Gameplay::showLeaderboard() {
    return leaderboard.showLeaderboard();
}

void Gameplay::resetDeck() {
    deck.reset();
}

int Gameplay::countSelectedCards(int id) {
    int cnt = 0;
    for (int i = 0; i < 5; i++) {
        if (players[id].hand.removedCards[i]) {
            cnt++;
        }
    }
    return cnt;
}