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