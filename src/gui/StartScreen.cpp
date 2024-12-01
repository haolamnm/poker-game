// Description: Implementation of the renderStartScreen function that renders the start screen of the game

#include "gui/StartScreen.h"

// Function to render the start screen
void renderStartScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    
    // Render the start screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Render the game title
    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, font, "Poker", windowWidth / 2, 50, textColor, true);

    // Render the PvP Mode button
    SDL_Rect pvpButtonRect = {PVP_BUTTON_X, PVP_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT};
    // Temporary color for the PvP button
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // TODO: SDL_RenderCopy(renderer, game->getPvpButtonTexture(), NULL, &pvpButtonRect);
    SDL_RenderFillRect(renderer, &pvpButtonRect);

    // Render the PvE Mode button
    SDL_Rect pveButtonRect = {PVE_BUTTON_X, PVE_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT};
    // Temporary color for the PvE button
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // TODO: SDL_RenderCopy(renderer, game->getPveButtonTexture(), NULL, &pveButtonRect);
    SDL_RenderFillRect(renderer, &pveButtonRect);

    // Render the User Account Info button
    SDL_Rect userInfoButtonRect = {START_X, START_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, game->getUserInfoButtonTexture(), NULL, &userInfoButtonRect);

    // Render the Instruction/Tutorial button
    SDL_Rect tutorialButtonRect = {START_X, START_Y + SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, game->getTutorialButtonTexture(), NULL, &tutorialButtonRect);

    // Render the About the Author button
    SDL_Rect aboutButtonRect = {START_X, START_Y + 2 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, game->getAboutButtonTexture(), NULL, &aboutButtonRect);

    // Render the Settings button
    SDL_Rect settingsButtonRect = {START_X, START_Y + 3 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, game->getSettingsButtonTexture(), NULL, &settingsButtonRect);

    // Render the Leaderboard button
    SDL_Rect leaderboardButtonRect = {START_X, START_Y + 4 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, game->getLeaderboardButtonTexture(), NULL, &leaderboardButtonRect);
}