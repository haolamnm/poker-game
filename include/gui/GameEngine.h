// Desscription: Header file for the GameEngine class

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "pch.h"
#include "../core/Lobby.h"

extern Lobby lobby;
extern bool isDealtPvP;
extern bool isDealtPvE;
extern bool isSavedPvP;
extern bool isSavedPvE;
extern bool isDrawButtonClicked;
extern int currentCardIndex;

// Game class: Encapsulates the core functions of the game engine
class GameEngine {
public:
    
    // Constructor: Initializes the game objects
    GameEngine();

    // Destructor: Frees the game objects
    ~GameEngine();

    // Function to initialize the game window and renderer
    bool init(const char* title, int width, int height, bool fullscreen);
    
    // Function to handle events in the game
    void handleEvents();

    // Function to update the game objects
    void update();

    // Function to render the game objects
    void render();

    // Function to clean the game objects
    void clean();

    // Loads and plays the background music.
    bool loadBackgroundMusic(const char* filePath);

    // Function to play a sound when a button is clicked.
    bool playButtonClickSound(const char* filePath);

    // Function to render text on the screen
    void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color, bool centered = false, bool rightAligned = false);

    // Function to toggle background music
    void toggleBackgroundMusic();

    // Function to toggle sound effects
    void toggleSoundEffects();

    // Function to check if a button is clicked
    bool isMouseHovering(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight);

    // Function to handle when a button is hovered
    void handleButtonHover(SDL_Texture* buttonTexture, int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight);
    
    // Function to render 5 cards
    void renderCards(const char* cardFiles[5], bool allowClick, int fadeCards, bool allFaceDown = true);

    // Function to handle next button click
    void handleNextButtonClickTutorial(int mouseX, int mouseY);
    void handlePrevButtonClickTutorial(int mouseX, int mouseY);
    void handleNextButtonClickPvP(int mouseX, int mouseY);
    void handleNextButtonClickPvE(int mouseX, int mouseY);

    void handleNextButtonGameMode(int mouseX, int mouseY);
    void handleDrawButtonClickPvP(int mouseX, int mouseY);

    // Getters for game state
    bool running() { 
        return isRunning;
    }

    // Getters for button textures
    SDL_Texture* getBackButtonTexture() const { 
        return backButtonTexture; 
    }
    SDL_Texture* getNextButtonTexture() const { 
        return nextButtonTexture; 
    }
    SDL_Texture* getPrevButtonTexture() const {
        return prevButtonTexture;
    }
    SDL_Texture* getAboutButtonTexture() const { 
        return aboutButtonTexture; 
    }
    SDL_Texture* getUserInfoButtonTexture() const { 
        return userInfoButtonTexture; 
    }
    SDL_Texture* getTutorialButtonTexture() const { 
        return tutorialButtonTexture; 
    }
    SDL_Texture* getSettingsButtonTexture() const { 
        return settingsButtonTexture; 
    }
    SDL_Texture* getLeaderboardButtonTexture() const { 
        return leaderboardButtonTexture; 
    }
    SDL_Texture* getMusicOnButtonTexture() const { 
        return musicOnButtonTexture; 
    }
    SDL_Texture* getMusicOffButtonTexture() const { 
        return musicOffButtonTexture; 
    }
    SDL_Texture* getSoundOnButtonTexture() const { 
        return soundOnButtonTexture; 
    }
    SDL_Texture* getSoundOffButtonTexture() const { 
        return soundOffButtonTexture; 
    }
    SDL_Texture* getFoldButtonTexture() const { 
        return foldButtonTexture; 
    }
    SDL_Texture* getCallButtonTexture() const { 
        return callButtonTexture; 
    }
    SDL_Texture* getRaiseButtonTexture() const { 
        return raiseButtonTexture; 
    }
    SDL_Texture* getdrawButtonTexture() const { 
        return drawButtonTexture; 
    }

    // Getters for game objects
    TTF_Font* getFont() { 
        return font; 
    }
    SDL_Window* getWindow() { 
        return window; 
    }
    SDL_Renderer* getRenderer() { 
        return renderer; 
    }
    
    // Getters for card states and rectangles
    bool* getCardRevealed() { 
        return cardRevealed; 
    }
    SDL_Rect* getCardRects() { 
        return cardRects; 
    }

    const char* getCurrentGameModeString() const;

    // Current card set
    int currentCardSet = 0;
    int currentPlayer = 0;

    void resetPvPGame();
    void resetPvEGame();

    enum GameMode {
        BASIC_POKER,
        DRAW_POKER,
        NUMBER_OF_GAME_MODES
    };

    GameMode currentGameMode;

private:
    // Indicates if the game is running.
    bool isRunning;

    // Keep track of the mouse button state
    bool mouseButtonPressed = false;

    // Pointer to the SDL window.
    SDL_Window* window;

    // Pointer to the SDL renderer.
    SDL_Renderer* renderer;

    // Enum for game states.
    enum GameState {
        START_SCREEN,
        PVP_SCREEN,
        PVE_SCREEN,
        USER_INFO_SCREEN,
        TUTORIAL_SCREEN,
        ABOUT_SCREEN,
        SETTINGS_SCREEN,
        LEADERBOARD_SCREEN
    };


    // Current game state.
    GameState currentGameState;

    // Button textures
    SDL_Texture* backButtonTexture = nullptr;
    SDL_Texture* nextButtonTexture = nullptr;
    SDL_Texture* prevButtonTexture = nullptr;
    SDL_Texture* aboutButtonTexture = nullptr;
    SDL_Texture* userInfoButtonTexture = nullptr;
    SDL_Texture* tutorialButtonTexture = nullptr;
    SDL_Texture* settingsButtonTexture = nullptr;
    SDL_Texture* leaderboardButtonTexture = nullptr;
    SDL_Texture* musicOnButtonTexture = nullptr;
    SDL_Texture* musicOffButtonTexture = nullptr;
    SDL_Texture* soundOnButtonTexture = nullptr;
    SDL_Texture* soundOffButtonTexture = nullptr;
    SDL_Texture* foldButtonTexture = nullptr;
    SDL_Texture* callButtonTexture = nullptr;
    SDL_Texture* drawButtonTexture = nullptr;
    SDL_Texture* raiseButtonTexture = nullptr;
    
    // Font
    TTF_Font* font;

    // Card textures and rectangles
    SDL_Rect cardRects[5];

    // Array to keep track of revealed cards
    bool cardRevealed[5];

    // Pointer to the background music.
    Mix_Music* backgroundMusic;
};

#endif