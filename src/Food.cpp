#include "Food.h"

Food::Food(string n, int p) {
    name = n;
    price = p;
}

void Food::print() {
    cout << name << IN_DELIMITER << price << OUT_DELIMITER;
}