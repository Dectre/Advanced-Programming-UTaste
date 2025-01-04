#ifndef UTASTE_RESERVE_H
#define UTASTE_RESERVE_H

#include "Manual.h"

class Food;
class Table;
class User;

class Reserve {
public:
    Reserve(const string& s, const string& e, Table* t, User* u);
    Reserve(const string& s, const string& e, Table* t, const vector<string>& o, User* u);
    int getID() const { return id; }
    void timePrint() const;
    bool checkConflict(const string& sTime, const string& eTime) const;
    void print() const;
    void shortPrint() const;
    void printOrders() const;
    bool checkRestaurant(const string& restaurantName) const;
    Reserve* find(const string& restaurantName, const string& reserveID);
    void removeReserveFromTable();
    Table* getTable() const { return table; }
    int getPriceAfterDiscount() { return priceAfterDiscount; }

private:
    int id;
    Table* table;
    int startTime;
    int endTime;
    vector<Food*> order;
    int priceBeforeDiscount = 0;
    int priceAfterDiscount = 0;
    User* customer;
    vector<int> discounts = {0, 0, 0};

    void initFoods(const vector<string>& foodsList);
    void initID();
    void calculatePrice();
    void pricePrint() const;
};

#endif //UTASTE_RESERVE_H
