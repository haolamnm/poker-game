// Description: This file contains the implementation of the renderLeaderboardScreen function

#include "gui/LeaderboardScreen.h"

int scrollOffset = 0;
int maxScrollOffset = 0;
const int SCROLL_SPEED = 15;

// Function to render the leaderboard screen
void renderLeaderboardScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Render the Leaderboard screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Render the Leaderboard screen title
    SDL_Color textColor = {255, 255, 255, 255};
    game->renderText(renderer, font, "Leaderboard", windowWidth / 2, 50, textColor, true);

    // Load the font for the leaderboard entries
    TTF_Font* leaderboardFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 18);
    if (!leaderboardFont) {
        std::cerr << "Failed to load leaderboard font: " << TTF_GetError() << std::endl;
        return;
    }

    // Get the leaderboard data    
    std::vector<std::vector<std::string>> leaderboard = lobby.handleLeaderboard();
    int nRow = leaderboard.size();
    int nCol = leaderboard[0].size();

    // Define column headers
    const char* headers[] = {"Rank", "Username", "Chips", "Winrate", "Favorite Strategy"};
    int headerCount = sizeof(headers) / sizeof(headers[0]);

    // Define column widths
    int columnWidths[] = {75, 150, 100, 100, 200};

    // Render column headers
    int startX = 50;
    int startY = 150;
    for (int j = 0; j < headerCount; j++) {
        game->renderText(renderer, leaderboardFont, headers[j], startX, startY, textColor, false);
        startX += columnWidths[j];
    }

    maxScrollOffset = std::max(0, (nRow * 30) - (490 - 180)); // Maximum scroll offset

    // Render leaderboard entries
    startY += 40 - scrollOffset; // Move down for the first row of data
    for (int i = 0; i < nRow; i++) {
        startX = 50; // Reset to the start of the row
        for (int j = 0; j < nCol; j++) {
            if (startY >= 180 && startY <= 490) {
                game->renderText(renderer, leaderboardFont, leaderboard[i][j].c_str(), startX, startY, textColor, false);
            }
            startX += columnWidths[j];
        }
        startY += 30; // Move down for the next row
    }

    if ((nRow * 30) > (490 - 180)) {
        game->renderText(renderer, leaderboardFont, "Scroll to view more", windowWidth / 2, 550, textColor, true);
    }

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Close the leaderboard font
    TTF_CloseFont(leaderboardFont);
}

void handleMouseWheelEvent(SDL_Event& event) {
    if (event.type == SDL_MOUSEWHEEL) {
        if (event.wheel.y > 0) {
            scrollOffset -= SCROLL_SPEED;
            if (scrollOffset < 0) {
                scrollOffset = 0;
            }
        } else if (event.wheel.y < 0) {
            scrollOffset += SCROLL_SPEED;
            if (scrollOffset > maxScrollOffset) {
                scrollOffset = maxScrollOffset;
            }
        }
    }
}