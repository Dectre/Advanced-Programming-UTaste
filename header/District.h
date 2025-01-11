#ifndef UTASTE_DISTRICT_H
#define UTASTE_DISTRICT_H

#include "Restaurant.h"

class User;

class District {
private:
    string name;
    vector<District*> neighbors;
    vector<Restaurant*> restaurants;
public:
    District(const string& name_, const vector<District*>& neighbors_);
    District(const string& name_);
    District();

    vector<District*> getNeighbors() { return neighbors; }
    void addNeighbor(District* neighbor) { neighbors.push_back(neighbor); }
    void addRestaurant(Restaurant* restaurant) { restaurants.push_back(restaurant); }
    void sortRestaurants();
    void newRestaurant(const vector<string>& arguments,const vector<map<string, string>>& menu);

    string getName() { return name; }

    void print();
    void printNeighbors();

    void showRestaurants();
    bool showRestaurantsByFood(const string& foodName);

    Restaurant* showRestaurantDetail(const string& restaurantName);

    District* checkIfItHasRestaurant(const string& restaurantName);
    void reserveTableInRestaurant(const string &restaurantName, const string &tableId, const string &startTime,
                                  const string &endTime, const string &foods, User* user);
    Restaurant* findRestaurantByName(const string& restaurantName);

};

#endif //UTASTE_DISTRICT_H
