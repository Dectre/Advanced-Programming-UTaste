#ifndef UTASTE_USER_H
#define UTASTE_USER_H

#include "Manual.h"
#include "Reserve.h"


class District;
class Reserve;

class User {
private:
    string username;
    string password;
    District* location = nullptr;
    vector<Reserve*> reserves;
public:
    User(string u, string p);
    string getUsername() { return username; }
    string getPassword() { return password; }
    District* getLocation() { return location; }
    vector<Reserve*> getReserves() { return reserves; }
    void setLocation(District* district) { location = district; }
    void addReserve(Reserve* newReserve) { reserves.push_back(newReserve); }
    bool checkConflicts(const string& startTime, const string& endTime);

    void showReserves();
    void showReservesForRestaurant(const string& restaurantName);
    vector<Reserve*> getSpecificRestaurantReserves(const string& restaurantName);
};


#endif //UTASTE_USER_H
