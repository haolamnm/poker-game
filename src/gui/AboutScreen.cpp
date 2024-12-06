/*
FILE: src/gui/AboutScreen.cpp

DESCRIPTION: Implementation file for the AboutScreen class. This
file is part of the GUI subsystem. This file contains the function
definition for rendering the About screen. 

NOTE: The About screen is where the player can view information
about the game, which is the reason why we developed the game.

TODO: Implement the content for the About screen.

AUTHOR: Lam Chi Hao.
*/

#include "gui/AboutScreen.h"

void renderAboutScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Render the About Us screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Render the About Us screen title
    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, font, "About Us", WINDOW_WIDTH / 2, 50, textColor, true);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
}