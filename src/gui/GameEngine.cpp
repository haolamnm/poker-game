
/*
FILE: src/GUI/GameEngine.cpp

DESCRIPTION: Implementation file for the GameEngine class. This 
file is part of the GUI subsystem. This file contains the function definitions for initializing the game engine, handling 
events, updating the game state, rendering the game objects, and 
cleaning up the game engine.

NOTE: There are several game states in the game engine, such as
the start screen, PvP screen, PvE screen, user info screen,
tutorial screen, about screen, settings screen, and leaderboard
screen.

AUTHOR: Lam Chi Hao & Le Nguyen Anh Tri.
*/

#include "gui/GameEngine.h"
#include "gui/PvPScreen.h"
#include "gui/PvEScreen.h"
#include "gui/AboutScreen.h"
#include "gui/StartScreen.h"
#include "gui/UserInfoScreen.h"
#include "gui/TutorialScreen.h"
#include "gui/SettingsScreen.h"
#include "gui/LeaderboardScreen.h"

Lobby lobby;

// Constructor: Initializes the game objects.
GameEngine::GameEngine() {
    isRunning = false;
    bigFontVintage = nullptr;
    mediumFontVintage = nullptr;
    smallFontVintage = nullptr;
    window = nullptr;
    renderer = nullptr;
    backgroundMusic = nullptr;
    currentGameMode = BASIC_POKER;
    currentGameState = START_SCREEN;
    currentDrawPokerRound = FIRST_BETTING_ROUND;
    
    // Initialize the card states and rectangles
    for (int i = 0; i < 5; ++i) {
        cardRevealed[i] = false;
        cardRects[i] = SDL_Rect{0, 0, 0, 0};
    }

    std::cout << GREEN_TEXT << "GameEngine constructor called." << RESET_TEXT << std::endl;
}

// Destructor: Frees the game objects.
GameEngine::~GameEngine() {
    std::cout << YELLOW_TEXT << "GameEngine destructor called." << RESET_TEXT << std::endl;
    clean();
}

