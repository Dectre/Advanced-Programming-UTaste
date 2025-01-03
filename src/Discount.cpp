#include "../header/Discount.h"

DiscountPerPercent::DiscountPerPercent(const string& minimum_, const string& percent_) {
    minimumPrice = stoi(minimum_);
    percent = stod(percent_);
}

DiscountPerPercent::DiscountPerPercent(const string& percent_) {
    this->percent = stod(percent_);
}

DiscountPerAmount::DiscountPerAmount(const string& minimum_, const string& amount_) {
    minimumPrice = stoi(minimum_);
    amount = stoi(amount_);
}

DiscountPerAmount::DiscountPerAmount(const string& amount_) {
    amount = stoi(amount_);
}

int DiscountPerAmount::getDiscountedPrice(int price) {
    if (price >= minimumPrice)
        return price - amount;
    return price;
}

int DiscountPerPercent::getDiscountedPrice(int price) {
    if (price >= minimumPrice)
        return price - (price * percent / 100);
    return price;
}