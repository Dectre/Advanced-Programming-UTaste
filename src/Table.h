#ifndef UTASTE_TABLE_H
#define UTASTE_TABLE_H

#include "Manual.h"

class Reserve;
class Restaurant;

class Table {
private:
    int id;
    vector<Reserve*> reserves;
    Restaurant* restaurant;
public:
    Table(const int& id_, Restaurant* restaurant_);
    int getId() { return id; }
    void print();
    void reservesTimePrint();
    Restaurant* getRestaurant() { return restaurant; }
    void reserve(const string& startTime, const string& endTime, const string& foods);
    bool isConflicted(const string& startTime, const string& endTime);
    vector<string> handleFoods(const string& foods);
    Reserve* getLastReserve() { return reserves[reserves.size()-1];}
    bool checkReserve(const string& reserveID);
    void removeReserve(Reserve* targetReserve);
};


#endif //UTASTE_TABLE_H