bool GameEngine::init(const char* title, int width, int height, bool fullscreen) {
    // NOTE: Initialize SDL.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << RED_TEXT << "SDL Initialization failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Initialize SDL_TTF.
    if (TTF_Init() == -1) {
        std::cerr << RED_TEXT << "TTF Initialization failed: " << TTF_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Initialize SDL_mixer.
    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNK_SIZE) < 0) {
        std::cerr << RED_TEXT << "SDL_mixer initialization failed: " << Mix_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Allocate 16 channels for audio mixing.
    Mix_AllocateChannels(16);

    // NOTE: Create the window for the game.
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window) {
        std::cerr << RED_TEXT << "Window creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Create the renderer for the game.
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << RED_TEXT << "Renderer creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Load the font for the game.
    bigFontVintage = TTF_OpenFont(FONT_VINTAGE_PATH, BIG_FONT_SIZE);
    if (!bigFontVintage) {
        std::cerr << RED_TEXT << "Failed to load font: " << TTF_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    mediumFontVintage = TTF_OpenFont(FONT_VINTAGE_PATH, MEDIUM_FONT_SIZE);
    if (!mediumFontVintage) {
        std::cerr << RED_TEXT << "Failed to load font: " << TTF_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    smallFontVintage = TTF_OpenFont(FONT_VINTAGE_PATH, SMALL_FONT_SIZE);
    if (!smallFontVintage) {
        std::cerr << RED_TEXT << "Failed to load font: " << TTF_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Load the background music for the game.
    if (!loadBackgroundMusic(BACKGROUND_MUSIC_PATH)) {
        std::cerr << RED_TEXT << "Failed to load background music." << RESET_TEXT << std::endl;
        return false;
    }

    // NOTE: Load the icon for the game window.
    SDL_Surface* icon = IMG_Load(ICON_PATH);
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    } else {
        std::cerr << RED_TEXT << "Icon loading failed: " << SDL_GetError() << RESET_TEXT << std::endl;
    }

    // NOTE: Load the cursor for the game window.
    SDL_Surface* cursorSurface = IMG_Load(CURSOR_PATH);
    if (!cursorSurface) {
        std::cerr << RED_TEXT << "Cursor image loading failed: " << IMG_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    SDL_FreeSurface(cursorSurface);
    if (!cursor) {
        std::cerr << RED_TEXT << "Cursor creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    SDL_SetCursor(cursor);

    // NOTE: Load the button images for the game.
    backButtonTexture = IMG_LoadTexture(renderer, BUTTON_HOME_PATH);
    nextButtonTexture = IMG_LoadTexture(renderer, BUTTON_NEXT_PATH);
    prevButtonTexture = IMG_LoadTexture(renderer, BUTTON_PREV_PATH);
    aboutButtonTexture = IMG_LoadTexture(renderer, BUTTON_ABOUT_PATH);
    tutorialButtonTexture = IMG_LoadTexture(renderer, BUTTON_TUTORIAL_PATH);
    settingsButtonTexture = IMG_LoadTexture(renderer, BUTTON_SETTINGS_PATH);
    userInfoButtonTexture = IMG_LoadTexture(renderer, BUTTON_USER_INFO_PATH);
    leaderboardButtonTexture = IMG_LoadTexture(renderer, BUTTON_LEADERBOARD_PATH);
    musicOnButtonTexture = IMG_LoadTexture(renderer, BUTTON_MUSIC_ON_PATH);
    musicOffButtonTexture = IMG_LoadTexture(renderer, BUTTON_MUSIC_OFF_PATH);
    soundOnButtonTexture = IMG_LoadTexture(renderer, BUTTON_SOUND_ON_PATH);
    soundOffButtonTexture = IMG_LoadTexture(renderer, BUTTON_SOUND_OFF_PATH);
    foldButtonTexture = IMG_LoadTexture(renderer, BUTTON_FOLD_PATH);
    callButtonTexture = IMG_LoadTexture(renderer, BUTTON_CALL_PATH);
    drawButtonTexture = IMG_LoadTexture(renderer, BUTTON_RESET_PATH);
    raiseButtonTexture = IMG_LoadTexture(renderer, BUTTON_RAISE_PATH);
    
    if (!aboutButtonTexture || 
        !backButtonTexture  ||
        !nextButtonTexture  ||
        !prevButtonTexture  ||
        !userInfoButtonTexture || 
        !tutorialButtonTexture ||
        !settingsButtonTexture || 
        !leaderboardButtonTexture ||
        !musicOnButtonTexture  ||
        !musicOffButtonTexture ||
        !soundOnButtonTexture  ||
        !soundOffButtonTexture || 
        !foldButtonTexture     ||
        !callButtonTexture     ||
        !raiseButtonTexture    ||
        !drawButtonTexture) {
        std::cerr << RED_TEXT << "Failed to load button images: " << IMG_GetError() << RESET_TEXT << std::endl;
        return false;
    }

    isRunning = true;
    std::cout << GREEN_TEXT << "GameEngine initialized successfully." << RESET_TEXT << std::endl;
    
    return true;
}

bool isButtonClicked(int x, int y, int buttonX, int buttonY, int buttonWidth = SMALL_BUTTON_WIDTH, int buttonHeight = SMALL_BUTTON_HEIGHT) {
    return x >= buttonX && x <= buttonX + buttonWidth && y >= buttonY && y <= buttonY + buttonHeight;
}

void GameEngine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        handleTextInput(event);
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y);
            // CHECK: Buttons clicked in the start screen.
            if (currentGameState == START_SCREEN) {
                // CHECK: PVP button clicked.
                if (isButtonClicked(x, y, PVP_BUTTON_X, PVP_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT)) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = PVP_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: PvP screen" << RESET_TEXT << std::endl;
                    resetPvPGame();
                }
                // CHECK: PVE button clicked.
                else if (isButtonClicked(x, y, PVE_BUTTON_X, PVE_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT)) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = PVE_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: PvE screen" << RESET_TEXT << std::endl;
                    resetPvEGame();
                }
                // CHECK: User Info button clicked.
                else if (isButtonClicked(x, y, START_X, START_Y)) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = USER_INFO_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: User Info screen" << RESET_TEXT << std::endl;
                }
                // CHECK: Tutorial button clicked.
                else if (isButtonClicked(x, y, START_X, START_Y + SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING)) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = TUTORIAL_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: Tutorial screen" << RESET_TEXT << std::endl;
                }
                // CHECK: About Us button clicked.
                else if (isButtonClicked(x, y, START_X, START_Y + 2 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING))) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = ABOUT_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: About screen" << RESET_TEXT << std::endl;
                }
                // CHECK: Settings button clicked.
                else if (isButtonClicked(x, y, START_X, START_Y + 3 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING))) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = SETTINGS_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: Settings screen" << RESET_TEXT << std::endl;
                }
                // CHECK: Leaderboard button clicked.
                else if (isButtonClicked(x, y, START_X, START_Y + 4 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING))) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = LEADERBOARD_SCREEN;
                    scrollOffset = 0;
                    std::cout << BLUE_TEXT << "Current state: Leaderboard screen" << RESET_TEXT << std::endl;
                }
                // RENDER: Create new account button.
                const std::vector<std::string>& usernames = lobby.getUsernames();
                int startY = WINDOW_HEIGHT - 30 * usernames.size() - 10; // 10 pixels padding from the bottom
                for (size_t i = 0; i < usernames.size(); ++i) {
                    int textWidth, textHeight;
                    TTF_SizeText(bigFontVintage, usernames[i].c_str(), &textWidth, &textHeight);
                    int deleteButtonWidth, deleteButtonHeight;
                    TTF_SizeText(bigFontVintage, "x", &deleteButtonWidth, &deleteButtonHeight);
                    int startX = WINDOW_WIDTH - textWidth - deleteButtonWidth - 30;
                    SDL_Rect deleteButtonRect = {startX + textWidth + 10, startY, deleteButtonWidth, deleteButtonHeight};
                    if (x >= deleteButtonRect.x && x <= deleteButtonRect.x + deleteButtonRect.w &&
                        y >= deleteButtonRect.y && y <= deleteButtonRect.y + deleteButtonRect.h) {
                        lobby.removeUsername(usernames[i]);
                        break;
                    }
                    startY += 30; // 30 pixels spacing between usernames
                }
            // CHECK: Back button clicked.
            } else if (currentGameState == PVP_SCREEN || 
                        currentGameState == PVE_SCREEN || 
                        currentGameState == ABOUT_SCREEN ||
                        currentGameState == SETTINGS_SCREEN  || 
                        currentGameState == TUTORIAL_SCREEN  || 
                        currentGameState == USER_INFO_SCREEN ||
                        currentGameState == LEADERBOARD_SCREEN) {
                if (isButtonClicked(x, y, START_X, START_X)) {
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                    currentGameState = START_SCREEN;
                    std::cout << BLUE_TEXT << "Current state: Start screen" << RESET_TEXT << std::endl;
                }
            }
            // HANDLE: Buttons clicked in the tutorial screen.
            if (currentGameState == TUTORIAL_SCREEN) {
                handleNextButtonClickTutorial(x, y);
                handlePrevButtonClickTutorial(x, y);
            // HANDLE: Buttons clicked in the leaderboard screen.
            } else if (currentGameState == PVP_SCREEN) {
                handleNextButtonClickPvP(x, y);
                if (currentGameMode == DRAW_POKER) {
                    if (currentDrawPokerRound == DRAW_ROUND) {
                        if (drawButtonFlag == false) handleDrawButtonClickPvP(x, y);
                    }
                    if (currentDrawPokerRound == FIRST_BETTING_ROUND || currentDrawPokerRound == SECOND_BETTING_ROUND) {
                        if (callButtonFlag == false) handleCallButtonClickPvP(x, y);
                        if (foldButtonFlag == false) handleFoldButtonClickPvP(x, y);
                        handleRaiseButtonClickPvP(x, y);
                    }
                }
            } else if (currentGameState == PVE_SCREEN) {
                handleNextButtonClickPvE(x, y);
            } else if (currentGameState == SETTINGS_SCREEN) {
                handleNextButtonClickSettings(x, y);
                handleRaiseButtonClickSettings(x, y);
            }
            break;
        case SDL_MOUSEWHEEL:
            handleMouseWheelEvent(event);
            break;
        default:
            break;
        }
    }
}

