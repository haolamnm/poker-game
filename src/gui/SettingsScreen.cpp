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
int defaultChipBetted = 20;

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
    SDL_Texture* rasieButtonTexture = game->getRaiseButtonTexture();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, smallFontVintage, "Settings", WINDOW_WIDTH / 2, 50, textColor, true);

    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render background music toggle buttons
    game->renderText(renderer, bigFontVintage, "Background music", WINDOW_WIDTH / 2, 150, textColor, false);
    SDL_Rect musicOnButtonRect = {WINDOW_WIDTH / 2 + 100, 150, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, musicOnButtonTexture, NULL, &musicOnButtonRect);
    game->handleButtonHover(musicOnButtonTexture, mouseX, mouseY, musicOnButtonRect.x, musicOnButtonRect.y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    SDL_Rect musicOffButtonRect = {WINDOW_WIDTH / 2 + 100 + SMALL_BUTTON_WIDTH + 20, 150, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, musicOffButtonTexture, NULL, &musicOffButtonRect);
    game->handleButtonHover(musicOffButtonTexture, mouseX, mouseY, musicOffButtonRect.x, musicOffButtonRect.y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render sound effects toggle buttons
    game->renderText(renderer, bigFontVintage, "Sound effects", WINDOW_WIDTH / 2, 180, textColor, false);
    SDL_Rect soundOnButtonRect = {WINDOW_WIDTH / 2 + 100, 180, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, soundOnButtonTexture, NULL, &soundOnButtonRect);
    game->handleButtonHover(soundOnButtonTexture, mouseX, mouseY, soundOnButtonRect.x, soundOnButtonRect.y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
    SDL_Rect soundOffButtonRect = {WINDOW_WIDTH / 2 + 100 + SMALL_BUTTON_WIDTH + 20, 180, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, soundOffButtonTexture, NULL, &soundOffButtonRect);
    game->handleButtonHover(soundOffButtonTexture, mouseX, mouseY, soundOffButtonRect.x, soundOffButtonRect.y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render current game mode
    game->renderText(renderer, smallFontVintage, "Current Game Mode:", 400, 300, textColor, false);
    game->renderText(renderer, smallFontVintage, game->getCurrentGameModeString(), WINDOW_WIDTH / 2 + 150, 210, textColor, false);

    SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
    game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    SDL_Rect rasieButtonRect = {RAISE_BUTTON_X, RAISE_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, rasieButtonTexture, NULL, &rasieButtonRect);
    game->handleButtonHover(rasieButtonTexture, mouseX, mouseY, RAISE_BUTTON_X, RAISE_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render default chip betted
    std::string defaultChipBettedText = "Default chip betted: " + std::to_string(defaultChipBetted);
    game->renderText(renderer, smallFontVintage, defaultChipBettedText.c_str(), WINDOW_WIDTH / 2, 400, textColor, true);

    // TODO:
    // Implement the functionality to toggle the music and sound effects settings
    // Implement input for min chip per game, the number of bots, game mode.
}