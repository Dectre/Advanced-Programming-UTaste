#include "Table.h"
#include "Reserve.h"
#include "Restaurant.h"

Table::Table(int id_, Restaurant* restaurant_) {
    id = id_;
    restaurant = move(restaurant_);
}

void Table::print() {
    cout << id << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER;
    reservesTimePrint();
}

void Table::reservesTimePrint() {
    for (size_t i = 0; i < reserves.size(); i++) {
        reserves[i]->timePrint();
        if (i != reserves.size() - 1)
            cout << SEPERATOR_DELIMITER << WORD_SEPERATOR_DELIMITER;
    }
}

void Table::reserve(const std::string &startTime, const std::string &endTime, const std::string &foods) {
    if (isConflicted(startTime, endTime)) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    if (!foods.empty()){
        vector<string> foodsList = handleFoods(foods);
        reserves.push_back(new Reserve(startTime, endTime, this, foodsList));
    }
    else
        reserves.push_back(new Reserve(startTime, endTime, this));
}

bool Table::isConflicted(const string &startTime, const string &endTime) {
    for (auto reserve : reserves)
        if (reserve->checkConflict(startTime, endTime)) return true;
    return false;
}

vector<string> Table::handleFoods(const string &foods) {
    vector<string> foodsList = splitStringBy(foods, SEPERATOR_DELIMITER);
    for (auto foodName : foodsList) {
        if (!restaurant->hasFood(foodName))
            throw invalid_argument(NON_EXISTENCE_RESPONSE);
    }
    return foodsList;
}

int Table::findLastReserveId() {
    if (!reserves.empty())
        return reserves[reserves.size() - 1]->getReserveID() + 1;
    return 1;
}