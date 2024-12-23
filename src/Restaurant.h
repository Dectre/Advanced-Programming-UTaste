#ifndef UTASTE_RESTAURANT_H
#define UTASTE_RESTAURANT_H

#include "Food.h"
#include "Table.h"

class District;

class Restaurant {
private:
    string name;
    District* location;
    vector<Food> Menu;
    int openingTime;
    int closingTime;
    vector<Table> tables;
public:
    Restaurant(string name_, District* location_, vector<Food> Menu_,
               int openingTime_, int closingTime_, int numOfTables);
    string getName() { return name; }
    District* getLocation() { return location; }
    vector<Food> getMenu() { return Menu; }
};


#endif //UTASTE_RESTAURANT_H
