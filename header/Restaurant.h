#ifndef UTASTE_RESTAURANT_H
#define UTASTE_RESTAURANT_H

#include "Food.h"
#include "Table.h"
#include "Discount.h"

class District;

class Restaurant {
private:
    string name;
    District* location;
    vector<Food*> menu;
    int openingTime;
    int closingTime;
    vector<Table*> tables;
    int lastReserveId = 0;
    Discount* firstOrderDiscount;
    Discount* totalPriceDiscount;
    void handleMenu(const vector<map<string, string>>& menu_);
public:
    Restaurant(const string& name_, District* location_, const vector<map<string, string>>& menu_,
               const string& openingTime_, const string& closingTime_, const string& numOfTables);
    string getName() { return name; }

    void shortPrint();
    bool hasFood(const std::string& foodName);
    void detailedPrint();
    void menuPrint();
    void tablesPrint();

    void reserveTable(const string &tableId, const string &startTime, const string &endTime, const string &foods);
    Table* findTableByID(const string& tableID);
    bool checkTimeConflicts(const string& startTime, const string& endTime);
    Food* getFoodByName(const string& foodName);
    int getLastReserveID() const {return lastReserveId;}
    bool checkReserve(const string& reserveID);

    void setDiscounts(vector<string> discounts);
    void handleTotalPriceDiscount(vector<string> totalPriceDetails);
    void handleFirstOrderDiscount(vector<string> firstOrderDetails);
    void handleFoodsDiscount(vector<string> foodsDiscountDetails);

};

#endif //UTASTE_RESTAURANT_H
