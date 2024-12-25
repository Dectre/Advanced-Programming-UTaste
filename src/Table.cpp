#include "Table.h"
#include "Reserve.h"

Table::Table(int id_) {
    id = id_;
}

void Table::print() {
    cout << id << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER;
    reservesTimePrint();
}

void Table::reservesTimePrint() {
    for (size_t i = 0; i < reserves.size(); i++) {
        reserves[i]->timePrint();
        if (i != reserves.size() - 1)
            cout << endl;
    }
}