#include "gui/GameEngine.h"

// Pointer to the game object.
GameEngine* game = nullptr;

int main(int argc, char* argv[]) {
    game = new GameEngine();

    // Initialize the game.
    if (game->init("CSC10012 - Poker 🃏", 800, 600, false)) {
        // Set the game loop frame delay.
        const int frameDelay = 1000 / 30; // 30 FPS
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

    // Clean up the game.
    // Destructor is called automatically when the game object goes out of scope.
    delete game;

    return 0;
}