void GameEngine::update() {
    // Update game state
}

void GameEngine::render() {
    if (currentGameState == START_SCREEN) {
        renderStartScreen(this);
    } else if (currentGameState == PVP_SCREEN) {
        renderPvPScreen(this);
    } else if (currentGameState == PVE_SCREEN) {
        renderPvEScreen(this);
    } else if (currentGameState == ABOUT_SCREEN) {
        renderAboutScreen(this);
    } else if (currentGameState == TUTORIAL_SCREEN) {
        renderTutorialScreen(this);
    } else if (currentGameState == SETTINGS_SCREEN) {
        renderSettingsScreen(this);
    } else if (currentGameState == USER_INFO_SCREEN) {
        renderUserInfoScreen(this);
    } else if (currentGameState == LEADERBOARD_SCREEN) {
        renderLeaderboardScreen(this);
    } else {
        SDL_Log("Unexpected game state: %d", currentGameState);
    }
    SDL_RenderPresent(renderer);
}

void GameEngine::clean() {
    std::cout << YELLOW_TEXT << "Cleaning up GameEngine..." << RESET_TEXT << std::endl;
    if (bigFontVintage) {
        TTF_CloseFont(bigFontVintage);
        bigFontVintage = nullptr;
    }
    if (mediumFontVintage) {
        TTF_CloseFont(mediumFontVintage);
        mediumFontVintage = nullptr;
    }
    if (smallFontVintage) {
        TTF_CloseFont(smallFontVintage);
        smallFontVintage = nullptr;
    }
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    if (backButtonTexture) {
        SDL_DestroyTexture(backButtonTexture);
        backButtonTexture = nullptr;
    }
    if (nextButtonTexture) {
        SDL_DestroyTexture(nextButtonTexture);
        nextButtonTexture = nullptr;
    }
    if (prevButtonTexture) {
        SDL_DestroyTexture(prevButtonTexture);
        prevButtonTexture = nullptr;
    }
    if (aboutButtonTexture) {
        SDL_DestroyTexture(aboutButtonTexture);
        aboutButtonTexture = nullptr;
    }
    if (tutorialButtonTexture) {
        SDL_DestroyTexture(tutorialButtonTexture);
        tutorialButtonTexture = nullptr;
    }
    if (settingsButtonTexture) {
        SDL_DestroyTexture(settingsButtonTexture);
        settingsButtonTexture = nullptr;
    }
    if (userInfoButtonTexture) {
        SDL_DestroyTexture(userInfoButtonTexture);
        userInfoButtonTexture = nullptr;
    }
    if (leaderboardButtonTexture) {
        SDL_DestroyTexture(leaderboardButtonTexture);
        leaderboardButtonTexture = nullptr;
    }
    if (musicOnButtonTexture) {
        SDL_DestroyTexture(musicOnButtonTexture);
        musicOnButtonTexture = nullptr;
    }
    if (musicOffButtonTexture) {
        SDL_DestroyTexture(musicOffButtonTexture);
        musicOffButtonTexture = nullptr;
    }
    if (soundOnButtonTexture) {
        SDL_DestroyTexture(soundOnButtonTexture);
        soundOnButtonTexture = nullptr;
    }
    if (soundOffButtonTexture) {
        SDL_DestroyTexture(soundOffButtonTexture);
        soundOffButtonTexture = nullptr;
    }
    if (foldButtonTexture) {
        SDL_DestroyTexture(foldButtonTexture);
        foldButtonTexture = nullptr;
    }
    if (callButtonTexture) {
        SDL_DestroyTexture(callButtonTexture);
        callButtonTexture = nullptr;
    }
    if (raiseButtonTexture) {
        SDL_DestroyTexture(raiseButtonTexture);
        raiseButtonTexture = nullptr;
    }
    if (drawButtonTexture) {
        SDL_DestroyTexture(drawButtonTexture);
        drawButtonTexture = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
    Mix_CloseAudio();
    std::cout << GREEN_TEXT << "GameEngine cleaned." << RESET_TEXT << std::endl;
}

bool GameEngine::loadBackgroundMusic(const char* filePath) {
    backgroundMusic = Mix_LoadMUS(filePath);
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
        return false;
    }
    Mix_VolumeMusic(BACKGROUND_MUSIC_VOLUME);

    // NOTE: Play the background music on loop.
    Mix_PlayMusic(backgroundMusic, -1);
    return true;
}

