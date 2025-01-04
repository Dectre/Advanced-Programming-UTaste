#include "../header/Table.h"
#include "../header/Reserve.h"
#include "../header/Restaurant.h"


Table::Table(const int& id_, Restaurant* restaurant_) {
    id = id_;
    restaurant = restaurant_;
}

void Table::print() {
    cout << id << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER;
    reservesTimePrint();
}

void Table::reservesTimePrint() {
    vector<Reserve*> sortedReserves(reserves.begin(), reserves.end());
    sort(sortedReserves.begin(), sortedReserves.end(), [](Reserve* a, Reserve* b) {
        return a->getStartTime() < b->getStartTime();
    });
    for (size_t i = 0; i < sortedReserves.size(); i++) {
        sortedReserves[i]->timePrint();
        if (i != sortedReserves.size() - 1)
            cout << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER;
    }
}

void Table::reserve(const string &startTime, const string &endTime, const string &foods, User* user) {
    if (isConflicted(startTime, endTime)) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    Reserve* newReserve = nullptr;
    try {
        if (!foods.empty()) {
            vector<string> foodsList = handleFoods(foods);
            newReserve = new Reserve(startTime, endTime, this, foodsList, user);
        } else
            newReserve = new Reserve(startTime, endTime, this, user);
        reserves.push_back(newReserve);
    } catch (const invalid_argument&) {
        delete newReserve;
        throw;
    }
}


bool Table::isConflicted(const string &startTime, const string &endTime) {
    for (auto reserve : reserves)
        if (reserve->checkConflict(startTime, endTime)) return true;
    return false;
}

vector<string> Table::handleFoods(const string &foods) {
    vector<string> foodsList = splitStringBy(foods, SEPARATOR_DELIMITER);
    for (const auto& foodName : foodsList) {
        if (!restaurant->hasFood(foodName))
            throw invalid_argument(NON_EXISTENCE_RESPONSE);
    }
    return foodsList;
}

bool Table::checkReserve(const string &reserveID) {
    for (auto reserve : reserves)
        if (reserve->getID() == safeStoi(reserveID)) return true;
    return false;
}

void Table::removeReserve(Reserve* targetReserve) {
    auto it = remove(reserves.begin(), reserves.end(), targetReserve);
    if (it != reserves.end()) {
        delete *it;
        reserves.erase(it, reserves.end());
    }
}
