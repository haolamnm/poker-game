// Description: Implementation of the GameEngine class.

#include "gui/GameEngine.h"
#include "gui/PvPScreen.h"
#include "gui/PvEScreen.h"
#include "gui/AboutScreen.h"
#include "gui/StartScreen.h"
#include "gui/UserInfoScreen.h"
#include "gui/TutorialScreen.h"
#include "gui/SettingsScreen.h"
#include "gui/LeaderboardScreen.h"

// Constants for audio playback
constexpr int AUDIO_FREQUENCY = 44100;
constexpr int AUDIO_CHANNELS = 2;
constexpr int AUDIO_CHUNK_SIZE = 2048;

// Constant for font size
constexpr int FONT_SIZE = 64;

// Constant paths for game assets
constexpr const char* FONT_PATH = "assets/fonts/SVN-Vintage.otf";
constexpr const char* ICON_PATH = "assets/imgs/icon/icon.png";
constexpr const char* CURSOR_PATH = "assets/imgs/cursor/cursor.png";

constexpr const char* BUTTON_HOME_PATH = "assets/imgs/buttons/home.png";
constexpr const char* BUTTON_NEXT_PATH = "assets/imgs/buttons/arrow_right.png";
constexpr const char* BUTTON_ABOUT_PATH = "assets/imgs/buttons/about_us.png";
constexpr const char* BUTTON_TUTORIAL_PATH = "assets/imgs/buttons/tutorial.png";
constexpr const char* BUTTON_SETTINGS_PATH = "assets/imgs/buttons/settings.png";
constexpr const char* BUTTON_USER_INFO_PATH = "assets/imgs/buttons/user_info.png";
constexpr const char* BUTTON_LEADERBOARD_PATH = "assets/imgs/buttons/leaderboard.png";
// constexpr const char* BUTTON_MUSIC_PATH = "assets/imgs/buttons/background_music_off.png";
// constexpr const char* BUTTON_SOUND_PATH = "assets/imgs/buttons/sound_effects_off.png";
// constexpr const char* BUTTON_PVP_PATH = "assets/imgs/buttons/pvp.png";
// constexpr const char* BUTTON_PVE_PATH = "assets/imgs/buttons/pve.png";

constexpr const char* BUTTON_CLICK_SOUND_PATH = "assets/audios/button_click.wav";
constexpr const char* BACKGROUND_MUSIC_PATH = "assets/audios/background_music.mp3";

constexpr const char* BACK_CARD_PATH = "assets/imgs/cards/BACK.png";

// Constants for background music volume
constexpr int BACKGROUND_MUSIC_VOLUME = 32; // 0 to 128

Lobby lobby;

// Constructor: Initializes the game objects.
GameEngine::GameEngine() {
    isRunning = false;
    font = nullptr;
    window = nullptr;
    renderer = nullptr;
    backgroundMusic = nullptr;
    currentState = START_SCREEN;
    
    
    // Initialize the card states and rectangles
    for (int i = 0; i < 5; ++i) {
        cardRevealed[i] = false;
        cardRects[i] = SDL_Rect{0, 0, 0, 0};
    }
    
    // Console debug statement
    std::cout << GREEN_TEXT << "GameEngine constructor called." << RESET_TEXT << std::endl;
}

// Destructor: Frees the game objects.
GameEngine::~GameEngine() {
    std::cout << YELLOW_TEXT << "GameEngine destructor called." << RESET_TEXT << std::endl;
    clean();
}

