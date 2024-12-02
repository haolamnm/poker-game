// Description: Implementation of the renderSettingsScreen function

#include "gui/SettingsScreen.h"

// Function to render the Settings screen
void renderSettingsScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    // SDL_Texture* musicToggleButtonTexture = game->getMusicToggleButtonTexture();
    // SDL_Texture* soundToggleButtonTexture = game->getSoundToggleButtonTexture();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Render the Settings screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Render the Settings screen title
    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, font, "Settings", windowWidth / 2, 50, textColor, true);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    // Render the background music toggle button
    // SDL_Rect musicToggleButtonRect = {START_X, START_X + SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    // SDL_RenderCopy(renderer, musicToggleButtonTexture, NULL, &musicToggleButtonRect);

    // Render the sound effects toggle button
    // SDL_Rect soundToggleButtonRect = {START_X, START_X + 2 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    // SDL_RenderCopy(renderer, soundToggleButtonTexture, NULL, &soundToggleButtonRect);
}