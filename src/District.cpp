#include "District.h"

District::District(string name_, vector<District*> neighbors_) {
    name = name_;
    neighbors = neighbors_;
}

District::District(string name_) {
    name = name_;
}

void District::newRestaurant(vector<string> arguments, vector<map<string, string>> menu) {
    addRestaurant(new Restaurant(arguments[0], this, menu, arguments[3], arguments[4], arguments[5]));
}

void District::print() {
    cout << name << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER;
    printNeighbors();
    cout << '\n';
}

void District::printNeighbors() {
    for (size_t i = 0; i < neighbors.size(); i++) {
        cout << neighbors[i]->getName();
        if (i != neighbors.size() - 1)
            cout << SEPERATOR_DELIMITER << WORD_SEPERATOR_DELIMITER;
    }
}

void District::showRestaurants() {
    for (auto restaurant : restaurants) {
        restaurant->shortPrint();
    }
}

bool District::showRestaurantsByFood(const string& foodName) {
    bool found = false;
    for (auto restaurant : restaurants) {
        if (restaurant->hasFood(foodName)) {
            restaurant->shortPrint();
            found = true;
        }
    }
    return found;
}
