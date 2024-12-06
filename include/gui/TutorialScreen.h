/*
FILE: include/gui/TutorialScreen.h

DESCRIPTION: Header file for the tutorial screen. This file is 
part of the GUI subsystem and is used to render the tutorial 
screen. This file contains the function declaration for 
rendering the tutorial screen.

NOTE: The tutorial screen is where the player can view the
poker card combinations and their corresponding strengths.

AUTHOR: Lam Chi Hao.
*/

#ifndef TUTORIAL_SCREEN_H
#define TUTORIAL_SCREEN_H

#include "gui/GameEngine.h"
#include <SDL2/SDL.h>

void renderTutorialScreen(GameEngine* game);

#endif