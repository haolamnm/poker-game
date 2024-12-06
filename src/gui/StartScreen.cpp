/*
FILE: src/gui/StartScreen.cpp

DESCRIPTION: Implementation file for the start screen. This file is part
of the GUI subsystem and is used to render the start screen. This file
contains the function definition for rendering the start screen.

NOTE: In the start screen, the player can choose to play PvP or PvE mode,
view their user account information, view the tutorial, view the about
screen, view the settings screen, and view the leaderboard.

AUTHOR: Lam Chi Hao.
*/

#include "gui/StartScreen.h"

// Function to render the start screen
void renderStartScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* userInfoButtonTexture = game->getUserInfoButtonTexture();
    SDL_Texture* tutorialButtonTexture = game->getTutorialButtonTexture();
    SDL_Texture* aboutButtonTexture = game->getAboutButtonTexture();
    SDL_Texture* settingsButtonTexture = game->getSettingsButtonTexture();
    SDL_Texture* leaderboardButtonTexture = game->getLeaderboardButtonTexture();
    
    // Render the start screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    
    SDL_RenderClear(renderer);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
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
    SDL_RenderCopy(renderer, userInfoButtonTexture, NULL, &userInfoButtonRect);
    game->handleButtonHover(userInfoButtonTexture, mouseX, mouseY, START_X, START_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the Instruction/Tutorial button
    SDL_Rect tutorialButtonRect = {START_X, START_Y + SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer,tutorialButtonTexture, NULL, &tutorialButtonRect);
    game->handleButtonHover(tutorialButtonTexture, mouseX, mouseY, START_X, START_Y + SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the About the Author button
    SDL_Rect aboutButtonRect = {START_X, START_Y + 2 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, aboutButtonTexture, NULL, &aboutButtonRect);
    game->handleButtonHover(aboutButtonTexture, mouseX, mouseY, START_X, START_Y + 2 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the Settings button
    SDL_Rect settingsButtonRect = {START_X, START_Y + 3 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, settingsButtonTexture, NULL, &settingsButtonRect);
    game->handleButtonHover(settingsButtonTexture, mouseX, mouseY, START_X, START_Y + 3 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the Leaderboard button
    SDL_Rect leaderboardButtonRect = {START_X, START_Y + 4 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, leaderboardButtonTexture, NULL, &leaderboardButtonRect);
    game->handleButtonHover(leaderboardButtonTexture, mouseX, mouseY, START_X, START_Y + 4 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING), SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the current users in the lobby
    renderUsernames(game);
}

// Function to render the usernames
void renderUsernames(GameEngine* game) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 18);
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    SDL_Color deleteColor = {255, 0, 0, 255}; // Red color

    const std::vector<std::string>& usernames = lobby.getUsernames();
    
    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(game->getWindow(), &windowWidth, &windowHeight);

    // Calculate the starting Y position for the usernames
    int startY = windowHeight - 30 * usernames.size() - 10; // 10 pixels padding from the bottom

    for (const std::string& username : usernames) {
        int textWidth, textHeight;
        TTF_SizeText(font, username.c_str(), &textWidth, &textHeight);
        int deleteButtonWidth, deleteButtonHeight;
        TTF_SizeText(font, "x", &deleteButtonWidth, &deleteButtonHeight);
        int startX = windowWidth - textWidth - deleteButtonWidth - 30; // 10 pixels padding from the right and between username and 'x'
        
        // Render the username
        game->renderText(renderer, font, username.c_str(), startX, startY, textColor, false);

        // Render the 'x' button as text
        SDL_Rect deleteButtonRect = {startX + textWidth + 10, startY, deleteButtonWidth, deleteButtonHeight};
        game->renderText(renderer, font, "x", deleteButtonRect.x, deleteButtonRect.y, deleteColor, false);

        startY += 30; // Move down for the next username
    }

    TTF_CloseFont(font);
}