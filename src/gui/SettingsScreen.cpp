/*
FILE: src/gui/SettingsScreen.cpp

DESCRIPTION: Implementation file for the settings screen. This file is
part of the GUI subsystem and is used to render the settings screen. This
file contains the function definition for rendering the settings screen.

NOTE: We can configure the background music, sound effects, and game mode
in this screen.

AUTHOR: Lam Chi Hao.
*/

#include "gui/SettingsScreen.h"

// Boolean variables for music and sound effects settings
bool isMusicOn = true;
bool isSoundEffectsOn = true;

// For settings chip
unsigned int defaultChipsBetted = 20;

// Function to render the Settings screen
void renderSettingsScreen(GameEngine* game) {
    TTF_Font* smallFontVintage = game->getSmallFontVintage();
    TTF_Font* bigFontVintage = game->getBigFontVintage();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    SDL_Texture* musicOnButtonTexture = game->getMusicOnButtonTexture();
    SDL_Texture* musicOffButtonTexture = game->getMusicOffButtonTexture();
    SDL_Texture* soundOnButtonTexture = game->getSoundOnButtonTexture();
    SDL_Texture* soundOffButtonTexture = game->getSoundOffButtonTexture();
    SDL_Texture* raiseButtonTexture = game->getRaiseButtonTexture();
    SDL_Texture* downButtonTexture = game->getDownButtonTexture();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, bigFontVintage, "Settings", WINDOW_WIDTH / 2, 50, textColor, true);

    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render background music toggle buttons
    game->renderText(renderer, smallFontVintage, "Background music", WINDOW_WIDTH / 2 - 100, 150, textColor, false, true);
    SDL_Rect musicButtonRect = {WINDOW_WIDTH / 2 + 100, 150, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_Texture* musicButtonTexture = game->isMusicOn ? musicOnButtonTexture : musicOffButtonTexture;
    SDL_RenderCopy(renderer, musicButtonTexture, NULL, &musicButtonRect);
    game->handleButtonHover(musicButtonTexture, mouseX, mouseY, musicButtonRect.x, musicButtonRect.y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render sound effects toggle buttons
    game->renderText(renderer, smallFontVintage, "Sound effects", WINDOW_WIDTH / 2 - 100, 210, textColor, false, true);
    SDL_Rect soundButtonRect = {WINDOW_WIDTH / 2 + 100, 210, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_Texture* soundButtonTexture = game->isSoundEffectsOn ? soundOnButtonTexture : soundOffButtonTexture;
    SDL_RenderCopy(renderer, soundButtonTexture, NULL, &soundButtonRect);
    game->handleButtonHover(soundButtonTexture, mouseX, mouseY, soundButtonRect.x, soundButtonRect.y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    
    // Render current game mode
    // std::string currentGameModeText = "Current Game Mode: ";
    game->renderText(renderer, smallFontVintage, game->getCurrentGameModeString(), WINDOW_WIDTH / 2 - 100, 270, textColor, false, true);

    SDL_Rect nextButtonRect = {WINDOW_WIDTH / 2 + 100, 270, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
    game->handleButtonHover(nextButtonTexture, mouseX, mouseY, WINDOW_WIDTH / 2 + 100, 270, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    SDL_Rect raiseButtonRect = {WINDOW_WIDTH / 2 + 100, 330, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, raiseButtonTexture, NULL, &raiseButtonRect);
    game->handleButtonHover(raiseButtonTexture, mouseX, mouseY, WINDOW_WIDTH / 2 + 100, 330, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    SDL_Rect downButtonRect = {WINDOW_WIDTH / 2 + 170, 330, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, downButtonTexture, NULL, &downButtonRect);
    game->handleButtonHover(downButtonTexture, mouseX, mouseY, WINDOW_WIDTH / 2 + 170, 330, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render default chip betted
    std::string defaultChipsBettedText = "Default chips betted: " + std::to_string(defaultChipsBetted);
    game->renderText(renderer, smallFontVintage, defaultChipsBettedText.c_str(), WINDOW_WIDTH / 2 - 100, 330, textColor, false, true);
}