#ifndef TASTE_TASTE_H
#define TASTE_TASTE_H

#include "Manual.h"
#include "User.h"
#include "District.h"

class Taste {
private:
    vector<District> districts;
    vector<User*> users;
    User* currentUser = nullptr;
public:
    Taste();
    ~Taste();
    bool usernameExists(const string & username);
    void signUp(const string& username, const string& password);
    void login(const string& username, const string& password);
    void logout();
};


#endif //TASTE_TASTE_H