bool GameEngine::playButtonClickSound(const char* filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (!sound) {
        std::cerr << RED_TEXT << "Failed to load sound effect: " << Mix_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    int channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1) {
        std::cerr << "Failed to play sound effect: " << Mix_GetError() << std::endl;
        Mix_FreeChunk(sound);
        return false;
    }
    return true;
}

void GameEngine::renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color, bool centered, bool rightAligned) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        if (textTexture) {
            int textWidth, textHeight;
            TTF_SizeText(font, text, &textWidth, &textHeight);
            SDL_Rect textRect = {x, y, textWidth, textHeight};
            if (centered) {
                textRect.x -= textWidth / 2;
            }
            if (rightAligned) {
                textRect.x -= textWidth;
            }
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        } else {
            std::cerr << RED_TEXT << "Text texture creation failed: " << RESET_TEXT << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << RED_TEXT << "Text surface creation failed: " << RESET_TEXT << TTF_GetError() << std::endl;
    }
}

bool GameEngine::isMouseHovering(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    return mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
}

void GameEngine::handleButtonHover(SDL_Texture* buttonTexture, int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    if (isMouseHovering(mouseX, mouseY, buttonX, buttonY, buttonWidth, buttonHeight)) {
        // NOTE: Reduce the brightness of the button when hovered.
        SDL_SetTextureColorMod(buttonTexture, 200, 200, 200);
    } else {
        SDL_SetTextureColorMod(buttonTexture, 255, 255, 255);
    }
}

