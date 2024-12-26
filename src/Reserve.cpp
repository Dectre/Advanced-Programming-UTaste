#include "Reserve.h"
#include "Food.h"
#include "Table.h"
#include "Restaurant.h"

Reserve::Reserve(const string& s, const string& e, Table* t) {
    startTime = stoi(s);
    endTime = stoi(e);
    table = t;
    initID();
}

Reserve::Reserve(const string& s, const string& e, Table* t, const vector<string>& o) {
    startTime = stoi(s);
    endTime = stoi(e);
    table = t;
    initFoods(o);
    initID();
    calculatePrice();
}

void Reserve::timePrint() {
    cout << IN_DELIMITER << startTime << TO_DELIMITER << endTime << OUT_DELIMITER;
}

bool Reserve::checkConflict(const string &sTime, const string &eTime) {
    if (stoi(sTime) >= endTime || stoi(eTime) <= startTime)
        return false;
    return true;
}
void Reserve::initFoods(vector<string> foodsList) {
    for (auto foodName : foodsList)
        order.push_back(table->getRestaurant()->getFoodByName(foodName));
}

void Reserve::initID() {
    Restaurant* restaurant = table->getRestaurant();
    int ReserveID = restaurant->getLastReserveID() + 1;
    id = ReserveID;
}

void Reserve::print() {
    cout << RESERVE_ID_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER << id << endl;
    cout << TABLE_OUTPUT << WORD_SEPERATOR_DELIMITER << table->getId() << WORD_SEPERATOR_DELIMITER
    << FOR_OUTPUT << WORD_SEPERATOR_DELIMITER << startTime  << WORD_SEPERATOR_DELIMITER
    << TO_OUTPUT << WORD_SEPERATOR_DELIMITER << endTime << WORD_SEPERATOR_DELIMITER
            << IN_OUTPUT << WORD_SEPERATOR_DELIMITER  << table->getRestaurant()->getName() << endl;
    cout << PRICE_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER << price << endl;
}

void Reserve::calculatePrice() {
    for (auto food : order)
        price += food->getPrice();
}

void Reserve::shortPrint() {
    cout << id << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER
    << table->getRestaurant()->getName() << WORD_SEPERATOR_DELIMITER
    << table->getId() << WORD_SEPERATOR_DELIMITER
    << startTime << TO_DELIMITER << endTime << WORD_SEPERATOR_DELIMITER;
    printOrders();
    cout << endl;
}

void Reserve::printOrders() {
    unordered_map<string, int> foodCounts;
    for (auto food : order)
        foodCounts[food->getName()]++;

    vector<pair<string, int>> sortedFoods(foodCounts.begin(), foodCounts.end());

    sort(sortedFoods.begin(), sortedFoods.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    });

    for (const auto& [foodName, count] : sortedFoods)
        cout << foodName << IN_DELIMITER << count << OUT_DELIMITER << WORD_SEPERATOR_DELIMITER;
}

bool Reserve::checkRestaurant(const string &restaurantName) {
    if (restaurantName == table->getRestaurant()->getName())
        return true;
    return false;
}




