// Description: Implementation of the renderPvPScreen function

#include "gui/PvPScreen.h"

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

    // Handle back button hover
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);

    // Check if there are at least 2 players in the lobby
    const std::vector<std::string>& usernames = lobby.getUsernames();
    if (usernames.size() < 2) {
        // Render a message indicating that more players are needed
        SDL_Color textColor = {255, 0, 0, 255}; // Red color
        TTF_Font* msgFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 28);
        game->renderText(renderer, msgFont, "Need at least 2 players to play PvP", windowWidth / 2, windowHeight / 2, textColor, true);
        TTF_CloseFont(msgFont);
    } else {
        // Render the "username" text
        SDL_Color textColor = {255, 255, 255, 255}; // White color
        game->renderText(renderer, font, usernames[game->currentPlayer].c_str(), windowWidth / 2, 50, textColor, true);

        static bool isDealt = false;
        static Gameplay gameplay;
        int numberOfCards = 5;
        // Gameplay gameplay;
        if (!isDealt) {
            isDealt = true;
            gameplay.init(usernames, 0);
            gameplay.dealCards(numberOfCards);
            std::cout << "So beautiful" << '\n';
        }
        const char* cardSets[usernames.size()][5];
        // Array of card file paths
            for (int i = 0; i < gameplay.numberOfPlayers; i++) {
                for (int j = 0; j < numberOfCards; j++) {
                    Card& currentCard = gameplay.players[i].hand.cards[j];
                    cardSets[i][j] = CARD_FILES[currentCard.suit * 13 + currentCard.rank].c_str();
                }
            }

        // Render the 5 cards
        game->renderCards(cardSets[game->currentPlayer], true, 0);
        
        // Handle next button hover
        SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
        SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
        game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    }
}