// Description: This file contains the implementation of the renderAboutScreen function

#include "gui/AboutScreen.h"

// Function to render the About screen
void renderAboutScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Render the About Us screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Render the About Us screen title
    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, font, "About Us", windowWidth / 2, 50, textColor, true);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
}