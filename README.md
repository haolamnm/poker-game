# CSC10012 - Poker Project

## This project uses

- [SDL2](https://www.libsdl.org/) library for graphical user interface.
- [C++](https://cplusplus.com/) programming language for developing the game logic.
- [Makefile](https://medium.com/@ayogun/what-is-makefile-and-make-how-do-we-use-it-3828f2ee8cb) a special file for running all necessary files.

## How to use?

### Some Makefile commands

- `all` &#8594; compiles whole program.
- `run` &#8594; runs the compiled program (should be used after `all`).
- `clean` &#8594; cleans all unnecessary files when done.

<!-- &#8594; is -> -->

### Mac/Linux user

- `make all`
- `make run`
- `make clean`

### Windows user

- `mingw32-make -f Makefile all`
- `mingw32-make -f Makefile run`
- `mingw32-make -f Makefile clean`

---

## Class Diagram

```mermaid
classDiagram
    class GameEngine {
        +bool init(const char* title, int width, int height, bool fullscreen)
        +void handleEvents()
        +void update()
        +void render()
        +void clean()
        +bool loadBackgroundMusic(const char* filePath)
        +bool playButtonClickSound(const char* filePath)
        +void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color, bool centered, bool rightAligned)
        +void renderCards(const char* cardFiles[5], bool allowClick, int fadeCards, bool allFaceDown)
        +void handleButtonHover(SDL_Texture* buttonTexture, int mouseX, int mouseY, int buttonX, int buttonY, int buttonWidth, int buttonHeight)
        +SDL_Texture* getBackButtonTexture() const
        +SDL_Texture* getNextButtonTexture() const
        +SDL_Texture* getPrevButtonTexture() const
        +SDL_Texture* getFoldButtonTexture() const
        +SDL_Texture* getCallButtonTexture() const
        +SDL_Texture* getRaiseButtonTexture() const
        +SDL_Texture* getdrawButtonTexture() const
        +TTF_Font* getBigFontVintage()
        +TTF_Font* getMediumFontVintage()
        +TTF_Font* getSmallFontVintage()
        +SDL_Window* getWindow()
        +SDL_Renderer* getRenderer()
        +SDL_Rect* getCardRects()
        +bool* getCardRevealed()
        +void handleNextButtonClickPvP(int mouseX, int mouseY)
        +void handleDrawButtonClickPvP(int mouseX, int mouseY)
        +void handleFoldButtonClickPvP(int mouseX, int mouseY)
        +void handleCallButtonClickPvP(int mouseX, int mouseY)
        +void handleRaiseButtonClickPvP(int mouseX, int mouseY)
        +void resetPvPGame()
        +void resetPvEGame()
        +int currentCardSet
        +int currentPlayer
        +string currentGameMode
        +string currentDrawPokerRound
    }

    class Gameplay {
        +void init(const std::vector<std::string>& usernames, int numberOfBots)
        +void dealCards(int numberOfCards)
        +void drawPlayerCards(Player& player)
        +void whoWins()
        +void savePlayerData(Player& player)
        +void saveAllPlayerData()
        +std::vector<std::vector<std::string>> showLeaderboard()
        +void resetDeck()
        +int countSelectedCards(int id)
        -Deck deck
        -Storage storage
        -Leaderboard leaderboard
        -int numberOfPlayers
        -int winner
        -unsigned int entryFee
        -unsigned int totalEntryFee
        -unsigned int totalChipsBetted
        -unsigned int highestBet
        -std::vector<Player> players
    }

    class Player {
        +void show()
        -std::string username
        -int id
        -Hand hand
        -bool isBot
        -bool isFolded
        -unsigned int chipsBetted
        -unsigned int gamesPlayed
        -unsigned int chips
        -float winrate
        -unsigned short rank
        -std::string favoriteStrategy
        -unsigned int winningStrategy[9]
    }

    class Lobby {
        +void assignUsername(const std::string& username)
        +void removeUsername(const std::string& username)
        +std::vector<std::string> getUsernames()
        +std::vector<std::vector<std::string>> handleLeaderboard()
        -Login login
        -Gameplay game
        -std::vector<std::string> usernames
    }

    class Hand {
        +void show()
        +void sortCards()
        +void evaluateHand()
        -int numberOfOnHandCards
        -int handStrength
        -std::string handName
        -Card cards[5]
        -Card sortedCards[5]
        -bool removedCards[5]
        -std::vector<Card> strengthCards
    }

    class Card {
        +std::string suitToString()
        +std::string rankToString()
        -Suits suit
        -Ranks rank
        -unsigned short value
    }

    class Deck {
        +void setup()
        +void shuffle()
        +void reset()
        -Card cards[52]
        -int remainCards
    }

    class Storage {
        +bool usernameExists(const std::string& username)
        +bool verify(const std::string& username, const std::string& password)
        +void createNewPlayer(const std::string& username, const std::string& password, unsigned int gamesPlayed, unsigned int chips, float winrate, unsigned short rank, const std::string& favoriteStrategy, unsigned int winningStrategy[])
        +void assignPlayerData(const std::string& username, unsigned int gamesPlayed, unsigned int chips, float winrate, unsigned short rank, const std::string& favoriteStrategy, unsigned int winningStrategy[])
        +void savePlayerData(const std::string& username)
        +std::vector<std::string> split(const std::string& str, char delimiter)
        -std::map<std::string, Player> storage
        -std::string fileName
    }

    class Leaderboard {
        +void loadPlayerData()
        +void updateLeaderboard()
        +void saveLeaderboard(const std::string& fileName)
        +void showLeaderboard()
        -std::vector<Player> players
    }

    class Login {
        +bool login(const std::string& username, const std::string& password)
        +bool createNewPlayer(const std::string& username, const std::string& password)
        +const std::string show()
        -Storage storage
        -std::string status
        -StatusCode statusCode
    }

    GameEngine --> Gameplay : uses
    GameEngine --> Player : manages
    GameEngine --> Lobby : uses
    GameEngine --> Hand : uses
    GameEngine --> Card : uses
    GameEngine --> Deck : uses
    GameEngine --> Storage : uses
    GameEngine --> Leaderboard : uses
    GameEngine --> Login : uses
    Gameplay --> Player : manages
    Gameplay --> Deck : uses
    Gameplay --> Storage : uses
    Gameplay --> Leaderboard : uses
    Lobby --> Login : uses
    Lobby --> Gameplay : uses
    Player --> Hand : has
    Hand --> Card : contains
    Deck --> Card : contains
    Storage --> Player : stores
    Leaderboard --> Player : ranks
    Login --> Storage : uses
```