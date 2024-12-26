#ifndef UTASTE_RESTAURANT_H
#define UTASTE_RESTAURANT_H

#include "Food.h"
#include "Table.h"

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
    void handleMenu(vector<map<string, string>> menu_);
public:
    Restaurant(string name_, District* location_, vector<map<string, string>> menu_,
               string openingTime_, string closingTime_, string numOfTables);
    string getName() { return name; }
    District* getLocation() { return location; }
    vector<Food*> getMenu() { return menu; }

    void shortPrint();
    bool hasFood(const std::string& foodName);
    void detailedPrint();
    void menuPrint();
    void tablesPrint();

    void reserveTable(const string &tableId, const string &startTime, const string &endTime, const string &foods);
    Table* findTableByID(const string& tableID);
    bool checkTimeConflicts(const string& startTime, const string& endTime);
    Food* getFoodByName(const string& foodName);
    void findLastReserveID();
    int getLastReserveID() {return lastReserveId;}
};


#endif //UTASTE_RESTAURANT_H
