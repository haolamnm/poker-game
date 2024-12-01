// Description: Implementation of the renderPvPScreen function

#include "gui/PvPScreen.h"

// Function to render the PvP screen
void renderPvPScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();

    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Get the mouse coordinates
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Render the PvP screen background
    SDL_SetRenderDrawColor(renderer, 9, 70, 27, 255);
    SDL_RenderClear(renderer);

    // Render the "Player 1" text
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    game->renderText(renderer, font, "Player 1", windowWidth / 2, 50, textColor, true);

    // Handle back button hover
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);

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