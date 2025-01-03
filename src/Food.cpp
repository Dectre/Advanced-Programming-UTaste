#include "../header/Food.h"

Food::Food (const string& n,const int& p){
    name = n;
    price = p;
}

void Food::print() {
    cout << name << IN_DELIMITER << price << OUT_DELIMITER;
}

void Food::setDiscount(string type, string value) {
    if (type == PERCENT)
        discount = new DiscountPerPercent(value);
    else
        discount = new DiscountPerAmount(value);
}