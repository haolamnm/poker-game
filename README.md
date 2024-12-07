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
        -SDL_Window* window
        -SDL_Renderer* renderer
        -GameState currentGameState
        -GameMode currentGameMode
        -drawPokerRound currentDrawPokerRound
        +init()
        +handleEvents()
        +update()
        +render()
        +clean()
    }

    class Gameplay {
        -Deck deck
        -Storage storage
        -Leaderboard leaderboard
        +init()
        +dealCards()
        +whoWins()
        +savePlayerData()
        +showLeaderboard()
    }

    class Player {
        -std::string username
        -Hand hand
        -bool isBot
        -bool isFolded
        -unsigned int chips
        -float winrate
        -unsigned short rank
    }

    class Hand {
        -Card cards[5]
        -int handStrength
        -std::string handName
        +show()
        +sortCards()
        +evaluateHand()
    }

    class Card {
        -Suits suit
        -Ranks rank
        +suitToString()
        +rankToString()
    }

    class Deck {
        -Card cards[52]
        -int remainCards
        +setup()
        +shuffle()
        +reset()
    }

    class Storage {
        -std::map<std::string, Player> storage
        +verify()
        +createNewPlayer()
        +savePlayerData()
        +updatePlayerStorage()
    }

    class Login {
        -Storage storage
        -std::string status
        +login()
        +createNewPlayer()
    }

    class Lobby {
        -Login login
        -Gameplay game
        -std::vector<std::string> usernames
        +assignUsername()
        +removeUsername()
        +handleLeaderboard()
    }

    GameEngine --> Gameplay : uses
    GameEngine --> Lobby : uses
    Gameplay --> Player : manages
    Gameplay --> Deck : uses
    Gameplay --> Storage : uses
    Player --> Hand : has
    Hand --> Card : contains
    Deck --> Card : contains
    Storage --> Player : stores
    Login --> Storage : uses
    Lobby --> Login : uses
    Lobby --> Gameplay : uses
```
