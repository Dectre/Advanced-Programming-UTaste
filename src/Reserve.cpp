#include "Reserve.h"
#include "Food.h"
#include "User.h"

Reserve::Reserve(int s, int e, User *c) {
    startTime = s;
    endTime = e;
    customer = c;
}

Reserve::Reserve(int s, int e, User *c, vector<Food*> o) {
    startTime = s;
    endTime = e;
    customer = c;
    order = move(o);
}

void Reserve::timePrint() {
    cout << IN_DELIMITER << startTime << TO_DELIMITER << endTime << OUT_DELIMITER;
}
