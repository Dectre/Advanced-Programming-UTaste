#include "District.h"

District::District(string name_, vector<District*> neighbors_, vector<Restaurant> restaurants_) {
    name = name_;
    neighbors = neighbors_;
    restaurants = restaurants_;
}

District::District(std::string name_) {
    name = name_;
}