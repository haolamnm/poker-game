// Description: Header file for the leaderboard screen

#ifndef LEADERBOARD_SCREEN_H
#define LEADERBOARD_SCREEN_H

#include <SDL2/SDL.h>
#include "gui/GameEngine.h"

extern int scrollOffset;

// Function to render the leaderboard screen
void renderLeaderboardScreen(GameEngine* game);

// Function to handle the mouse wheel event
void handleMouseWheelEvent(SDL_Event& event);

#endif // LEADERBOARD_SCREEN_H