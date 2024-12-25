#ifndef UTASTE_TABLE_H
#define UTASTE_TABLE_H

#include "Manual.h"

class Reserve;

class Table {
private:
    int id;
    vector<Reserve*> reserves;
public:
    Table(int id_);
    int getId() { return id; }
    vector<Reserve*> getReserves() { return reserves; }
    void print();
    void reservesTimePrint();
};


#endif //UTASTE_TABLE_H
