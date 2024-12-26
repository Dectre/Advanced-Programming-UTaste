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
    User(const string& u,const string& p);
    string getUsername() { return username; }
    string getPassword() { return password; }
    District* getLocation() { return location; }
    void setLocation(District* district) { location = district; }
    void addReserve(Reserve* newReserve) { reserves.push_back(newReserve); }
    bool checkConflicts(const string& startTime, const string& endTime);

    void showReserves();
    void showReservesForRestaurant(const string& restaurantName);
    vector<Reserve*> getSpecificRestaurantReserves(const string& restaurantName);
    void showReserve(const string& restaurantName, const string& reserveID);
    Reserve* findReserve(const string& restaurantName, const string& reserveID);

    void deleteReserve(const string& restaurantName, const string& reserveID);
};


#endif //UTASTE_USER_H
