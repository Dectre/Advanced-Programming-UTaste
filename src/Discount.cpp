#include "../header/Discount.h"

DiscountPerPercent::DiscountPerPercent(string minimum_, string percent_) {
    minimumPrice = stoi(minimum_);
    percent = stod(percent_);
}

DiscountPerPercent::DiscountPerPercent(string percent_) {
    this->percent = stod(percent_);
}

DiscountPerAmount::DiscountPerAmount(string minimum_, string amount_) {
    minimumPrice = stoi(minimum_);
    amount = stoi(amount_);
}

DiscountPerAmount::DiscountPerAmount(string amount_) {
    amount = stoi(amount_);
}

int DiscountPerAmount::getDiscountedPrice(int price) {
    if (price >= minimumPrice)
        return price - amount;
    return price;
}

int DiscountPerPercent::getDiscountedPrice(int price) {
    if (price >= minimumPrice)
        return price - (price * percent);
    return price;
}