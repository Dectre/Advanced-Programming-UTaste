#include "../header/Discount.h"

DiscountPerAmount::DiscountPerAmount(const string& minimum_, const string& amount_) {
    minimumPrice = stoi(minimum_);
    amount = stoi(amount_);
    type = byAMOUNT;
}

DiscountPerAmount::DiscountPerAmount(const string& amount_) {
    amount = stoi(amount_);
    type = byAMOUNT;
}

int DiscountPerAmount::getValue() const {
    return amount;
}

int DiscountPerAmount::getDiscountedPrice(int price) const {
    if (price >= minimumPrice)
        return price - amount > 0 ? price - amount : 0;
    return price;
}

DiscountPerPercent::DiscountPerPercent(const string& minimum_, const string& percent_) {
    minimumPrice = stoi(minimum_);
    percent = stoi(percent_);
    type = PERCENTAGE;
}

DiscountPerPercent::DiscountPerPercent(const string& percent_) {
    percent = stoi(percent_);
    type = PERCENTAGE;
}

int DiscountPerPercent::getValue() const {
    return percent;
}

int DiscountPerPercent::getDiscountedPrice(int price) const {
    if (price >= minimumPrice)
        return price - (price * percent / 100);
    return price;
}
