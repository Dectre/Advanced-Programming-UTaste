#include "User.h"
User::User(string u, string p) {
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

