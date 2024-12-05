// Description: Implementation of the renderPvPScreen function

#include "gui/PvPScreen.h"

bool isDealtPvP = false;
bool isSavedPvP = false;
bool isDrawButtonClicked = false;
bool drawButtonFlag = false;
bool isFoldButtonClicked = false;
bool isCallButtonClicked = false;
bool callButtonFlag = false;
bool isRaiseButtonClicked = false;
int currentCardIndex = -1;

// Function to render the PvP screen
void renderPvPScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    TTF_Font* mediumFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 40);
    TTF_Font* smallFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 18);
    TTF_Font* roundFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 34);
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    SDL_Texture* foldButtonTexture = game->getFoldButtonTexture();
    SDL_Texture* callButtonTexture = game->getCallButtonTexture();
    SDL_Texture* drawButtonTexture = game->getdrawButtonTexture();
    SDL_Texture* raiseButtonTexture = game->getRaiseButtonTexture();

    // Get the mouse coordinates
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Render the PvP screen background
    SDL_SetRenderDrawColor(renderer, 9, 70, 27, 255);
    SDL_RenderClear(renderer);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Check if there are at least 2 players in the lobby
    const std::vector<std::string>& usernames = lobby.getUsernames();
    if (usernames.size() < 2) {
        // Render a message indicating that more players are needed
        SDL_Color redColor = {255, 0, 0, 255}; // Red color
        TTF_Font* msgFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 28);
        game->renderText(renderer, msgFont, "Need at least 2 players to play PvP", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, redColor, true);
        TTF_CloseFont(msgFont);
    } 
    
    else if (game->currentPlayer <= usernames.size()) {
        // Render the current game mode at the bottom of the screen
        SDL_Color textColor = {255, 255, 255, 255};
        std::string gameModeText = "Game Mode: " + std::string(game->getCurrentGameModeString());
        game->renderText(renderer, smallFont, gameModeText.c_str(), WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50, textColor, true);
        if (game->currentGameMode == GameEngine::BASIC_POKER) {
            static Gameplay gameplay;
            int numberOfCards = 5;

            if (!isDealtPvP) {
                isDealtPvP = true;
                gameplay.init(usernames, 0);
                gameplay.resetDeck(); // Reset the deck for a new game
                gameplay.dealCards(numberOfCards);
            }
            const char* cardSets[usernames.size()][5];
            // Array of card file paths
            for (int i = 0; i < gameplay.numberOfPlayers; i++) {
                for (int j = 0; j < numberOfCards; j++) {
                    Card& currentCard = gameplay.players[i].hand.cards[j];
                    cardSets[i][j] = CARD_FILES[currentCard.rank * 4 + currentCard.suit].c_str();
                }
            }
            // for (int i = 0; i < gameplay.numberOfPlayers; i++) {
            //     std::cout << "Player's id: " << gameplay.players[i].id << " (" << gameplay.players[i].username << ")" << '\n';
            //     gameplay.players[i].hand.show();
            //     std::cout << "Hand strength: " << gameplay.players[i].hand.handStrength << " (" << gameplay.players[i].hand.handName << ")" << '\n';
            //     std::cout << '\n';
            // }
            // if (gameplay.winner != -1) {
            //     std::cout << "Winner: " << gameplay.players[gameplay.winner].username << '\n';
            // } else {
            //     std::cout << "It's a tie!" << '\n';
            // }

            // Save player data after dealing cards and determining the winner
            if (!isSavedPvP) {
                isSavedPvP = true;
                for (int i = 0; i < gameplay.numberOfPlayers; i++) {
                    gameplay.players[gameplay.players[i].id].chipsBetted += defaultChipBetted;
                    gameplay.totalChipsBetted += gameplay.players[gameplay.players[i].id].chipsBetted;
                }
                gameplay.whoWins();
                for (Player& player : gameplay.players) {
                    gameplay.savePlayerData(player);
                }
                gameplay.saveAllPlayerData();
            }

            // Render the 5 cards
            SDL_Color textColor = {255, 255, 255, 255}; // White color
            if (game->currentPlayer < usernames.size()) {
                // Render the current player's chips
                // std::string chipText = "Chips: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chips);
                // game->renderText(renderer, smallFont, chipText.c_str(), 780, 100, textColor, false, true);
                // Render the "username" text
                game->renderText(renderer, font, gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str(), WINDOW_WIDTH / 2, 50, textColor, true);
                game->renderCards(cardSets[gameplay.players[game->currentPlayer].id], true, 0, true);
                SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                bool allCardsFaceUp = true;
                for (int i = 0; i < 5; i++) {
                    if (!game->getCardRevealed()[i]) {
                        allCardsFaceUp = false;
                        break;
                    }
                }
                if (allCardsFaceUp) {
                    game->renderText(renderer, mediumFont, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
                }
                SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
                game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
            } else if (game->currentPlayer == usernames.size()) {
                if (gameplay.winner != -1) {
                    std::string winner = gameplay.players[gameplay.winner].username;
                    game->renderText(renderer, font, "Winner:", WINDOW_WIDTH / 2, 50, textColor, true);
                    game->renderText(renderer, font, winner.c_str(), WINDOW_WIDTH / 2, 125, textColor, true);
                    game->renderCards(cardSets[gameplay.winner], false, 0, false);
                    // Winner hand stregth
                    game->renderText(renderer, font, gameplay.players[gameplay.winner].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
                } else {
                    game->renderText(renderer, font, "It's a tie!", WINDOW_WIDTH / 2, 50, textColor, true);
                }
            }
        } else if (game->currentGameMode == GameEngine::DRAW_POKER) {
            static Gameplay gameplay;
            int numberOfCards = 5;

            if (!isDealtPvP) {
                isDealtPvP = true;
                gameplay.init(usernames, 0);
                gameplay.resetDeck(); // Reset the deck for a new game
                gameplay.dealCards(numberOfCards);
            }
            const char* cardSets[usernames.size()][5];
            // Array of card file paths
            for (int i = 0; i < gameplay.numberOfPlayers; i++) {
                for (int j = 0; j < numberOfCards; j++) {
                    Card& currentCard = gameplay.players[i].hand.cards[j];
                    cardSets[i][j] = CARD_FILES[currentCard.rank * 4 + currentCard.suit].c_str();
                }
            }
            for (int i = 0; i < gameplay.numberOfPlayers; i++) {
                gameplay.players[i].hand.evaluateHand();
            }

            if (game->currentDrawPokerRound == GameEngine::DRAW_ROUND) {
                if (drawButtonFlag == false && isDrawButtonClicked == true) {
                    isDrawButtonClicked = false;
                    drawButtonFlag = true;
                    gameplay.drawPlayerCards(gameplay.players[gameplay.players[game->currentPlayer].id]);
                }
                if (currentCardIndex != -1) {
                    int selectedCards = gameplay.countSelectedCards(gameplay.players[game->currentPlayer].id);
                    if (selectedCards < 3 || gameplay.players[game->currentPlayer].hand.removedCards[currentCardIndex]) {
                        gameplay.players[gameplay.players[game->currentPlayer].id].hand.removedCards[currentCardIndex] = 
                        !gameplay.players[gameplay.players[game->currentPlayer].id].hand.removedCards[currentCardIndex];
                    }
                    currentCardIndex = -1;
                }
                // Outline for the selected card
                SDL_Rect cardRect = {0, 0, 0, 0};
                for (int i = 0; i < 5; i++) {
                    if (gameplay.players[gameplay.players[game->currentPlayer].id].hand.removedCards[i]) {
                        cardRect = game->getCardRects()[i];
                        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); // Cyan color
                        SDL_Rect outlineRect = {cardRect.x - 6, cardRect.y - 6, cardRect.w + 12, cardRect.h + 12}; // Make the outline thicker
                        SDL_RenderDrawRect(renderer, &outlineRect);
                        outlineRect = {cardRect.x - 5, cardRect.y - 5, cardRect.w + 10, cardRect.h + 10}; // Draw another outline for thickness
                        SDL_RenderDrawRect(renderer, &outlineRect);
                    }
                }
            }
            if ((game->currentDrawPokerRound == GameEngine::FIRST_BETTING_ROUND || game->currentDrawPokerRound == GameEngine::SECOND_BETTING_ROUND)) {
                if (isRaiseButtonClicked == true) {
                    isRaiseButtonClicked = false;
                    gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted += 10;
                    gameplay.highestBet = std::max(gameplay.highestBet, gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted);
                    gameplay.totalChipsBetted += 10;

                    std::cout << "Raise button clicked" << '\n';
                }
                if (isFoldButtonClicked == true) {
                    isFoldButtonClicked = false;
                    std::cout << "Fold button clicked" << '\n';
                }
                if (callButtonFlag == false && isCallButtonClicked == true) {
                    isCallButtonClicked = false;
                    callButtonFlag = true;
                    if (gameplay.players[gameplay.players[game->currentPlayer].id].chips >= gameplay.highestBet) {
                        gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted = gameplay.highestBet;
                        gameplay.totalChipsBetted += gameplay.highestBet;
                    } else {
                        // render not enough money to call

                    }
                    std::cout << "Call button clicked" << '\n';
                }
            }

            if (!isSavedPvP) {
                isSavedPvP = true;
                for (Player& player : gameplay.players) {
                    gameplay.savePlayerData(player);
                }
                gameplay.saveAllPlayerData();
            }

            // Render the 5 cards
            SDL_Color textColor = {255, 255, 255, 255}; // White color
            if (game->currentPlayer < usernames.size()) {
                // Render the current player's chips
                std::string betText = "Bet: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted);
                game->renderText(renderer, smallFont, betText.c_str(), 780, 100, textColor, false, true);
                std::string totalBetText = "Total bet: " + std::to_string(gameplay.totalChipsBetted);
                game->renderText(renderer, smallFont, totalBetText.c_str(), 780, 125, textColor, false, true);

                // Render round text                
                SDL_Color textColor = {255, 255, 255, 255}; // White color
                game->renderText(renderer, roundFont, game->getCurrentRoundString(), WINDOW_WIDTH / 2, 50, textColor, true);

                // Render the "username" text
                game->renderText(renderer, mediumFont, gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str(), WINDOW_WIDTH / 2, 100, textColor, true);
                game->renderCards(cardSets[gameplay.players[game->currentPlayer].id], true, 0, true);
                SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                bool allCardsFaceUp = true;
                for (int i = 0; i < 5; i++) {
                    if (!game->getCardRevealed()[i]) {
                        allCardsFaceUp = false;
                        break;
                    }
                }
                if (allCardsFaceUp) {
                    std::string chipText = "Chips: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chips -
                                                                  gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted);
                    game->renderText(renderer, smallFont, chipText.c_str(), 780, 75, textColor, false, true);
                    game->renderText(renderer, mediumFont, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
                }
                SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
                game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render fold button
                SDL_Rect foldButtonRect = {FOLD_BUTTON_X, FOLD_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, foldButtonTexture, NULL, &foldButtonRect);
                game->handleButtonHover(foldButtonTexture, mouseX, mouseY, FOLD_BUTTON_X, FOLD_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render call button
                SDL_Rect callButtonRect = {CALL_BUTTON_X, CALL_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, callButtonTexture, NULL, &callButtonRect);
                game->handleButtonHover(callButtonTexture, mouseX, mouseY, CALL_BUTTON_X, CALL_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render raise button
                SDL_Rect raiseButtonRect = {RAISE_BUTTON_X, RAISE_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, raiseButtonTexture, NULL, &raiseButtonRect);
                game->handleButtonHover(raiseButtonTexture, mouseX, mouseY, RAISE_BUTTON_X, RAISE_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render reset button
                SDL_Rect drawButtonRect = {DRAW_BUTTON_X, DRAW_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, drawButtonTexture, NULL, &drawButtonRect);
                game->handleButtonHover(drawButtonTexture, mouseX, mouseY, DRAW_BUTTON_X, DRAW_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
            }
            else if (game->currentDrawPokerRound == GameEngine::SHOWDOWN_ROUND) {
                gameplay.whoWins();
                if (gameplay.winner != -1) {
                    std::string winner = gameplay.players[gameplay.winner].username;
                    game->renderText(renderer, font, "Winner:", WINDOW_WIDTH / 2, 50, textColor, true);
                    game->renderText(renderer, font, winner.c_str(), WINDOW_WIDTH / 2, 125, textColor, true);
                    game->renderCards(cardSets[gameplay.winner], false, 0, false);
                    // Winner hand stregth
                    game->renderText(renderer, mediumFont, gameplay.players[gameplay.winner].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
                } else {
                    game->renderText(renderer, font, "It's a tie!", WINDOW_WIDTH / 2, 50, textColor, true);
                }
            }
            else if (game->currentPlayer == usernames.size()) {
                game->currentDrawPokerRound = (GameEngine::drawPokerRound) ((int) game->currentDrawPokerRound + 1);
                game->currentPlayer = 0;
            } 
        }
    }
    TTF_CloseFont(mediumFont);
    TTF_CloseFont(smallFont);
    TTF_CloseFont(roundFont);
}