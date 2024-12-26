#include "Food.h"

Food::Food (const string& n,const int& p){
    name = n;
    price = p;
}

void Food::print() {
    cout << name << IN_DELIMITER << price << OUT_DELIMITER;
}