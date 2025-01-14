#ifndef UTASTE_USER_H
#define UTASTE_USER_H

#include "Manual.h"
#include "Reserve.h"


class District;

class User {
private:
    string username;
    string password;
    District* location = nullptr;
    vector<Reserve*> reserves;
    int budget = 1000000000;
public:
    User(const string& u,const string& p);
    string getUsername() { return username; }
    string getPassword() { return password; }
    District* getLocation() { return location; }
    void setLocation(District* district) { location = district; }
    void addReserve(Reserve* newReserve);
    bool checkConflicts(const string& startTime, const string& endTime);

    void showReserves();
    void showReservesForRestaurant(const string& restaurantName);
    vector<Reserve*> getSpecificRestaurantReserves(const string& restaurantName);
    vector<Reserve*> getReserves() { return reserves; }
    Reserve* showReserve(const string& restaurantName, const string& reserveID);
    Reserve* findReserve(const string& restaurantName, const string& reserveID);

    void deleteReserve(const string& restaurantName, const string& reserveID);

    void increaseBudget(const string& amount);
    void showBudget() const { cout << budget << endl; }
    int getBudget() const { return budget; }
};

#endif //UTASTE_USER_H
