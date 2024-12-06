/*
FILE: include/gui/StartScreen.h

DESCRIPTION: Header file for the start screen. This file is part 
of the GUI subsystem and is used to render the start screen. 
This file contains the function declaration for rendering the 
start screen.

NOTE: The start screen is the first screen that the player sees 
when they open the game. It contains the game title and buttons 
to navigate to other screens.

AUTHOR: Lam Chi Hao.
*/

#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "gui/GameEngine.h"
#include <SDL2/SDL.h>

void renderStartScreen(GameEngine* game);
void renderUsernames(GameEngine* game);

#endif