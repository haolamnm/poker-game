/*
FILE: include/core/Login.h

DESCRIPTION: Header file for the login class. This file contains
the class declaration for the login of the game. In the class, we
handle the login of the game, create a new player, and show the
status of the login.

AUTHOR: Le Nguyen Anh Tri.
*/

#ifndef LOGIN_H
#define LOGIN_H

#include "Storage.h"
#include <string>
#include <fstream>

enum StatusCode {
    OK,
    INCORRECT_PASSWORD,
    NEW_ACCOUNT
};

class Login {
private:
    Storage storage;
    std::string status;
public:
    StatusCode statusCode = OK;

    bool login(const std::string& username, const std::string& password);
    bool createNewPlayer(const std::string& username, const std::string& password);
    const std::string show();
};

#endif