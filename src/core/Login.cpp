/*
FILE: src/core/Login.cpp

DESCRIPTION: Implementation file for the login class. This file
contains the implementation of the member functions of the login
class. Handle things like login, create a new player, and show the
status of the login.

NOTE: This file interacts with the storage class to verify the
username and password of the player.

AUTHOR: Le Nguyen Anh Tri.
*/

#include "core/Login.h"

bool Login::login(const std::string& username, const std::string& password) {
    if (storage.usernameExists(username)) {
        if (storage.verify(username, password)) {
            status = "Login successful!";
            statusCode = OK;
            return true;
        } else {
            status = "Incorrect password!";
            statusCode = INCORRECT_PASSWORD;
            return false;
        }
    } else {
        status = "Username does not exist!, Do you want to create a new account? (y/n)";
        statusCode = NEW_ACCOUNT;
        return false;
    }
}

bool Login::createNewPlayer(const std::string& username, const std::string& password) {
    if (storage.usernameExists(username)) {
        status = "Username already exists!";
        return false;
    } else {
        unsigned int winningStrategy[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        storage.createNewPlayer(username, password, 0, 200, 0.0, 0, "None", winningStrategy);
        status = "New account created!";
        return true;
    }
}

const std::string Login::show() {
    return status;
}