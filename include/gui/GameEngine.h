/*
FILE: include/gui/GameEngine.h

DESCRIPTION: Header file for the game engine. This file is the 
main game engine that handles the core functions of the game. 
This file contains the GameEngine class declaration, which is 
responsible for initializing the game, handling events, updating 
the game state, rendering the game, and cleaning up resources 
after the game ends.

NOTE: GameEngine class is one of our core classes that manages 
the game loop, rendering, and event handling.

AUTHOR: Lam Chi Hao & Le Nguyen Anh Tri.
*/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "pch.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "../core/Lobby.h"

extern Lobby lobby;

extern bool isDealtPvP;
extern bool isDealtPvE;
extern bool isSavedPvP;
extern bool isSavedPvE;

extern bool isDrawButtonClicked;
extern bool drawButtonFlag;
extern bool isFoldButtonClicked;
extern bool foldButtonFlag;
extern bool isCallButtonClicked;
extern bool callButtonFlag;
extern bool isRaiseButtonClicked;

extern int currentCardIndex;

extern int defaultChipBetted;

class GameEngine {
private:
    bool isRunning;
    bool mouseButtonPressed = false;
    
    // Basic for game loop
    SDL_Window* window;
    SDL_Renderer* renderer;

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
    
    // TODO: Implemt small, medium and big font.
    TTF_Font* font;

    SDL_Rect cardRects[5];
    bool cardRevealed[5];

    Mix_Music* backgroundMusic;
public:
    GameEngine();
    ~GameEngine();

    // Initialize the game engine
    bool init(const char* title, int width, int height, bool fullscreen);
    
    // Basics for game loop
    void handleEvents();
    void update();
    void render();
    void clean();

    bool loadBackgroundMusic(const char* filePath);
    bool playButtonClickSound(const char* filePath);

    void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color, bool centered = false, bool rightAligned = false);

    void toggleBackgroundMusic();
    void toggleSoundEffects();

    bool isMouseHovering(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight);

    void handleButtonHover(SDL_Texture* buttonTexture, int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight);
    
    void renderCards(const char* cardFiles[5], bool allowClick, int fadeCards, bool allFaceDown = true);

    // Function to handle button click events
    void handleNextButtonClickTutorial(int mouseX, int mouseY);
    void handlePrevButtonClickTutorial(int mouseX, int mouseY);

    void handleNextButtonClickSettings(int mouseX, int mouseY);
    void handleRaiseButtonClickSettings(int mouseX, int mouseY);
    
    void handleNextButtonClickPvP(int mouseX, int mouseY);
    void handleDrawButtonClickPvP(int mouseX, int mouseY);
    void handleFoldButtonClickPvP(int mouseX, int mouseY);
    void handleCallButtonClickPvP(int mouseX, int mouseY);
    void handleRaiseButtonClickPvP(int mouseX, int mouseY);
    
    void handleNextButtonClickPvE(int mouseX, int mouseY);

    // Getter functions
    bool running() { 
        return isRunning;
    }
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
    TTF_Font* getFont() { 
        return font; 
    }
    SDL_Window* getWindow() { 
        return window; 
    }
    SDL_Renderer* getRenderer() { 
        return renderer; 
    }
    SDL_Rect* getCardRects() { 
        return cardRects; 
    }
    bool* getCardRevealed() { 
        return cardRevealed; 
    }
    const char* getCurrentGameModeString() const;
    const char* getCurrentRoundString() const;

    // To keep track
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

    enum drawPokerRound {
        FIRST_BETTING_ROUND = 1,
        DRAW_ROUND,
        SECOND_BETTING_ROUND,
        SHOWDOWN_ROUND
    };
    drawPokerRound currentDrawPokerRound;
};

#endif