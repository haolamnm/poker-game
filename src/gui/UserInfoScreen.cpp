// Description: Implementation of the UserInfoScreen rendering and input handling functions

#include "gui/UserInfoScreen.h"

// Global variables for storing input text
std::string usernameInput = "";
std::string passwordInput = "";
bool isUsernameActive = true;

void handleTextInput(SDL_Event& event) {
    if (event.type == SDL_TEXTINPUT) {
        if (isUsernameActive) {
            usernameInput += event.text.text;
        } else {
            passwordInput += event.text.text;
        }
    } else if (event.type == SDL_KEYDOWN) {
        // Backspace key to delete character
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            if (isUsernameActive && !usernameInput.empty()) {
                usernameInput.pop_back();
            } else if (!isUsernameActive && !passwordInput.empty()) {
                passwordInput.pop_back();
            }
        } 
        // Tab key to switch between input fields
        else if (event.key.keysym.sym == SDLK_TAB) {
            isUsernameActive = !isUsernameActive;
        } 
        // Enter key to submit the form
        else if (event.key.keysym.sym == SDLK_RETURN) {
            // cout << "Username: " << usernameInput << endl;
            // cout << "Password: " << passwordInput << endl;
            Login login;
            if (login.login(usernameInput, passwordInput)) {
                std::cout << GREEN_TEXT << login.show() << RESET_TEXT << std::endl;
                // GameEngine::lobby.assignUsername(usernameInput);
                // GameEngine::lobby.showUsernames();
            } else if (login.statusCode == NEW_ACCOUNT) {
                std::cout << login.show() << std::endl;
                char choice;
                std::cout << "Do you want to create a new account? (y/n): ";
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    login.createNewPlayer(usernameInput, passwordInput);
                    std::cout << login.show() << std::endl;
                }
            } else {
                std::cout << login.show() << std::endl;
            }
            
            usernameInput.clear();
            passwordInput.clear();
        }
    }
}

// Function to render the User Info screen
void renderUserInfoScreen(GameEngine* game) {
    SDL_Renderer* renderer = game->getRenderer();
    SDL_Texture* backButtonTexture = game->getBackButtonTexture();
    SDL_Window* window = game->getWindow();
    TTF_Font* font = game->getFont();

    // Load a smaller font for the input fields
    TTF_Font* inputFont = TTF_OpenFont("assets/fonts/SVN-Vintage.otf", 32);
    if (!inputFont) {
        std::cerr << "Failed to load input font: " << TTF_GetError() << std::endl;
        return;
    }

    // Get the window size
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Render the User Info screen background
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Render the back button
    SDL_Rect backButtonRect = {20, 20, 50, 50};
    SDL_RenderCopy(renderer, backButtonTexture, NULL, &backButtonRect);

    // Define fixed-size input field dimensions
    const int inputFieldWidth = 300;
    const int inputFieldHeight = 40;

    // Render username input text
    SDL_Color textColor = {255, 255, 255};
    SDL_Rect usernameInputRect = {windowWidth / 2 - inputFieldWidth / 2, 200, inputFieldWidth, inputFieldHeight};
    SDL_RenderSetClipRect(renderer, &usernameInputRect); // Set clipping rectangle
    if (!usernameInput.empty()) {
        SDL_Surface* usernameInputSurface = TTF_RenderText_Solid(inputFont, usernameInput.c_str(), textColor);
        if (usernameInputSurface) {
            SDL_Texture* usernameInputTexture = SDL_CreateTextureFromSurface(renderer, usernameInputSurface);
            SDL_FreeSurface(usernameInputSurface);

            if (usernameInputTexture) {
                int usernameInputWidth, usernameInputHeight;
                TTF_SizeText(inputFont, usernameInput.c_str(), &usernameInputWidth, &usernameInputHeight);
                SDL_Rect usernameTextRect = {usernameInputRect.x + 5, usernameInputRect.y + (inputFieldHeight - usernameInputHeight) / 2, usernameInputWidth, usernameInputHeight}; // Position and size of the text
                SDL_RenderCopy(renderer, usernameInputTexture, NULL, &usernameTextRect);
                SDL_DestroyTexture(usernameInputTexture);
            } else {
                std::cerr << RED_TEXT << "Username input texture creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
            }
        } else {
            std::cerr << RED_TEXT << "Username input surface creation failed: " << TTF_GetError() << RESET_TEXT << std::endl;
        }
    }
    SDL_RenderSetClipRect(renderer, NULL); // Clear clipping rectangle

    // Draw border around username input field
    SDL_Rect usernameBorderRect = {usernameInputRect.x - 1, usernameInputRect.y - 1, inputFieldWidth + 2, inputFieldHeight + 2};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &usernameBorderRect);

    // Render password input text (masked with asterisks)
    std::string maskedPassword(passwordInput.length(), '*');
    SDL_Rect passwordInputRect = {windowWidth / 2 - inputFieldWidth / 2, 300, inputFieldWidth, inputFieldHeight};
    SDL_RenderSetClipRect(renderer, &passwordInputRect); // Set clipping rectangle
    if (!maskedPassword.empty()) {
        SDL_Surface* passwordInputSurface = TTF_RenderText_Solid(inputFont, maskedPassword.c_str(), textColor);
        if (passwordInputSurface) {
            SDL_Texture* passwordInputTexture = SDL_CreateTextureFromSurface(renderer, passwordInputSurface);
            SDL_FreeSurface(passwordInputSurface);

            if (passwordInputTexture) {
                int passwordInputWidth, passwordInputHeight;
                TTF_SizeText(inputFont, maskedPassword.c_str(), &passwordInputWidth, &passwordInputHeight);
                SDL_Rect passwordTextRect = {passwordInputRect.x + 5, passwordInputRect.y + (inputFieldHeight - passwordInputHeight) / 2, passwordInputWidth, passwordInputHeight}; // Position and size of the text
                SDL_RenderCopy(renderer, passwordInputTexture, NULL, &passwordTextRect);
                SDL_DestroyTexture(passwordInputTexture);
            } else {
                std::cerr << RED_TEXT << "Password input texture creation failed: " << SDL_GetError() << RESET_TEXT << std::endl;
            }
        } else {
            std::cerr << RED_TEXT << "Password input surface creation failed: " << TTF_GetError() << RESET_TEXT << std::endl;
        }
    }
    SDL_RenderSetClipRect(renderer, NULL); // Clear clipping rectangle

    // Draw border around password input field
    SDL_Rect passwordBorderRect = {passwordInputRect.x - 1, passwordInputRect.y - 1, inputFieldWidth + 2, inputFieldHeight + 2};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for the border
    SDL_RenderDrawRect(renderer, &passwordBorderRect);

    // Close the input font
    TTF_CloseFont(inputFont);
}