#ifndef UTASTE_RESERVE_H
#define UTASTE_RESERVE_H

#include "Manual.h"

class Food;
class User;

class Reserve {
public:
    Reserve(int s, int e, User* c);
    Reserve(int s, int e, User* c, vector<Food*> o);
    int getStartTime() { return startTime; }
    int getEndTime() { return endTime; }
    User* getUser() { return customer; }
    vector<Food*> getOrder() { return order; }
    void timePrint();
private:
    int startTime;
    int endTime;
    User* customer;
    vector<Food*> order;
};


#endif //UTASTE_RESERVE_H
