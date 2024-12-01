#include "core/Login.h"

/* ------------------Login------------------ */
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
        storage.createNewPlayer(username, password, 0, 200, 0.0, 0, "Not have favorite strategy yet", winningStrategy);
        status = "New account created!";
        return true;
    }
}

const std::string Login::show() {
    return status;
}
/* ------------------End of Login------------------ */