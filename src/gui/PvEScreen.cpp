/*
FILE: src/gui/PvEScreen.cpp

Description: Implementation file for the Player vs Environment
(PvE). This file is part of the GUI subsystem and is used to
render the PvE screen. This file contains the function definition
for rendering the PvE screen.

NOTE: PvE only availables in the BASIC POKER game mode.

AUTHOR: Lam Chi Hao & Le Nguyen Anh Tri.
*/

#include "gui/PvEScreen.h"

// Define the isDealt variable
bool isDealtPvE = false;
bool isSavedPvE = false;

// Function to render the PvE screen
void renderPvEScreen(GameEngine* game) {
    TTF_Font* bigFontVintage = game->getBigFontVintage();
    TTF_Font* mediumFontVintage = game->getMediumFontVintage();
    TTF_Font* smallFontVintage = game->getSmallFontVintage();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Render the PvE screen background
    SDL_SetRenderDrawColor(renderer, 9, 70, 27, 255);
    SDL_RenderClear(renderer);

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Handle back button hover
    game->handleButtonHover(backButtonTexture, mouseX, mouseY, START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

    // Render the back button
    SDL_Rect backButtonRect = {START_X, START_X, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);
    
    // Check if there is at least 1 player in the lobby
    const std::vector<std::string>& usernames = lobby.getUsernames();
    if (usernames.empty()) {
        // Render a message indicating that at least 1 player is needed
        SDL_Color textColor = {255, 0, 0, 255}; // Red color
        game->renderText(renderer, mediumFontVintage, "Need at least 1 player to play PvE", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, textColor, true);
    } else {
        static Gameplay gameplay;
        int numberOfCards = 5;

        if (!isDealtPvE) {
            isDealtPvE = true;
            gameplay.entryFee = defaultChipBetted;
            gameplay.init(usernames, 5);
            gameplay.resetDeck(); // Reset the deck for a new game
            gameplay.dealCards(numberOfCards);
        }
        const char*** cardSets = new const char**[gameplay.numberOfPlayers];
        for (size_t i = 0; i < gameplay.numberOfPlayers; i++) {
            cardSets[i] = new const char*[5];
        }
        // Array of card file paths
        for (int i = 0; i < gameplay.numberOfPlayers; i++) {
            for (int j = 0; j < numberOfCards; j++) {
                Card& currentCard = gameplay.players[i].hand.cards[j];
                cardSets[i][j] = CARD_FILES[currentCard.rank * 4 + currentCard.suit].c_str();
            }
        }

        if (game->currentPlayer < gameplay.numberOfPlayers) {
            // Render the "username" text
            game->renderText(renderer, bigFontVintage, gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str(), WINDOW_WIDTH / 2, 50, textColor, true);
            game->renderCards(cardSets[gameplay.players[game->currentPlayer].id], true, 0, true);
            SDL_Rect nextButtonRect = {NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
            bool allCardsFaceUp = true;
            for (int i = 0; i < 5; i++) {
                if (!game->getCardRevealed()[i]) {
                    allCardsFaceUp = false;
                    break;
                }
            }

            std::string entryFeeText = "Entry fee: " + std::to_string(gameplay.entryFee);
            game->renderText(renderer, smallFontVintage, entryFeeText.c_str(), 780, 50, textColor, false, true);
            std::string betText = "Bet: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted);
            game->renderText(renderer, smallFontVintage, betText.c_str(), 780, 100, textColor, false, true);
            std::string totalBetText = "Total bet: " + std::to_string(gameplay.totalChipsBetted);
            game->renderText(renderer, smallFontVintage, totalBetText.c_str(), 780, 125, textColor, false, true);

            if (allCardsFaceUp) {
                std::string chipText = "Chips: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chips -
                                                                  gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted);
                game->renderText(renderer, smallFontVintage, chipText.c_str(), 780, 75, textColor, false, true);
                gameplay.players[gameplay.players[game->currentPlayer].id].hand.evaluateHand();
                game->renderText(renderer, mediumFontVintage, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
            }
            SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
            game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
        } else if (game->currentPlayer == static_cast<int>(gameplay.numberOfPlayers)) {
            // Save player data after dealing cards and determining the winner
            if (!isSavedPvE) {
                isSavedPvE = true;
                gameplay.whoWins();
                for (Player& player : gameplay.players) {
                    if (player.isBot == false) {
                        gameplay.savePlayerData(player);
                    }
                }
                gameplay.saveAllPlayerData();
            }
            if (gameplay.winner != -1) {
                std::string winner = gameplay.players[gameplay.winner].username;
                game->renderText(renderer, bigFontVintage, "Winner:", WINDOW_WIDTH / 2, 50, textColor, true);
                game->renderText(renderer, bigFontVintage, winner.c_str(), WINDOW_WIDTH / 2, 125, textColor, true);
                game->renderCards(cardSets[gameplay.winner], false, 0, false);
                // Winner hand stregth
                game->renderText(renderer, mediumFontVintage, gameplay.players[gameplay.winner].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
            } else {
                game->renderText(renderer, bigFontVintage, "It's a tie!", WINDOW_WIDTH / 2, 50, textColor, true);
            }
        }
        for (size_t i = 0; i < usernames.size(); ++i) {
            delete[] cardSets[i];
        }
        delete[] cardSets;
    }
}