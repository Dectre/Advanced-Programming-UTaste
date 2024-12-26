#include "../header/Restaurant.h"
#include "../header/District.h"

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

void Restaurant::reserveTable(const string &tableId, const string &startTime, const string &endTime, const string &foods) {
    Table* table = findTableByID(tableId);
    if (table == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    if (!checkTimeConflicts(startTime, endTime)) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    table->reserve(startTime, endTime, foods);
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
    if (end >= closingTime || start <= openingTime)
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