void GameEngine::renderCards(const char* cardFiles[5], bool allowClick, int fadeCards, bool allFaceDown) {
    SDL_Renderer* renderer = getRenderer();

    // Calculate the horizontal spacing between cards
    int totalCardWidth = 5 * CARD_WIDTH;
    int spacing = (WINDOW_WIDTH - totalCardWidth) / 6; // 6 spaces between 5 cards
    
    // Calculate the vertical position of the cards
    int startY = (WINDOW_HEIGHT - CARD_HEIGHT) / 2;

    // Load the back of the card image
    SDL_Surface* backSurface = IMG_Load(CARD_BACK);
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
    SDL_FreeSurface(backSurface);

    // Get the mouse coordinates
    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

    for (int i = 0; i < 5; ++i) {
        int startX = spacing + i * (CARD_WIDTH + spacing);
        SDL_Rect cardRect = {startX, startY, CARD_WIDTH, CARD_HEIGHT};
        getCardRects()[i] = cardRect;

        // Load the front of the card image
        SDL_Surface* cardSurface = IMG_Load(cardFiles[i]);
        SDL_Texture* cardTexture = SDL_CreateTextureFromSurface(renderer, cardSurface);
        SDL_FreeSurface(cardSurface);

        if (!cardTexture) {
            std::cerr << RED_TEXT << "Failed to load card image: " << IMG_GetError() << RESET_TEXT << std::endl;
            continue;
        }
        if (allFaceDown == true) {
            Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                if (currentGameState == START_SCREEN) {
                    if (isButtonClicked(mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT) ||
                        isButtonClicked(mouseX, mouseY, PVP_BUTTON_X, PVP_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT) ||
                        isButtonClicked(mouseX, mouseY, PVE_BUTTON_X, PVE_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT)) {
                        for (int i = 0; i < 5; ++i) {
                            getCardRevealed()[i] = false;
                        }
                    }
                } else if (currentGameState == PVP_SCREEN || currentGameState == PVE_SCREEN) {
                    if (isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT)) {
                        for (int i = 0; i < 5; ++i) {
                            getCardRevealed()[i] = false;
                        }
                    }
                }
            }
        }
        // Determine if the card should be faded
        if (i >= 5 - fadeCards) {
            SDL_SetTextureAlphaMod(cardTexture, 128);
        } else {
            SDL_SetTextureAlphaMod(cardTexture, 255);
        }
        // Handle card reveal logic
        if (foldButtonFlag == false && allowClick && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
            if (!mouseButtonPressed && 
                mouseX >= cardRect.x && mouseX <= cardRect.x + cardRect.w &&
                mouseY >= cardRect.y && mouseY <= cardRect.y + cardRect.h) {
                getCardRevealed()[i] = !getCardRevealed()[i];
                mouseButtonPressed = true;
            }
        } else if (foldButtonFlag == false && currentDrawPokerRound == DRAW_ROUND && allowClick && (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))) {
            // when user right clicks, render outline of the current card index
            if (!mouseButtonPressed && 
                mouseX >= cardRect.x && mouseX <= cardRect.x + cardRect.w &&
                mouseY >= cardRect.y && mouseY <= cardRect.y + cardRect.h) {
                currentCardIndex = i;
                mouseButtonPressed = true;
            }
        } else {
            mouseButtonPressed = false;
        }
        // Render the card texture or back texture based on reveal state
        if (allowClick && !getCardRevealed()[i]) {
            SDL_RenderCopy(renderer, backTexture, NULL, &cardRect);
        } else {
            SDL_RenderCopy(renderer, cardTexture, NULL, &cardRect);
        }
        SDL_DestroyTexture(cardTexture);
    }
    if (backTexture) {
        SDL_DestroyTexture(backTexture);
    } else {
        std::cerr << "Back texture was already NULL: " << SDL_GetError() << std::endl;
    }
}

