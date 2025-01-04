#include "../header/District.h"

District::District(const string& name_, const vector<District*>& neighbors_) {
    name = name_;
    neighbors = neighbors_;
}

District::District(const string& name_) {
    name = name_;
}

void District::newRestaurant(const vector<string>& arguments,const vector<map<string, string>>& menu) {
    addRestaurant(new Restaurant(arguments[0], this, menu, arguments[3], arguments[4], arguments[5]));
}

void District::print() {
    cout << name << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER;
    printNeighbors();
    cout << '\n';
}

void District::printNeighbors() {
    for (size_t i = 0; i < neighbors.size(); i++) {
        cout << neighbors[i]->getName();
        if (i != neighbors.size() - 1)
            cout << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER;
    }
}

void District::showRestaurants() {
    for (auto restaurant: restaurants) {
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

void District::showRestaurantDetail(const string &restaurantName) {
    for (auto restaurant : restaurants) {
        if (restaurantName == restaurant->getName()) {
            restaurant->detailedPrint();
            return;
        }
    }
    throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

District* District::checkIfItHasRestaurant(const string& restaurantName) {
    for (auto restaurant : restaurants) {
        if (restaurant->getName() == restaurantName) {
            return this;
        }
    }
    return nullptr;
}

void District::reserveTableInRestaurant(const string &restaurantName, const string &tableId, const string &startTime,
                                        const string &endTime, const string &foods, User* user) {
    Restaurant* restaurant = findRestaurantByName(restaurantName);
    if (restaurant == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    restaurant->reserveTable(tableId, startTime, endTime, foods, user);
}

Restaurant* District::findRestaurantByName(const string &restaurantName) {
    for (auto restaurant : restaurants) {
        if (restaurantName == restaurant->getName())
            return restaurant;
    }
    return nullptr;
}
