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
    vector<District*> handleNeighbors(const vector<string>& neighborsList);
    District* findDistrictByName(const string& name);
    bool usernameExists(const string & username);
    void checkIfLoggedIn();
    District* getUserLocation() { return currentUser-> getLocation(); }
    void checkLocationExists(District* location);
    void initializeTraversal(District* startDistrict, std::set<District*>& visited, std::queue<District*>& toVisit);
    void processDistrictsForRestaurants(std::set<District*>& visited, std::queue<District*>& toVisit);
    bool processSpecificDistrictsForRestaurants(const std::string& dishName, std::set<District*>& visited, std::queue<District*>& toVisit);

public:
    Taste();
    ~Taste();

    void signUp(const string& username, const string& password);
    void login(const string& username, const string& password);
    void logout();

    void handleDistrict(const string& name, const vector<string>& neighbors);
    void handleRestaurant(vector<string> arguments, vector<map<string, string>> foods);

    void sortDistricts();

    void showDistricts();
    void showSpecificDistrict(const string& districtName);

    void setUserLocation(const string& districtName);

    void showRestaurants();
    void showSpecificRestaurants(const string& foodName);

    void districtsShowRestaurantDetail(const string& restaurantName);
};


#endif //TASTE_TASTE_H
