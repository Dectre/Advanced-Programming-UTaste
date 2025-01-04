#include "../header/User.h"
#include "../header/Restaurant.h"

User::User(const string& u,const string& p) {
    username = u;
    password = p;
}

bool User::checkConflicts(const string &startTime, const string &endTime) {
    for (auto reserve : reserves)
        if (reserve->checkConflict(startTime, endTime)) return true;
    return false;
}

void User::showReserves() {
    if (reserves.empty()) throw invalid_argument(EMPTY_RESPONSE);
    for (auto reserve : reserves)
        reserve->shortPrint();
}

void User::showReservesForRestaurant(const string& restaurantName) {
    vector<Reserve*> reservesToShow = getSpecificRestaurantReserves(restaurantName);
    if (reservesToShow.empty()) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    for (auto reserve : reservesToShow)
        reserve->shortPrint();
}

vector<Reserve *> User::getSpecificRestaurantReserves(const string &restaurantName) {
    vector<Reserve*> reservesToShow;
    for (auto reserve : reserves)
        if (reserve->checkRestaurant(restaurantName)) reservesToShow.push_back(reserve);
    return reservesToShow;
}

void User::showReserve(const string &restaurantName, const string &reserveID) {
    Reserve* reserve = findReserve(restaurantName, reserveID);
    if (reserve == nullptr) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    reserve->shortPrint();
}

Reserve* User::findReserve(const string &restaurantName, const string &reserveID) {
    for (auto reserve : reserves) {
        if (reserve->find(restaurantName, reserveID) != nullptr)
            return reserve;
    }
    return nullptr;
}

void User::deleteReserve(const string &restaurantName, const string &reserveID) {
    Reserve* targetReserve = findReserve(restaurantName, reserveID);
    if (targetReserve == nullptr) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    reserves.erase(remove(reserves.begin(), reserves.end(), targetReserve), reserves.end());
    budget += returnRate * targetReserve->getPriceAfterDiscount();
    targetReserve->removeReserveFromTable();
}

void User::increaseBudget(const string& amount) {
    int tempAmount = safeStoi(amount);
    if (tempAmount < 0) throw invalid_argument(BAD_REQUEST_RESPONSE);
    budget += tempAmount;
    cout << SUCCESSFUL_RESPONSE << endl;
}

void User::addReserve(Reserve* newReserve) {
    reserves.push_back(newReserve);
    budget -= newReserve->getPriceAfterDiscount();
}

