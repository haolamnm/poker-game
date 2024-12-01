// Description: Header file for user info screen

#ifndef USER_INFO_SCREEN_H
#define USER_INFO_SCREEN_H

// SLD2
#include <SDL2/SDL.h>

// User-defined
#include "gui/GameEngine.h"
#include "core/Login.h"

// Function to handle the user info screen input
void handleTextInput(SDL_Event& event);

// Function to render the user info screen
void renderUserInfoScreen(GameEngine* game);

#endif // USER_INFO_SCREEN_H