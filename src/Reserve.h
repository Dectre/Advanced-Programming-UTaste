#ifndef UTASTE_RESERVE_H
#define UTASTE_RESERVE_H

#include "Manual.h"

class Food;
class User;

class Reserve {
public:
    Reserve(int s, int e, User* c);
    Reserve(int s, int e, User* c, vector<Food*> o);
    int getReserveStartTime() { return reserveStart; }
    int getReserveEndTime() { return reserveEnd; }
    User* getUser() { return customer; }
    vector<Food*> getOrder() { return order; }
private:
    int reserveStart;
    int reserveEnd;
    User* customer;
    vector<Food*> order;
};


#endif //UTASTE_RESERVE_H
