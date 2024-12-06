/*
FILE: src/gui/TutorialScreen.cpp

DESCRIPTION: Implementation file for the tutorial screen. This file is
part of the GUI subsystem and is used to render the tutorial screen. This
file contains the function definition for rendering the tutorial screen.

NOTE: The tutorial screen is where the player can view the poker card
combinations and their corresponding strengths.

AUTHOR: Lam Chi Hao.
*/

#include "gui/TutorialScreen.h"

// Function to render the Tutorial screen
void renderTutorialScreen(GameEngine* game) {
    TTF_Font* bigFontVintage = game->getBigFontVintage();
    TTF_Font* mediumFontVintage = game->getMediumFontVintage();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    SDL_Texture* prevButtonTexture = game->getPrevButtonTexture();

    // Get the mouse coordinates
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Render the Tutorial screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Render the Tutorial screen title
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    game->renderText(renderer, bigFontVintage, "Tutorial", WINDOW_WIDTH / 2, 50, textColor, true);

    // Handle back button hover
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);

    // Handle next button hover
    game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the next button
    SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);

    // Handle prev button hover
    game->handleButtonHover(prevButtonTexture, mouseX, mouseY, PREV_BUTTON_X, PREV_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the prev button
    SDL_Rect prevButtonRect = {PREV_BUTTON_X, PREV_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, prevButtonTexture, NULL, &prevButtonRect);

    // Array of card file paths for each set
    const char* cardSets[9][5] = {
        {CARD_K_H, CARD_J_H, CARD_10_H, CARD_9_H, CARD_8_H},  // Straight flush, king high
        {CARD_9_H, CARD_9_D, CARD_9_C, CARD_9_S, CARD_JOKER}, // Four of a kind, 9
        {CARD_3_C, CARD_3_S, CARD_3_D, CARD_6_C, CARD_6_H},   // Full house, 3 over 6
        {CARD_K_C, CARD_10_C, CARD_7_C, CARD_6_C, CARD_4_C},  // Flush, king high
        {CARD_7_C, CARD_6_H, CARD_5_S, CARD_4_H, CARD_3_C},   // Straight, 7 high
        {CARD_2_D, CARD_2_S, CARD_2_C, CARD_K_H, CARD_6_H},   // Three of a kind, 2
        {CARD_J_H, CARD_J_C, CARD_4_C, CARD_4_S, CARD_9_H},   // Two pairs, jack and 4
        {CARD_4_H, CARD_4_S, CARD_K_S, CARD_10_D, CARD_5_S},  // One pair, 4
        {CARD_K_H, CARD_J_H, CARD_8_C, CARD_7_D, CARD_4_S}    // High card, king
    };

    const char* cardSetStrength[9] = {
        "Straight flush (K)",
        "Four of a kind (9)",
        "Full house (3 6)",
        "Flush (K)",
        "Straight (7)",
        "Three of a kind (2)",
        "Two pairs (J 4)",
        "One pair (4)",
        "High card (K)"
    };

    // Array of fade cards for each set
    int fadeCards[9] = {0, 1, 0, 0, 0, 2, 1, 3, 4};

    // Render the current set of cards
    game->renderCards(cardSets[game->currentCardSet], false, fadeCards[game->currentCardSet], false);
    game->renderText(renderer, mediumFontVintage, cardSetStrength[game->currentCardSet], WINDOW_WIDTH / 2, 450, textColor, true);
}