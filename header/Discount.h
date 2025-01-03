#ifndef UTASTE_DISCOUNT_H
#define UTASTE_DISCOUNT_H

#include "Manual.h"

class Discount {
public:
    void getMinimum();
protected:
    int minimumPrice= 0;
    int getValue();
    int getDiscountedPrice(int price);
};

class DiscountPerAmount : public Discount {
private:
    int amount;
public:
    DiscountPerAmount(string minimum_, string amount_);
    DiscountPerAmount(string amount_);
    int getAmount() { return amount; }
    int getDiscountedPrice(int price);
};

class DiscountPerPercent : public Discount {
private:
    double percent;
public:
    DiscountPerPercent(string minimum_, string percent_);
    DiscountPerPercent(string percent_);
    double getPercent() { return percent; }
    int getDiscountedPrice(int price);
};

#endif //UTASTE_DISCOUNT_H
