#include "User.h"
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
    if (reserves.empty()) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    for (auto reserve : reserves)
        reserve->shortPrint();
}

void User::showReservesForRestaurant(const string& restaurantName) {
    vector<Reserve*> reservesToShow = getSpecificRestaurantReserves(restaurantName);
    if (reservesToShow.empty()) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    for (auto reserve : reservesToShow)
        reserve->shortPrint();
}

vector<Reserve *> User::getSpecificRestaurantReserves(const std::string &restaurantName) {
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
    if (targetReserve == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);

    targetReserve->removeReserveFromTable();
    reserves.erase(std::remove(reserves.begin(), reserves.end(), targetReserve), reserves.end());

    delete targetReserve;
}

