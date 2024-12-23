#include "Restaurant.h"

Restaurant::Restaurant(std::string name_, District *location_, vector<Food> Menu_, int openingTime_, int closingTime_,
                       int numOfTables) {
    name = name_;
    location = location_;
    Menu = Menu_;
    openingTime = openingTime_;
    closingTime = closingTime_;
    for (int i = 0; i < numOfTables ; i++) {
        tables.push_back(Table(i));
    }
}