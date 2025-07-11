#include "../header/Restaurant.h"
#include "../header/District.h"
#include "../header/User.h"

Restaurant::Restaurant(const string& name_, District* location_, const vector<map<string, string>>& menu_,
                       const string& openingTime_, const string& closingTime_, const string& numOfTables) {
    name = name_;
    location = location_;
    handleMenu(menu_);
    openingTime = safeStoi(openingTime_);
    closingTime = safeStoi(closingTime_);
    for (int i = 0; i < safeStoi(numOfTables) ; i++) {
        tables.push_back(new Table(i + 1, this));
    }
}

void Restaurant::handleMenu(const vector<map<string, string>>& menu_) {
    for (auto food : menu_)
        menu.push_back(new Food(food[NAME_KEY], safeStoi(food[PRICE_KEY])));
}

void Restaurant::shortPrint() {
    cout << name << WORD_SEPARATOR_DELIMITER << IN_DELIMITER << location->getName() << OUT_DELIMITER << endl;
}

bool Restaurant::hasFood(const string& foodName) {
    for (auto menuItem : menu)
        if (menuItem->getName() == foodName) return true;
    return false;
}

void Restaurant::detailedPrint() {
    cout << NAME_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << name << endl;
    cout << DISTRICT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << location->getName() << endl;
    cout << TIME_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER << openingTime << TO_DELIMITER << closingTime << endl;
    cout << MENU_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER;
    menuPrint();
    tablesPrint();
    discountsPrint();
}

void Restaurant::menuPrint() {
    for (size_t i = 0; i < menu.size(); i++) {
        menu[i]->print();
        if (i != menu.size() - 1)
            cout << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER;
    }
    cout << endl;
}

void Restaurant::tablesPrint() {
    for (auto table : tables) {
        table->print();
        cout << endl;
    }
}

void Restaurant::reserveTable(const string &tableId, const string &startTime, const string &endTime, const string &foods, User* user) {
    Table* table = findTableByID(tableId);
    if (table == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    if (!checkTimeConflicts(startTime, endTime)) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    table->reserve(startTime, endTime, foods, user);
    lastReserveId += 1;
}

Table* Restaurant::findTableByID(const string &tableID) {
    for (auto table:tables) {
        if (safeStoi(tableID) == table->getId())
            return table;
    }
    return nullptr;
}

bool Restaurant::checkTimeConflicts(const string &startTime, const string &endTime) {
    int start = safeStoi(startTime);
    int end = safeStoi(endTime);
    if (start == end)
        throw invalid_argument(BAD_REQUEST_RESPONSE);
    if (start < 1 || start > 24 || end < 1 || end > 24)
        return false;
    if (end > closingTime || start < openingTime)
        return false;
    return true;
}


Food* Restaurant::getFoodByName(const string &foodName) {
    for (auto food : menu)
        if (foodName == food->getName())
            return food;
    return nullptr;
}

bool Restaurant::checkReserve(const string &reserveID) {
    for (auto table : tables) {
        if (table->checkReserve(reserveID)) return true;
    }
    return false;
}

void Restaurant::setDiscounts(vector<std::string> discounts) {
    vector<string> totalPriceDetails = splitStringBy(discounts[0], ELEMENT_SEPARATOR_DELIMITER);
    handleTotalPriceDiscount(totalPriceDetails);
    vector<string> firstOrderDetails = splitStringBy(discounts[1], ELEMENT_SEPARATOR_DELIMITER);
    handleFirstOrderDiscount(firstOrderDetails);
    vector<string> foodsDiscount = splitStringBy(discounts[2], FOOD_SEPERATOR_DELIMITER);
    handleFoodsDiscount(foodsDiscount);
}

void Restaurant::handleTotalPriceDiscount(vector<string> totalPriceDetails) {
    if (totalPriceDetails[0] == NONE)
        totalPriceDiscount = nullptr;
    else if (totalPriceDetails[0] == byPERCENT)
        totalPriceDiscount = new DiscountPerPercent(totalPriceDetails[1], totalPriceDetails[2]);
    else
        totalPriceDiscount = new DiscountPerAmount(totalPriceDetails[1], totalPriceDetails[2]);
}

void Restaurant::handleFirstOrderDiscount(vector<string> firstOrderDetails) {
    if (firstOrderDetails[0] == NONE)
        firstOrderDiscount = nullptr;
    else if (firstOrderDetails[0] == byPERCENT)
        firstOrderDiscount = new DiscountPerPercent(firstOrderDetails[1]);
    else
        firstOrderDiscount = new DiscountPerAmount(firstOrderDetails[1]);
}

void Restaurant::handleFoodsDiscount(vector<std::string> foodsDiscountDetails) {
    if (foodsDiscountDetails[0] != NONE) {
        for (auto foodDiscountDetails: foodsDiscountDetails) {
            vector<string> discountDetails = splitStringBy(foodDiscountDetails, ELEMENT_SEPARATOR_DELIMITER);
            vector<string> foodDetails = splitStringBy(discountDetails[1], EXPLANATION_DELIMITER);
            Food *food = getFoodByName(foodDetails[0]);
            food->setDiscount(discountDetails[0], foodDetails[1]);
        }
    }
}

void Restaurant::discountsPrint() {
    if (totalPriceDiscount != nullptr)
        cout << TOTAL_ORDER_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER <<
             totalPriceDiscount->getType() << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER <<
             totalPriceDiscount->getMinimum() << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER <<
             totalPriceDiscount->getValue() << endl;
    foodsDiscountPrint();
    if (firstOrderDiscount != nullptr)
        cout << FIRST_ORDER_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER <<
             firstOrderDiscount->getType() << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER <<
             firstOrderDiscount->getValue() << endl;
}

void Restaurant::foodsDiscountPrint() {
    if (checkIfRestaurantHasFoodDiscount()) {
        cout << ITEM_SPECIFIC_DISCOUNT_OUTPUT << EXPLANATION_DELIMITER << WORD_SEPARATOR_DELIMITER;
        size_t count = 0;
        vector<Food*> foodsWithDiscount = getFoodsWithDiscount();
        for (auto food : foodsWithDiscount) {
            if (food->getDiscount() != nullptr) {
                Discount* discount = food->getDiscount();
                cout << food->getName() << IN_DELIMITER
                     << discount->getType() << EXPLANATION_DELIMITER
                     << WORD_SEPARATOR_DELIMITER << discount->getValue() << OUT_DELIMITER;
                count++;
                if (count < foodsWithDiscount.size())
                    cout << SEPARATOR_DELIMITER << WORD_SEPARATOR_DELIMITER;
            }
        }
        cout << endl;
    }
}

vector<Food *> Restaurant::getFoodsWithDiscount() {
    vector<Food*> foodsWithDiscount;
    for (auto food : menu) {
        if (food->getDiscount() != nullptr )
            foodsWithDiscount.push_back(food);
    }
    return foodsWithDiscount;
}

bool Restaurant::checkIfRestaurantHasFoodDiscount() {
    for (auto food : menu) {
        if (food->getDiscount() != nullptr)
            return true;
    }
    return false;
}

bool Restaurant::findCustomer(User* user) {
    for (auto customer : customersClub)
        if (customer == user) return true;
    return false;
}

int Restaurant::getPriceAfterFirstOrderDiscount(int price) {
    if (firstOrderDiscount != nullptr)
        return firstOrderDiscount->getDiscountedPrice(price);
    return price;
}

int Restaurant::getPriceAfterTotalOrderDiscount(int price) {
    if (totalPriceDiscount != nullptr)
        return totalPriceDiscount->getDiscountedPrice(price);
    return price;
}
