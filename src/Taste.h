#ifndef TASTE_TASTE_H
#define TASTE_TASTE_H

#include "Manual.h"
#include "User.h"
#include "District.h"

class Taste {
private:
    vector<District*> districts;
    vector<User*> users;
    User* currentUser = nullptr;
    vector<District*> handleNeighbors(vector<string> neighborsList);
    District* findDistrictByName(string name);
public:
    Taste();
    ~Taste();
    bool usernameExists(const string & username);
    void signUp(const string& username, const string& password);
    void login(const string& username, const string& password);
    void logout();

    void handleDistrict(string name, vector<string> neighbors);
    void handleRestaurant(vector<string> arguments, vector<map<string, string>> foods);
};


#endif //TASTE_TASTE_H
