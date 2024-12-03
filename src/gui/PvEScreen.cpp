// Description: Implementation of the renderPvEScreen function

#include "gui/PvEScreen.h"

// Define the isDealt variable
bool isDealtPvE = false;

// Function to render the PvE screen
void renderPvEScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    
    // Get window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Render the PvE screen background
    SDL_SetRenderDrawColor(renderer, 9, 70, 27, 255);
    SDL_RenderClear(renderer);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Handle back button hover
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    
    // Check if there is at least 1 player in the lobby
    const std::vector<std::string>& usernames = lobby.getUsernames();
    if (usernames.empty()) {
        // Render a message indicating that at least 1 player is needed
        SDL_Color textColor = {255, 0, 0, 255}; // Red color
        TTF_Font* msgFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 28);
        game->renderText(renderer, msgFont, "Need at least 1 player to play PvE", windowWidth / 2, windowHeight / 2, textColor, true);
        TTF_CloseFont(msgFont);
    } else {
        static Gameplay gameplay;
        int numberOfCards = 5;

        if (!isDealtPvE) {
            isDealtPvE = true;
            gameplay.init(usernames, 5); // Initialize with 5 bots
            gameplay.resetDeck(); // Reset the deck for a new game
            gameplay.dealCards(numberOfCards);
        }
        const char* cardSets[gameplay.numberOfPlayers][5];
        // Array of card file paths
        for (int i = 0; i < gameplay.numberOfPlayers; i++) {
            for (int j = 0; j < numberOfCards; j++) {
                Card& currentCard = gameplay.players[i].hand.cards[j];
                cardSets[i][j] = CARD_FILES[currentCard.rank * 4 + currentCard.suit].c_str();
            }
        }
        gameplay.whoWins();

        // Render the 5 cards
        SDL_Color textColor = {255, 255, 255, 255}; // White color
        if (game->currentPlayer < gameplay.numberOfPlayers) {
            // Render the "username" text
            game->renderText(renderer, font, gameplay.players[game->currentPlayer].username.c_str(), windowWidth / 2, 50, textColor, true);
            game->renderCards(cardSets[game->currentPlayer], true, 0, true);
            SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
            bool allCardsFaceUp = true;
            for (int i = 0; i < 5; i++) {
                if (!game->getCardRevealed()[i]) {
                    allCardsFaceUp = false;
                    break;
                }
            }
            if (allCardsFaceUp) {
                game->renderText(renderer, font, gameplay.players[game->currentPlayer].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
            }
            SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
            game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
        } else if (game->currentPlayer == gameplay.numberOfPlayers) {
            const std::string& winner = gameplay.players[gameplay.winner].username;
            game->renderText(renderer, font, "Winner:", windowWidth / 2, 50, textColor, true);
            game->renderText(renderer, font, winner.c_str(), windowWidth / 2, 125, textColor, true);
            game->renderCards(cardSets[gameplay.winner], false, 0, false);
            // Winner hand strength
            game->renderText(renderer, font, gameplay.players[gameplay.winner].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
        }
    }
}