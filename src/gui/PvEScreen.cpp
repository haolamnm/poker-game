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
    TTF_Font* font = game->getFont();
    TTF_Font* mediumFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 40);
    TTF_Font* smallFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 18);
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    SDL_Color textColor = {255, 255, 255, 255};
    
    // Get window dimensions

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
        SDL_Color redColor = {255, 0, 0, 255}; // Red color
        TTF_Font* msgFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 28);
        game->renderText(renderer, msgFont, "Need at least 1 player to play PvE", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, redColor, true);
        TTF_CloseFont(msgFont);
    } else {
        static Gameplay gameplay;
        int numberOfCards = 5;

        if (!isDealtPvE) {
            isDealtPvE = true;
            gameplay.init(usernames, 5); // Initialize with 5 bots
            gameplay.resetDeck(); // Reset the deck for a new game
            gameplay.dealCards(numberOfCards);
        }
        const char* cardSets[gameplay.numberOfPlayers][5];
        // Array of card file paths
        for (int i = 0; i < gameplay.numberOfPlayers; i++) {
            for (int j = 0; j < numberOfCards; j++) {
                Card& currentCard = gameplay.players[i].hand.cards[j];
                cardSets[i][j] = CARD_FILES[currentCard.rank * 4 + currentCard.suit].c_str();
            }
        }

        // Save player data after dealing cards and determining the winner
        if (!isSavedPvE) {
            isSavedPvE = true;
            if (gameplay.players[gameplay.players[game->currentPlayer].id].username.substr(0, 3) != "Bot") {
                gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted += defaultChipBetted;
                gameplay.totalChipsBetted += gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted;
            }
            gameplay.whoWins();
            for (Player& player : gameplay.players) {
                gameplay.savePlayerData(player);
            }
            gameplay.saveAllPlayerData();
        }

        // Render the 5 cards
        if (game->currentPlayer < gameplay.numberOfPlayers) {
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
                std::string chipText = "Chips: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chips -
                                                              gameplay.players[gameplay.players[game->currentPlayer].id].chipsBetted);
                gameplay.players[gameplay.players[game->currentPlayer].id].hand.evaluateHand();
                game->renderText(renderer, smallFont, chipText.c_str(), 780, 75, textColor, false, true);
                game->renderText(renderer, font, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), WINDOW_WIDTH / 2, 450, textColor, true);
            }
            SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
            game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
        } else if (game->currentPlayer == gameplay.numberOfPlayers) {
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
    }
    TTF_CloseFont(mediumFont);
    TTF_CloseFont(smallFont);
}