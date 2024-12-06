/*
FILE: include/gui/UserInfoScreen.h

DESCRIPTION: Header file for the user info screen. This file is part. This file contains the function declaration for rendering the user info screen.

NOTE: The user info screen is where the player can create a new account or login to an existing account. After logging in, the player will be pushed into the lobby.

AUTHOR: Lam Chi Hao & Le Nguyen Anh Tri.
*/

#ifndef USER_INFO_SCREEN_H
#define USER_INFO_SCREEN_H

#include "gui/GameEngine.h"
#include "core/Login.h"
#include <SDL2/SDL.h>

void handleTextInput(SDL_Event& event);
void renderUserInfoScreen(GameEngine* game);

#endif