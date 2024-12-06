/*
FILE: include/gui/PvPScreen.h

DESCRIPTION: Header file for the Player vs Player (PvP) screen. 
This file is part of the GUI subsystem and is used to render the 
PvP screen. This file contains the function declaration for 
rendering the PvP screen.

NOTE: PvP availables in all game mode.

AUTHOR: Lam Chi Hao.
*/

#ifndef PVP_SCREEN_H
#define PVP_SCREEN_H

#include "gui/GameEngine.h"
#include "core/Gameplay.h"
#include <SDL2/SDL.h>

void renderPvPScreen(GameEngine* game);

#endif