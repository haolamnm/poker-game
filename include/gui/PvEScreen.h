/*
FILE: include/gui/PvEScreen.h

Description: Header file for the Player vs Environment (PvE) 
screen. This file is part of the GUI subsystem and is used to 
render the PvE screen. This file contains the function 
declaration for rendering the PvE screen.

NOTE: PvE only availables in the BASIC POKER game mode.

AUTHOR: Lam Chi Hao.
*/

#ifndef PVE_SCREEN_H
#define PVE_SCREEN_H

#include "gui/GameEngine.h"
#include "core/Gameplay.h"
#include <SDL2/SDL.h>

void renderPvEScreen(GameEngine* game);

#endif