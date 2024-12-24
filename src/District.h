#ifndef UTASTE_DISTRICT_H
#define UTASTE_DISTRICT_H

#include "Restaurant.h"

class District {
private:
    string name;
    vector<District*> neighbors;
    vector<Restaurant> restaurants;
public:
    District(string name_, vector<District*> neighbors_);
    District(string name_);
    District();
    void addNeighbor(District* neighbor) { neighbors.push_back(neighbor); }
    string getName() { return name; }
};


#endif //UTASTE_DISTRICT_H