void GameEngine::handleNextButtonClickTutorial(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y)) {
        currentCardSet = (currentCardSet + 1) % 9;
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handlePrevButtonClickTutorial(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, PREV_BUTTON_X, PREV_BUTTON_Y)) {
        currentCardSet = (currentCardSet - 1 + 9) % 9;
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handleNextButtonClickPvP(int mouseX, int mouseY) {
    std::vector<std::string> usernames = lobby.getUsernames();
    if (currentPlayer < static_cast<int>(usernames.size()) && isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y)) {
        currentPlayer += 1;
        if (currentDrawPokerRound == DRAW_ROUND) {
            drawButtonFlag = false;
        } else if (currentDrawPokerRound == FIRST_BETTING_ROUND || currentDrawPokerRound == SECOND_BETTING_ROUND) {
            callButtonFlag = false;
        }
    } 
}

void GameEngine::handleNextButtonClickPvE(int mouseX, int mouseY) {
    std::vector<std::string> usernames = lobby.getUsernames();
    // TODO: Implement extern variable for number of bots
    if (currentPlayer < static_cast<int>(usernames.size()) + 5 && isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y)) {
        currentPlayer += 1;
    }
}

void GameEngine::handleNextButtonClickSettings(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y)) {
        currentGameMode = static_cast<GameMode>((currentGameMode + 1) % NUMBER_OF_GAME_MODES);
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handleDrawButtonClickPvP(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, DRAW_BUTTON_X, DRAW_BUTTON_Y)) {
        isDrawButtonClicked = true;
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handleCallButtonClickPvP(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, CALL_BUTTON_X, CALL_BUTTON_Y)) {
        isCallButtonClicked = true;
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handleFoldButtonClickPvP(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, FOLD_BUTTON_X, FOLD_BUTTON_Y)) {
        isFoldButtonClicked = true;
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handleRaiseButtonClickPvP(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, RAISE_BUTTON_X, RAISE_BUTTON_Y)) {
        isRaiseButtonClicked = true;        
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::handleRaiseButtonClickSettings(int mouseX, int mouseY) {
    if (isButtonClicked(mouseX, mouseY, RAISE_BUTTON_X, RAISE_BUTTON_Y)) {
        defaultChipBetted += 20;     
        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
    }
}

void GameEngine::resetPvPGame() {
    currentPlayer = 0;
    isDealtPvP = false;
    isSavedPvP = false;
    isDrawButtonClicked = false;
    drawButtonFlag = false;
    isCallButtonClicked = false;
    callButtonFlag = false;
    isFoldButtonClicked = false;
    foldButtonFlag = false;
    isRaiseButtonClicked = false;
    currentCardIndex = -1;
    currentDrawPokerRound = FIRST_BETTING_ROUND;
    
    for (int i = 0; i < 5; i++) {
        getCardRevealed()[i] = false;
    }
}

void GameEngine::resetPvEGame() {
    currentPlayer = 0;
    isDealtPvE = false;
    isSavedPvE = false;
    for (int i = 0; i < 5; i++) {
        getCardRevealed()[i] = false;
    }
}

const char* GameEngine::getCurrentGameModeString() const {
    switch (currentGameMode) {
        case BASIC_POKER:
            return "Basic Poker";
        case DRAW_POKER:
            return "Draw Poker";
        default:
            return "Unknown";
    }
}

const char* GameEngine::getCurrentRoundString() const {
    switch (currentDrawPokerRound) {
        case FIRST_BETTING_ROUND:
            return "ROUND 1: Betting";
        case DRAW_ROUND:
            return "ROUND 2: Draw";
        case SECOND_BETTING_ROUND:
            return "ROUND 3: Betting";
        case SHOWDOWN_ROUND:
            return "ROUND 4: Showdown";
        default:
            return "Unknown Round";
    }
}
