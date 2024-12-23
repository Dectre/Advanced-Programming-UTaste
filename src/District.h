#ifndef UTASTE_DISTRICT_H
#define UTASTE_DISTRICT_H

#include "Restaurant.h"

class District {
private:
    string name;
    vector<District*> neighbors;
    vector<Restaurant> restaurants;
public:
    District(string name_, vector<District*> neighbors_, vector<Restaurant> restaurants_);
    District(string name_);
};


#endif //UTASTE_DISTRICT_H
