// Description: Implementation of the renderPvPScreen function

#include "gui/PvPScreen.h"

// Define the isDealt variable
bool isDealtPvP = false;
bool isSavedPvP = false;

// Function to render the PvP screen
void renderPvPScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();

    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Get the mouse coordinates
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Render the PvP screen background
    SDL_SetRenderDrawColor(renderer, 9, 70, 27, 255);
    SDL_RenderClear(renderer);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Check if there are at least 2 players in the lobby
    const std::vector<std::string>& usernames = lobby.getUsernames();
    if (usernames.size() < 2) {
        // Render a message indicating that more players are needed
        SDL_Color textColor = {255, 0, 0, 255}; // Red color
        TTF_Font* msgFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 28);
        game->renderText(renderer, msgFont, "Need at least 2 players to play PvP", windowWidth / 2, windowHeight / 2, textColor, true);
        TTF_CloseFont(msgFont);
    } 
    
    else if (game->currentPlayer <= usernames.size()) {
        static Gameplay gameplay;
        int numberOfCards = 5;

        if (!isDealtPvP) {
            isDealtPvP = true;
            gameplay.init(usernames, 0);
            gameplay.resetDeck(); // Reset the deck for a new game
            gameplay.dealCards(numberOfCards);
        }
        const char* cardSets[usernames.size()][5];
        // Array of card file paths
        for (int i = 0; i < gameplay.numberOfPlayers; i++) {
            for (int j = 0; j < numberOfCards; j++) {
                Card& currentCard = gameplay.players[i].hand.cards[j];
                cardSets[i][j] = CARD_FILES[currentCard.rank * 4 + currentCard.suit].c_str();
            }
        }
        gameplay.whoWins();
        for (int i = 0; i < gameplay.numberOfPlayers; i++) {
            std::cout << "Player's id: " << gameplay.players[i].id << " (" << gameplay.players[i].username << ")" << '\n';
            gameplay.players[i].hand.show();
            std::cout << "Hand strength: " << gameplay.players[i].hand.handStrength << " (" << gameplay.players[i].hand.handName << ")" << '\n';
            std::cout << '\n';
        }
        if (gameplay.winner != -1) {
            std::cout << "Winner: " << gameplay.players[gameplay.winner].username << '\n';
        } else {
            std::cout << "It's a tie!" << '\n';
        }

        // Save player data after dealing cards and determining the winner
        if (!isSavedPvP) {
            isSavedPvP = true;
            for (Player& player : gameplay.players) {
                gameplay.savePlayerData(player);
            }
            gameplay.saveAllPlayerData();
        }

        // Render the 5 cards
        SDL_Color textColor = {255, 255, 255, 255}; // White color
        if (game->currentPlayer < usernames.size()) {
            // Render the "username" text
            // gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str()
            game->renderText(renderer, font, gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str(), windowWidth / 2, 50, textColor, true);
            game->renderCards(cardSets[gameplay.players[game->currentPlayer].id], true, 0, true);
            SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
            bool allCardsFaceUp = true;
            for (int i = 0; i < 5; i++) {
                if (!game->getCardRevealed()[i]) {
                    allCardsFaceUp = false;
                    break;
                }
            }
            if (allCardsFaceUp) {
                game->renderText(renderer, font, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
            }
            SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
            game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
        } else if (game->currentPlayer == usernames.size()) {
            if (gameplay.winner != -1) {
                std::string winner = gameplay.players[gameplay.winner].username;
                game->renderText(renderer, font, "Winner:", windowWidth / 2, 50, textColor, true);
                game->renderText(renderer, font, winner.c_str(), windowWidth / 2, 125, textColor, true);
                game->renderCards(cardSets[gameplay.winner], false, 0, false);
                // Winner hand stregth
                game->renderText(renderer, font, gameplay.players[gameplay.winner].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
            } else {
                game->renderText(renderer, font, "It's a tie!", windowWidth / 2, 50, textColor, true);
            }
        }
    }
}