// Function to initialize the game engine
bool GameEngine::init(const char* title, int width, int height, bool fullscreen) {
    // Initialize SDL
    // Purpose: To create the game window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << RED_TEXT << "SDL Initialization failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "SDL initialized successfully." << RESET_TEXT << std::endl;

    // Initialize SDL_TTF for text rendering
    // Purpose: To render text on the screen
    if (TTF_Init() == -1) {
        std::cerr << RED_TEXT << "TTF Initialization failed: " << TTF_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "TTF initialized successfully." << RESET_TEXT << std::endl;

    // Initialize SDL_mixer for audio playback
    // Purpose: To play background music and sound effects
    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNK_SIZE) < 0) {
        std::cerr << RED_TEXT << "SDL_mixer initialization failed: " << Mix_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "SDL_mixer initialized successfully." << RESET_TEXT << std::endl;

    // Allocate 16 channels for sound effects
    // Purpose: To play multiple sound effects simultaneously
    Mix_AllocateChannels(16);

    // Create the window with the specified title, width, and height
    // Purpose: To create the game window
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!window) {
        std::cerr << RED_TEXT << "Window creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Window created successfully." << RESET_TEXT << std::endl;

    // Create the renderer for the window
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << RED_TEXT << "Renderer creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Renderer created successfully." << RESET_TEXT << std::endl;

    // Load the font for text rendering
    font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        std::cerr << RED_TEXT << "Failed to load font: " << TTF_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Font loaded successfully." << RESET_TEXT << std::endl;

    // Load and play the background music
    if (!loadBackgroundMusic(BACKGROUND_MUSIC_PATH)) {
        std::cerr << RED_TEXT << "Failed to load background music." << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Background music loaded and playing." << RESET_TEXT << std::endl;

    // Set the window icon for the game
    SDL_Surface* icon = IMG_Load(ICON_PATH);
    if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
        // std::cout << GREEN_TEXT << "Icon loaded successfully." << RESET_TEXT << std::endl;
    } else {
        std::cerr << RED_TEXT << "Icon loading failed: " << SDL_GetError() << RESET_TEXT << std::endl;
    }

    // Load the custom cursor image for the game
    SDL_Surface* cursorSurface = IMG_Load(CURSOR_PATH);
    if (!cursorSurface) {
        std::cerr << RED_TEXT << "Cursor image loading failed: " << IMG_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Cursor image loaded successfully." << RESET_TEXT << std::endl;

    // Create the cursor from the surface
    SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);

     // Free the surface after creating the cursor
    SDL_FreeSurface(cursorSurface);

    // Check if the cursor was created successfully
    if (!cursor) {
        std::cerr << RED_TEXT << "Cursor creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Cursor created successfully." << RESET_TEXT << std::endl;

    // Set the custom cursor as the active cursor
    SDL_SetCursor(cursor);

    // Load button images for the game
    backButtonTexture = IMG_LoadTexture(renderer, BUTTON_HOME_PATH);
    nextButtonTexture = IMG_LoadTexture(renderer, BUTTON_NEXT_PATH);
    aboutButtonTexture = IMG_LoadTexture(renderer, BUTTON_ABOUT_PATH);
    tutorialButtonTexture = IMG_LoadTexture(renderer, BUTTON_TUTORIAL_PATH);
    settingsButtonTexture = IMG_LoadTexture(renderer, BUTTON_SETTINGS_PATH);
    userInfoButtonTexture = IMG_LoadTexture(renderer, BUTTON_USER_INFO_PATH);
    leaderboardButtonTexture = IMG_LoadTexture(renderer, BUTTON_LEADERBOARD_PATH);
    // musicToggleButtonTexture = IMG_LoadTexture(renderer, BUTTON_MUSIC_PATH);
    // soundToggleButtonTexture = IMG_LoadTexture(renderer, BUTTON_SOUND_PATH);
    // pvpButtonTexture = IMG_LoadTexture(renderer, BUTTON_PVP_PATH);
    // pveButtonTexture = IMG_LoadTexture(renderer, BUTTON_PVE_PATH);
    
    // Check if the button images were loaded successfully
    // TODO: !pvpButtonTexture || !pveButtonTexture ||
    // TODO: !musicToggleButtonTexture || !soundToggleButtonTexture ||
    if (!aboutButtonTexture || 
        !backButtonTexture  ||
        !nextButtonTexture  ||
        !userInfoButtonTexture || 
        !tutorialButtonTexture ||
        !settingsButtonTexture || 
        !leaderboardButtonTexture) {
        std::cerr << RED_TEXT << "Failed to load button images: " << IMG_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Button images loaded successfully." << RESET_TEXT << std::endl;

    // Set the game state to running.
    isRunning = true;
    std::cout << GREEN_TEXT << "GameEngine initialized successfully." << RESET_TEXT << std::endl;
    
    return true;
}

// Function to check if a button is clicked
bool isButtonClicked(int x, int y, int buttonX, int buttonY, int buttonWidth = SMALL_BUTTON_WIDTH, int buttonHeight = SMALL_BUTTON_HEIGHT) {
    return x >= buttonX && x <= buttonX + buttonWidth && y >= buttonY && y <= buttonY + buttonHeight;
}

void GameEngine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Handle text input events
        handleTextInput(event);

        // Handle events based on the event type
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (currentState == START_SCREEN) {
                    // Check if the PvP button is clicked.
                    if (isButtonClicked(x, y, PVP_BUTTON_X, PVP_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT)) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = PVP_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: PvP screen" << RESET_TEXT << std::endl;
                    }
                    
                    // Check if the PvE button is clicked.
                    else if (isButtonClicked(x, y, PVE_BUTTON_X, PVE_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT)) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = PVE_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: PvE screen" << RESET_TEXT << std::endl;
                    }
                    
                    // Check if the User Info button is clicked.
                    else if (isButtonClicked(x, y, START_X, START_Y)) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = USER_INFO_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: User Info screen" << RESET_TEXT << std::endl;
                    }
                    
                    // Check if the Tutorial button is clicked.
                    else if (isButtonClicked(x, y, START_X, START_Y + SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING)) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = TUTORIAL_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: Tutorial screen" << RESET_TEXT << std::endl;
                    }
                    
                    // Check if the About button is clicked.
                    else if (isButtonClicked(x, y, START_X, START_Y + 2 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING))) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = ABOUT_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: About screen" << RESET_TEXT << std::endl;
                    }
                    
                    // Check if the Settings button is clicked.
                    else if (isButtonClicked(x, y, START_X, START_Y + 3 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING))) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = SETTINGS_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: Settings screen" << RESET_TEXT << std::endl;
                    }
                    
                    // Check if the Leaderboard button is clicked.
                    else if (isButtonClicked(x, y, START_X, START_Y + 4 * (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING))) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = LEADERBOARD_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: Leaderboard screen" << RESET_TEXT << std::endl;
                    }

                    const std::vector<std::string>& usernames = lobby.getUsernames();
                    int windowWidth, windowHeight;
                    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
                    int startY = windowHeight - 30 * usernames.size() - 10; // 10 pixels padding from the bottom

                    for (size_t i = 0; i < usernames.size(); ++i) {
                        int textWidth, textHeight;
                        TTF_SizeText(font, usernames[i].c_str(), &textWidth, &textHeight);
                        int deleteButtonWidth, deleteButtonHeight;
                        TTF_SizeText(font, "x", &deleteButtonWidth, &deleteButtonHeight);
                        int startX = windowWidth - textWidth - deleteButtonWidth - 30; // 10 pixels padding from the right and between username and 'x'

                        SDL_Rect deleteButtonRect = {startX + textWidth + 10, startY, deleteButtonWidth, deleteButtonHeight};
                        if (x >= deleteButtonRect.x && x <= deleteButtonRect.x + deleteButtonRect.w &&
                            y >= deleteButtonRect.y && y <= deleteButtonRect.y + deleteButtonRect.h) {
                            lobby.removeUsername(usernames[i]);
                            break;
                        }

                        startY += 30; // Move down for the next username
                    }
                
                } else if (currentState == PVP_SCREEN || 
                           currentState == PVE_SCREEN || 
                           currentState == ABOUT_SCREEN || 
                           currentState == SETTINGS_SCREEN  || 
                           currentState == TUTORIAL_SCREEN  || 
                           currentState == USER_INFO_SCREEN ||
                           currentState == LEADERBOARD_SCREEN) {
                    // Check if the home button is clicked.
                    if (isButtonClicked(x, y, START_X, START_X)) {
                        playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                        currentState = START_SCREEN;
                        std::cout << BLUE_TEXT << "Current state: Start screen" << RESET_TEXT << std::endl;
                    }
                }

                if (currentState == TUTORIAL_SCREEN) {
                    handleNextButtonClickTutorial(x, y);
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                }
                if (currentState == PVP_SCREEN) {
                    handleNextButtonClickPvP(x, y);
                    playButtonClickSound(BUTTON_CLICK_SOUND_PATH);
                }
                // Check if the card is clicked in the PvP screen
                // if (currentState == PVP_SCREEN) {
                //     for (int i = 0; i < 5; ++i) {
                //         if (x >= cardRects[i].x && x <= cardRects[i].x + cardRects[i].w &&
                //             y >= cardRects[i].y && y <= cardRects[i].y + cardRects[i].h) {
                //             cardRevealed[i] = !cardRevealed[i];
                //         }
                //     }
                // }
                break;
            default:
                break;
        }
    }
}

