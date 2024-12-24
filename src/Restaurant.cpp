#include "Restaurant.h"

Restaurant::Restaurant(string name_, District* location_, vector<map<string, string>> menu_,
                       string openingTime_, string closingTime_, string numOfTables) {
    name = name_;
    location = location_;
    handleMenu(menu_);
    openingTime = stoi(openingTime_);
    closingTime = stoi(closingTime_);
    for (int i = 0; i < stoi(numOfTables) ; i++) {
        tables.push_back(Table(i));
    }
}

void Restaurant::handleMenu(vector<map<std::string, std::string>> menu_) {
    for (auto food : menu_)
        menu.push_back(new Food(food[NAME_KEY], stoi(food[PRICE_KEY])));
}