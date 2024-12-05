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
    // std::string statusCode;
    StatusCode statusCode = OK;

    bool login(const std::string& username, const std::string& password);
    bool createNewPlayer(const std::string& username, const std::string& password);
    const std::string show();
};

#endif // LOGIN_H