// Function to update the game state
void GameEngine::update() {
    // Update game state
}

// Function to render the game objects
void GameEngine::render() {
    if (currentState == START_SCREEN) {
        renderStartScreen(this);
    } else if (currentState == PVP_SCREEN) {
        renderPvPScreen(this);
    } else if (currentState == PVE_SCREEN) {
        renderPvEScreen(this);
    } else if (currentState == ABOUT_SCREEN) {
        renderAboutScreen(this);
    } else if (currentState == TUTORIAL_SCREEN) {
        renderTutorialScreen(this);
    } else if (currentState == SETTINGS_SCREEN) {
        renderSettingsScreen(this);
    } else if (currentState == USER_INFO_SCREEN) {
        renderUserInfoScreen(this);
    } else if (currentState == LEADERBOARD_SCREEN) {
        renderLeaderboardScreen(this);
    } else {
        // Handle unexpected state
        SDL_Log("Unexpected game state: %d", currentState);
    }

    SDL_RenderPresent(renderer);
}

// Function to clean up the game engine
void GameEngine::clean() {
    // std::cout << YELLOW_TEXT << "Cleaning up GameEngine..." << RESET_TEXT << std::endl;
    // Free the font
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    // Free the background music
    if (backgroundMusic) {
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }

    // Quit SDL_mixer
    Mix_CloseAudio();

    // Free the renderer
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    // Free the window
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

    // if (musicToggleButtonTexture) {
    //     SDL_DestroyTexture(musicToggleButtonTexture);
    //     musicToggleButtonTexture = nullptr;
    // }

    // if (soundToggleButtonTexture) {
    //     SDL_DestroyTexture(soundToggleButtonTexture);
    //     soundToggleButtonTexture = nullptr;
    // }

    // Quit SDL and SDL_TTF
    TTF_Quit();
    SDL_Quit();

    std::cout << GREEN_TEXT << "GameEngine cleaned." << RESET_TEXT << std::endl;
}

