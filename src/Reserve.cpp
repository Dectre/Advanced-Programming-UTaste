#include "../header/Reserve.h"
#include "../header/Table.h"
#include "../header/Restaurant.h"
#include "../header/User.h"

Reserve::Reserve(const string& s, const string& e, Table* t, User* u) {
    startTime = safeStoi(s);
    endTime = safeStoi(e);
    table = t;
    customer = u;
    initID();
}

Reserve::Reserve(const string& s, const string& e, Table* t, const vector<string>& o, User* u) {
    startTime = safeStoi(s);
    endTime = safeStoi(e);
    table = t;
    initFoods(o);
    calculatePrice();
    if (priceAfterDiscount > u->getBudget()) {
        throw invalid_argument(BAD_REQUEST_RESPONSE);
    }
    initID();
    customer = u;
}

void Reserve::timePrint() const {
    cout << IN_DELIMITER << startTime << TO_DELIMITER << endTime << OUT_DELIMITER;
}

bool Reserve::checkConflict(const string& sTime, const string& eTime) const {
    return !(safeStoi(sTime) >= endTime || safeStoi(eTime) <= startTime);
}

void Reserve::initFoods(const vector<string>& foodsList) {
    for (const auto& foodName : foodsList)
        order.push_back(table->getRestaurant()->getFoodByName(foodName));
}

void Reserve::initID() {
    Restaurant* restaurant = table->getRestaurant();
    int ReserveID = restaurant->getLastReserveID() + 1;
    id = ReserveID;
}

void Reserve::print() const {
    cout << RESERVE_ID_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << id << endl
         << TABLE_OUTPUT << WORD_SEPARATOR_DELIMITER << table->getId() << WORD_SEPARATOR_DELIMITER
         << FOR_OUTPUT << WORD_SEPARATOR_DELIMITER << startTime << WORD_SEPARATOR_DELIMITER
         << TO_OUTPUT << WORD_SEPARATOR_DELIMITER << endTime << WORD_SEPARATOR_DELIMITER
         << IN_OUTPUT << WORD_SEPARATOR_DELIMITER << table->getRestaurant()->getName() << endl;
    pricePrint();
}

void Reserve::pricePrint() const {
    if (discounts[0] != 0 || discounts[1] != 0 || discounts[2] != 0) {
        cout << ORIGINAL_PRICE_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << priceBeforeDiscount << endl;
        if (discounts[2] != 0)
            cout << TOTAL_ORDER_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << discounts[2]
                 << endl;
        if (discounts[0] != 0)
            cout << TOTAL_ITEM_SPECIFIC_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER
                 << discounts[0] << endl;
        if (discounts[1] != 0)
            cout << TOTAL_ITEM_SPECIFIC_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER
                 << discounts[0] << endl;
        cout << TOTAL_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER
             << discounts[0] + discounts[1] + discounts[2] << endl;
        cout << TOTAL_PRICE_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << priceAfterDiscount << endl;
    }
    else
        cout << PRICE_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << priceBeforeDiscount << endl;
}


void Reserve::calculatePrice() {
    Restaurant* restaurant = table->getRestaurant();
    for (auto food : order) {
        priceBeforeDiscount += food->getPrice();
        priceAfterDiscount += food->getDiscountedPrice();
    }
    discounts[0] = priceBeforeDiscount - priceAfterDiscount;
    int tempPrice = priceAfterDiscount;
    if (!restaurant->findCustomer(customer)) {
        priceAfterDiscount = restaurant->getPriceAfterFirstOrderDiscount(priceAfterDiscount);
        discounts[1] = tempPrice - priceAfterDiscount;
    }
    tempPrice = priceAfterDiscount;
    priceAfterDiscount = restaurant->getPriceAfterTotalOrderDiscount(priceAfterDiscount);
    discounts[2] = tempPrice - priceAfterDiscount;
}

void Reserve::shortPrint() const {
    cout << id << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER
         << table->getRestaurant()->getName() << WORD_SEPARATOR_DELIMITER
         << table->getId() << WORD_SEPARATOR_DELIMITER
         << startTime << TO_DELIMITER << endTime << WORD_SEPARATOR_DELIMITER;
    printOrders();
    cout << endl;
}

void Reserve::printOrders() const {
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
        cout << foodName << IN_DELIMITER << count << OUT_DELIMITER << WORD_SEPARATOR_DELIMITER;
}

bool Reserve::checkRestaurant(const string &restaurantName) const {
    return restaurantName == table->getRestaurant()->getName();
}

Reserve* Reserve::find(const string &restaurantName, const string &reserveID) {
    if (table->getRestaurant()->getName() == restaurantName && safeStoi(reserveID) == id) return this;
    return nullptr;
}

void Reserve::removeReserveFromTable() {
    table->removeReserve(this);
}
