// Description: Implementation of the renderPvEScreen function

#include "gui/PvEScreen.h"

// Function to render the PvE screen
void renderPvEScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    
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
        // Render the PvE screen title
        SDL_Color textColor = {255, 255, 255, 255}; // White color
        game->renderText(renderer, font, "PVE", windowWidth / 2, 50, textColor, true);

        // Array of card file paths
        const char* cardFiles[5] = {
            CARD_2_C,
            CARD_3_D,
            CARD_4_H,
            CARD_5_S,
            CARD_6_C
        };

        // Render the 5 cards
        game->renderCards(cardFiles, true, 0);
    }
}