// Function to load the background music
// Purpose: Easy to maintain and implement further features
bool GameEngine::loadBackgroundMusic(const char* filePath) {
    backgroundMusic = Mix_LoadMUS(filePath);
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Background music loaded successfully." << RESET_TEXT << std::endl;

    Mix_VolumeMusic(BACKGROUND_MUSIC_VOLUME);

    // Play the background music on loop
    Mix_PlayMusic(backgroundMusic, -1);

    return true;
}

bool GameEngine::playButtonClickSound(const char* filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath);
    if (!sound) {
        std::cerr << RED_TEXT << "Failed to load sound effect: " << Mix_GetError() << RESET_TEXT << std::endl;
        return false;
    }
    // std::cout << GREEN_TEXT << "Sound effect loaded successfully." << RESET_TEXT << std::endl;

    int channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1) {
        std::cerr << "Failed to play sound effect: " << Mix_GetError() << std::endl;
        Mix_FreeChunk(sound);
        return false;
    }
    // std::cout << GREEN_TEXT << "Sound effect played successfully." << RESET_TEXT << std::endl;

    return true;
}

void GameEngine::renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color, bool centered = false) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, color);
    if (textSurface) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        if (textTexture) {
            int textWidth, textHeight;
            TTF_SizeText(font, text, &textWidth, &textHeight);
            SDL_Rect textRect = {centered ? x - textWidth / 2 : x, y, textWidth, textHeight};
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        } else {
            std::cerr << RED_TEXT << "Text texture creation failed: " << RESET_TEXT << SDL_GetError() << std::endl;
        }
    } else {
        std::cerr << RED_TEXT << "Text surface creation failed: " << RESET_TEXT << TTF_GetError() << std::endl;
    }
    // std::cout << GREEN_TEXT << "Text rendered successfully." << RESET_TEXT << std::endl; 
}

