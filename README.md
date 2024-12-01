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
    class Card {
        - Suits suit
        - Ranks rank
        - ushort value
        + suitToString() string
        + rankToString() string
    }

    class Deck {
        - Card[] cards
        - int remainCards
        + setup() void
        + shuffle() void
        + dealCards(int) void
    }

    class Hand {
        - Card[] cards
        - int numberOfOnHandCards
        - int handStrength
        - string handName
        + show() void
        + sortCards() void
    }

    class Strength {
        + isStraightFlush(Hand) bool
        + isFourOfAKind(Hand) bool
        + isFullHouse(Hand) bool
        + isFlush(Hand) bool
        + isStraight(Hand) bool
        + isThreeOfAKind(Hand) bool
        + isTwoPair(Hand) bool
        + isOnePair(Hand) bool
        + evaluateHand(Hand) int
        + compareHands(Hand, Hand) int
    }

    class Player {
        - string username
        - int id
        - Hand hand
        - uint gamesPlayed
        - uint chips
        - float winrate
        - ushort rank
        - string favoriteStrategy
        - uint[] winningStrategy
        + show() void
    }

    class Storage {
        - map<string, Player> storage
        - string fileName
        + Storage(string)
        + split(string, char) vector<string>
        + usernameExists(string) bool
        + verify(string, string) bool
        + createNewPlayer(string, string, uint, uint, float, ushort, string, uint[]) void
        + assignPlayerData(string, uint, uint, float, ushort, string, uint[]) void
        + savePlayerData(string) void
        + getPlayerData(string) vector<string>
        + getAllUsernames() vector<string>
        + hashPassword(string) string
    }

    class Leaderboard {
        - vector<Player> players
        - Storage playerStorage
        + loadPlayerData() void
        + updateLeaderboard() void
        + saveLeaderboard(string) void
        + showLeaderboard() void
    }

    class Gameplay {
        - Deck deck
        - Storage storage
        - Leaderboard leaderboard
        - int numberOfPlayers
        - int winner
        - vector<Player> players
        + init(int, vector<string>) void
        + dealCards(int) void
        + whoWins() void
        + savePlayerData(Player) void
        + saveAllPlayerData() void
        + showLeaderboard() void
    }

    class Login {
        - Storage storage
        - string status
        - string statusCode
        + login(string, string) bool
        + createNewPlayer(string, string) bool
        + show() string
    }

    class Lobby {
        - Login login
        - Gameplay gameplay
        - vector<string> usernames
        + start() void
        + showMenu() void
        + handleLogin() void
        + handleGame() void
        + handleLeaderboard() void
    }

    Login --> Storage: uses

    Gameplay --> Player: manages
    Gameplay --> Deck: uses
    Gameplay --> Leaderboard: uses
    Gameplay --> Storage: uses
    Leaderboard --> Player: ranks
    Lobby --> Login: uses
    Lobby --> Gameplay: uses
    Player --> Login: has
    Player --> Hand: has
    Deck --> Card: contains
    Hand --> Card: contains
    Strength --> Hand: uses
```