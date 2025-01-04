#include "../header/Food.h"

Food::Food (const string& n,const int& p){
    name = n;
    price = p;
}

void Food::print() {
    cout << name << IN_DELIMITER << price << OUT_DELIMITER;
}

void Food::setDiscount(string type, string value) {
    if (type == byPERCENT)
        discount = new DiscountPerPercent(value);
    else
        discount = new DiscountPerAmount(value);
}

int Food::getDiscountedPrice() {
    if (discount != nullptr) return discount->getDiscountedPrice(price);
    return price;
}