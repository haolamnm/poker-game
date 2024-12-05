// Description: Implementation of the renderPvPScreen function

#include "gui/PvPScreen.h"

bool isDealtPvP = false;
bool isSavedPvP = false;
bool isDrawButtonClicked = false;
int currentCardIndex = -1;

enum drawPokerRound {
    FIRST_BETTING_ROUND = 1,
    DRAW_ROUND,
    SECOND_BETTING_ROUND,
    SHOWDOWN_ROUND
};

drawPokerRound currentDrawPokerRound = FIRST_BETTING_ROUND;

// Function to render the PvP screen
void renderPvPScreen(GameEngine* game) {
    TTF_Font* font = game->getFont();
    TTF_Font* mediumFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 24);
    TTF_Font* smallFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 18);
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Texture* nextButtonTexture = game->getNextButtonTexture();
    SDL_Texture* foldButtonTexture = game->getFoldButtonTexture();
    SDL_Texture* callButtonTexture = game->getCallButtonTexture();
    SDL_Texture* drawButtonTexture = game->getdrawButtonTexture();
    SDL_Texture* raiseButtonTexture = game->getRaiseButtonTexture();

    // Get the window dimensions
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

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
        SDL_Color textColor = {255, 0, 0, 255}; // Red color
        TTF_Font* msgFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 28);
        game->renderText(renderer, msgFont, "Need at least 2 players to play PvP", windowWidth / 2, windowHeight / 2, textColor, true);
        TTF_CloseFont(msgFont);
    } 
    
    else if (game->currentPlayer <= usernames.size()) {
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
            gameplay.whoWins();
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
                game->renderText(renderer, font, gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str(), windowWidth / 2, 50, textColor, true);
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
                    game->renderText(renderer, mediumFont, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
                }
                SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
                game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
            } else if (game->currentPlayer == usernames.size()) {
                if (gameplay.winner != -1) {
                    std::string winner = gameplay.players[gameplay.winner].username;
                    game->renderText(renderer, font, "Winner:", windowWidth / 2, 50, textColor, true);
                    game->renderText(renderer, font, winner.c_str(), windowWidth / 2, 125, textColor, true);
                    game->renderCards(cardSets[gameplay.winner], false, 0, false);
                    // Winner hand stregth
                    game->renderText(renderer, font, gameplay.players[gameplay.winner].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
                } else {
                    game->renderText(renderer, font, "It's a tie!", windowWidth / 2, 50, textColor, true);
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
                std::cout << "Player's id: " << gameplay.players[i].id << " (" << gameplay.players[i].username << ")" << '\n';
                gameplay.players[i].hand.evaluateHand();
                gameplay.players[i].hand.show();
                std::cout << "Hand strength: " << gameplay.players[i].hand.handStrength << " (" << gameplay.players[i].hand.handName << ")" << '\n';
                std::cout << '\n';
            }
            if (gameplay.winner != -1) {
                std::cout << "Winner: " << gameplay.players[gameplay.winner].username << '\n';
            } else {
                std::cout << "It's a tie!" << '\n';
            }
            // gameplay.whoWins();

            if (currentCardIndex != -1) {
                int selectedCards = gameplay.countSelectedCards(gameplay.players[game->currentPlayer].id);
                if (selectedCards < 3 || gameplay.players[game->currentPlayer].hand.removedCards[currentCardIndex]) {
                    gameplay.players[gameplay.players[game->currentPlayer].id].hand.removedCards[currentCardIndex] = 
                    !gameplay.players[gameplay.players[game->currentPlayer].id].hand.removedCards[currentCardIndex];
                }
                currentCardIndex = -1;
            }
            if (isDrawButtonClicked == true) {
                isDrawButtonClicked = false;
                gameplay.drawPlayerCards(gameplay.players[gameplay.players[game->currentPlayer].id]);
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
                std::string chipText = "Chips: " + std::to_string(gameplay.players[gameplay.players[game->currentPlayer].id].chips);
                game->renderText(renderer, smallFont, chipText.c_str(), 780, 100, textColor, false, true);
                // Render round text
                std::string roundText = "Round: " + std::to_string(currentDrawPokerRound);
                game->renderText(renderer, font, roundText.c_str(), windowWidth / 2, 50, textColor, true);
                // Render the "username" text
                game->renderText(renderer, font, gameplay.players[gameplay.players[game->currentPlayer].id].username.c_str(), windowWidth / 2, 100, textColor, true);
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
                    game->renderText(renderer, mediumFont, gameplay.players[gameplay.players[game->currentPlayer].id].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
                }
                SDL_RenderCopy(renderer, nextButtonTexture, NULL, &nextButtonRect);
                game->handleButtonHover(nextButtonTexture, mouseX, mouseY, NEXT_BUTTON_X, NEXT_BUTTON_Y, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Calculate positions for the buttons in a 2x2 grid
                int buttonX1 = START_X;
                int buttonY1 = windowHeight - SMALL_BUTTON_HEIGHT - SMALL_BUTTON_SPACING;
                int buttonX2 = START_X + SMALL_BUTTON_WIDTH + SMALL_BUTTON_SPACING;
                int buttonY2 = windowHeight - SMALL_BUTTON_HEIGHT - SMALL_BUTTON_SPACING;
                int buttonX3 = START_X;
                int buttonY3 = windowHeight - (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING) * 2;
                int buttonX4 = START_X + SMALL_BUTTON_WIDTH + SMALL_BUTTON_SPACING;
                int buttonY4 = windowHeight - (SMALL_BUTTON_HEIGHT + SMALL_BUTTON_SPACING) * 2;

                // Render fold button
                SDL_Rect foldButtonRect = {buttonX1, buttonY1, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, foldButtonTexture, NULL, &foldButtonRect);
                game->handleButtonHover(foldButtonTexture, mouseX, mouseY, buttonX1, buttonY1, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render call button
                SDL_Rect callButtonRect = {buttonX2, buttonY2, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, callButtonTexture, NULL, &callButtonRect);
                game->handleButtonHover(callButtonTexture, mouseX, mouseY, buttonX2, buttonY2, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render raise button
                SDL_Rect raiseButtonRect = {buttonX3, buttonY3, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, raiseButtonTexture, NULL, &raiseButtonRect);
                game->handleButtonHover(raiseButtonTexture, mouseX, mouseY, buttonX3, buttonY3, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);

                // Render reset button
                SDL_Rect drawButtonRect = {buttonX4, buttonY4, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT};
                SDL_RenderCopy(renderer, drawButtonTexture, NULL, &drawButtonRect);
                game->handleButtonHover(drawButtonTexture, mouseX, mouseY, buttonX4, buttonY4, SMALL_BUTTON_WIDTH, SMALL_BUTTON_HEIGHT);
            }
            else if (currentDrawPokerRound == SHOWDOWN_ROUND) {
                gameplay.whoWins();
                if (gameplay.winner != -1) {
                    std::string winner = gameplay.players[gameplay.winner].username;
                    game->renderText(renderer, font, "Winner:", windowWidth / 2, 50, textColor, true);
                    game->renderText(renderer, font, winner.c_str(), windowWidth / 2, 125, textColor, true);
                    game->renderCards(cardSets[gameplay.winner], false, 0, false);
                    // Winner hand stregth
                    game->renderText(renderer, mediumFont, gameplay.players[gameplay.winner].hand.handName.c_str(), windowWidth / 2, 450, textColor, true);
                } else {
                    game->renderText(renderer, font, "It's a tie!", windowWidth / 2, 50, textColor, true);
                }
            }
            else if (game->currentPlayer == usernames.size()) {
                if (currentDrawPokerRound == SECOND_BETTING_ROUND) currentDrawPokerRound = SHOWDOWN_ROUND;
                else currentDrawPokerRound = (drawPokerRound) ((int) currentDrawPokerRound + 1);
                game->currentPlayer = 0;
            } 
        }
    }
    TTF_CloseFont(mediumFont);
    TTF_CloseFont(smallFont);
}