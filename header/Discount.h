#ifndef UTASTE_DISCOUNT_H
#define UTASTE_DISCOUNT_H

#include "Manual.h"

class Discount {
public:
    virtual int getValue() const = 0;
    virtual int getDiscountedPrice(int price) const = 0;
    int getMinimum() const { return minimumPrice; }
    string getType() const { return type; }

protected:
    int minimumPrice = 0;
    string type;
};

class DiscountPerAmount : public Discount {
private:
    int amount;
public:
    DiscountPerAmount(const string& minimum_, const string& amount_);
    DiscountPerAmount(const string& amount_);
    int getValue() const override;
    int getDiscountedPrice(int price) const override;
};

class DiscountPerPercent : public Discount {
private:
    int percent;
public:
    DiscountPerPercent(const string& minimum_, const string& percent_);
    DiscountPerPercent(const string& percent_);
    int getValue() const override;
    int getDiscountedPrice(int price) const override;
};

#endif // UTASTE_DISCOUNT_H
