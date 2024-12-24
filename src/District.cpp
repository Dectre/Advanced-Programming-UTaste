#include "District.h"

District::District(string name_, vector<District*> neighbors_) {
    name = name_;
    neighbors = neighbors_;
}

District::District(std::string name_) {
    name = name_;
}