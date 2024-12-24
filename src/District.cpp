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