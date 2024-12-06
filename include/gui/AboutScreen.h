/*
FILE: include/gui/AboutScreen.h

DESCRIPTION: Header file for the about screen. This file is part 
of the GUI subsystem and is used to render the about screen. 
This file contains the function declaration for rendering the 
about screen.

NOTE: The about screen is where the player can view information 
about the game.

AUTHOR: Lam Chi Hao.
*/

#ifndef ABOUT_SCREEN_H
#define ABOUT_SCREEN_H

#include "gui/GameEngine.h"
#include <SDL2/SDL.h>

void renderAboutScreen(GameEngine* game);

#endif