#include "Reserve.h"
#include "Food.h"
#include "User.h"

Reserve::Reserve(int s, int e, User *c) {
    reserveStart = s;
    reserveEnd = e;
    customer = c;
}

Reserve::Reserve(int s, int e, User *c, vector<Food*> o) {
    reserveStart = s;
    reserveEnd = e;
    customer = c;
    order = move(o);
}

