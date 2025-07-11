#ifndef UTASTE_FOOD_H
#define UTASTE_FOOD_H
#include "Manual.h"
#include "Discount.h"

class Food {
private:
    string name;
    int price;
    Discount* discount = nullptr;
public:
    Food(const string& n,const int& p);
    string getName() { return name; }
    int getPrice() { return price; }
    void print();
    void setDiscount(string type, string value);
    Discount* getDiscount() { return discount; }
    int getDiscountedPrice();
};

#endif //UTASTE_FOOD_H
