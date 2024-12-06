/*
FILE: include/gui/SettingsScreen.h

DESCRIPTION: Header file for the settings screen. This file is 
part of the GUI subsystem and is used to render the settings 
screen.

NOTE: We can config the background music, sound effects, and 
game mode in this screen.

AUTHOR: Lam Chi Hao
*/

#ifndef SETTINGS_SCREEN_H
#define SETTINGS_SCREEN_H

#include <SDL2/SDL.h>
#include "gui/GameEngine.h"

void renderSettingsScreen(GameEngine* game);

#endif