/*
FILE: include/gui/LeaderboardScreen.h

DESCRIPTION: Header file for the leaderboard screen. This file 
is part of the GUI subsystem and is used to render the 
leaderboard screen. This file contain the function declaration 
for rendering the leaderboard screen.

NOTE: The leaderboard screen is where the player can view the 
leaderboard of the game. The leaderboard shows the top players 
based on their winrate.

AUTHOR: Lam Chi Hao.
*/

#ifndef LEADERBOARD_SCREEN_H
#define LEADERBOARD_SCREEN_H

#include "gui/GameEngine.h"
#include <SDL2/SDL.h>

extern int scrollOffset;

void renderLeaderboardScreen(GameEngine* game);
void handleMouseWheelEvent(SDL_Event& event);

#endif