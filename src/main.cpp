/*
FILE: src/main.cpp

DESCRIPTION: 

NOTE: 

AUTHOR: Lam Chi Hao.
*/

#include "gui/GameEngine.h"

GameEngine* game = nullptr;

int main(int argc, char* argv[]) {
    game = new GameEngine();

    // Initialize the game.
    if (game->init("CSC10012 - Poker 🃏", 800, 600, false)) {
        // Set the game loop frame delay.
        const int frameDelay = 1000 / 60; // 60 FPS
        Uint32 frameStart;
        int frameTime;

        // Run the game loop.
        while (game->running()) {
            // Get the current frame start time.
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            // Delay the game loop to achieve the desired frame rate.
            frameTime = SDL_GetTicks() - frameStart;

            // If the frame delay is greater than the frame time, delay the game loop.
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }

    delete game;
    return 0;
}