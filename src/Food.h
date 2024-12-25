#ifndef UTASTE_FOOD_H
#define UTASTE_FOOD_H
#include "Manual.h"

class Food {
private:
    string name;
    int price;
public:
    Food(string n, int p);
    string getName() { return name; }
    int getPrice() { return price; }
    void print();
};


#endif //UTASTE_FOOD_H
