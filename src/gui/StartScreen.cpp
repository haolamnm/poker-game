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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &pvpButtonRect);
    game->renderText(renderer, font, "PvP", PVP_BUTTON_X + BIG_BUTTON_WIDTH / 2, PVP_BUTTON_Y + BIG_BUTTON_HEIGHT / 2 - 45, textColor, true);

    // Render the PvE Mode button
    SDL_Rect pveButtonRect = {PVE_BUTTON_X, PVE_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &pveButtonRect);
    game->renderText(renderer, font, "PvE", PVE_BUTTON_X + BIG_BUTTON_WIDTH / 2, PVE_BUTTON_Y + BIG_BUTTON_HEIGHT / 2 - 45, textColor, true);

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

    // Render the current users in the lobby
    renderUsernames(game);
}

// Function to render the usernames
void renderUsernames(GameEngine* game) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 18);
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    const std::vector<std::string>& usernames = lobby.getUsernames();
    
    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(game->getWindow(), &windowWidth, &windowHeight);

    // Calculate the starting Y position for the usernames
    int startY = windowHeight - 30 * usernames.size() - 10; // 10 pixels padding from the bottom

    for (const std::string& username : usernames) {
        int textWidth, textHeight;
        TTF_SizeText(font, username.c_str(), &textWidth, &textHeight);
        int startX = windowWidth - textWidth - 10; // 10 pixels padding from the right
        game->renderText(renderer, font, username.c_str(), startX, startY, textColor, false);
        startY += 30; // Move down for the next username
    }

    TTF_CloseFont(font);
}