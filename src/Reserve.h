#ifndef UTASTE_RESERVE_H
#define UTASTE_RESERVE_H

#include "Manual.h"

class Food;
class Table;

class Reserve {
public:
    Reserve(const string& s, const string& e, Table* t);
    Reserve(const string& s, const string& e, Table* t, const vector<string>& o);
    int getID() { return id; }
    void timePrint();
    bool checkConflict(const string& sTime, const string& eTime);
    void print();
    void shortPrint();
    void printOrders();
    bool checkRestaurant(const string& restaurantName);
    Reserve* find(const string& restaurantName, const string& reserveID);
    void removeReserveFromTable();
private:
    int id;
    Table* table;
    int startTime;
    int endTime;
    vector<Food*> order;
    int price = 0;

    void initFoods(const vector<string>& foodsList);
    void initID();
    void calculatePrice();
};


#endif //UTASTE_RESERVE_H
