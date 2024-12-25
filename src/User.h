#ifndef UTASTE_USER_H
#define UTASTE_USER_H

#include "Manual.h"

class District;
class Reserve;

class User {
private:
    string username;
    string password;
    District* location;
    vector<Reserve*> reserves;
public:
    User(string u, string p);
    string getUsername() { return username; }
    string getPassword() { return password; }
    District* getLocation() { return location; }
    vector<Reserve*> getReserves() { return reserves; }
    void setLocation(District* district) { location = district; }
};


#endif //UTASTE_USER_H
