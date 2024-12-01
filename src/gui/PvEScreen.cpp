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

    // Render the PvE screen title
    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, font, "PVE", windowWidth / 2, 50, textColor, true);

    // Render the back button
    SDL_Rect backButtonRect = {20, 20, 50, 50};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
}