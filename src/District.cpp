#include "District.h"

District::District(string name_, vector<District*> neighbors_) {
    name = name_;
    neighbors = neighbors_;
}

District::District(std::string name_) {
    name = name_;
}

void District::newRestaurant(vector<std::string> arguments, vector<map<std::string, std::string>> menu) {
    addRestaurant(new Restaurant(arguments[0], this, menu, arguments[3], arguments[4], arguments[5]));
}

void District::print() {
    cout << name << EXPLANATION_DELIMITER << WORD_SEPERATOR_DELIMITER;
    printNeighbors();
    cout << '\n';
}

void District::printNeighbors() {
    for (size_t i = 0; i < neighbors.size(); i++) {
        cout << neighbors[i]->getName();
        if (i != neighbors.size() - 1)
            cout << SEPERATOR_DELIMITER << WORD_SEPERATOR_DELIMITER;
    }
}