// Function to check if the mouse is hovering over a button
bool GameEngine::isMouseHovering(int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    return mouseX >= buttonX && mouseX <= buttonX + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
}

// Function to handle button hover effect
void GameEngine::handleButtonHover(SDL_Texture* buttonTexture, int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight) {
    if (isMouseHovering(mouseX, mouseY, buttonX, buttonY, buttonWidth, buttonHeight)) {
        SDL_SetTextureColorMod(buttonTexture, 200, 200, 200);
    } else {
        SDL_SetTextureColorMod(buttonTexture, 255, 255, 255);
    }
}

// Function to render 5 cards
void GameEngine::renderCards(const char* cardFiles[5], bool allowClick, int fadeCards, bool allFaceDown) {
    SDL_Renderer* renderer = getRenderer();

    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(getWindow(), &windowWidth, &windowHeight);

    // Calculate the horizontal spacing between cards
    int totalCardWidth = 5 * CARD_WIDTH;
    int spacing = (windowWidth - totalCardWidth) / 6; // 6 spaces between 5 cards
    
    // Calculate the vertical position of the cards
    int startY = (windowHeight - CARD_HEIGHT) / 2;

    // Load the back of the card image
    SDL_Surface* backSurface = IMG_Load(BACK_CARD_PATH);
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
            if (((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT)) ||
                ((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && isButtonClicked(mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT)) ||
                ((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && isButtonClicked(mouseX, mouseY, PVP_BUTTON_X, PVP_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT)) ||
                ((mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) && isButtonClicked(mouseX, mouseY, PVE_BUTTON_X, PVE_BUTTON_Y, BIG_BUTTON_WIDTH, BIG_BUTTON_HEIGHT))) {
                for (int i = 0; i < 5; ++i) {
                    getCardRevealed()[i] = false;
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
        if (allowClick && (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))) {
            if (!mouseButtonPressed && 
                mouseX >= cardRect.x && mouseX <= cardRect.x + cardRect.w &&
                mouseY >= cardRect.y && mouseY <= cardRect.y + cardRect.h) {
                getCardRevealed()[i] = !getCardRevealed()[i];
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
    SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    if (isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y)) {
        currentCardSet = (currentCardSet + 1) % 9;
    }
}

void GameEngine::handleNextButtonClickPvP(int mouseX, int mouseY) {
    std::vector<std::string> usernames = lobby.getUsernames();
    if (currentPlayer < usernames.size() - 1 && isButtonClicked(mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y)) {
        currentPlayer += 1;
    }
}

// void GameEngine::toggleBackgroundMusic() {
//     if (Mix_PausedMusic()) {
//         Mix_ResumeMusic();
//     } else {
//         Mix_PauseMusic();
//     }
// }

// void GameEngine::toggleSoundEffects() {
//     if (Mix_Volume(-1, -1) == 0) {
//         Mix_Volume(-1, MIX_MAX_VOLUME);
//     } else {
//         Mix_Volume(-1, 0);
//     }
// }