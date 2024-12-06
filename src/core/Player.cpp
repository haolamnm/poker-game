/*
FILE: src/core/Player.cpp

DESCRIPTION: Implementation file for the player class. This file
contains the implementation of the member functions of the player
class. Handle things like showing the player's information, saving
the player's data, and showing the leaderboard.

NOTE: Players are ranked based on their winrate. The player with the
highest winrate will be ranked first.

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Player.h"

/* ------------------Player------------------ */
void Player::show() {
    std::cout << "Username: " << username << '\n';
    std::cout << "Games played: " << gamesPlayed << '\n';
    std::cout << "Chips: " << chips << '\n';
    std::cout << "Winrate: " << winrate << '\n';
    std::cout << "Rank: " << rank << '\n';
    std::cout << "Favorite strategy: " << favoriteStrategy << '\n';
    std::cout << "Winning strategy: ";
    for (int i = 0; i < 9; i++) {
        std::cout << winningStrategy[i] << ' ';
    }
    std::cout << '\n';
}


/* ------------------End of Player------------------ */