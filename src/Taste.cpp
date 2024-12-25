#include "Taste.h"
#include "User.h"

 Taste::Taste() {
     districts.clear();
}
 Taste::~Taste() {}




bool Taste::usernameExists(const std::string &username) {
    for (auto user : users){
        if (user->getUsername() == username)
            return true;
    }
    return false;
}

void Taste::signUp(const std::string &username, const std::string &password) {
    if (currentUser != nullptr)
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    if (usernameExists(username))
        throw invalid_argument(BAD_REQUEST_RESPONSE);
    users.push_back(new User(username, password));
    currentUser = users[users.size()-1];
    cout << SUCCESSFUL_RESPONSE << endl;
}

void Taste::login(const std::string &username, const std::string &password) {
    if (currentUser == nullptr) {
        for (auto user: users) {
            if (user->getUsername() == username && user->getPassword() != password)
                throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
            if (user->getUsername() == username && user->getPassword() == password) {
                currentUser = user;
                cout << SUCCESSFUL_RESPONSE << endl;
            }
        }
        if (currentUser == nullptr)
            throw invalid_argument(NON_EXISTENCE_RESPONSE);
    }
    else
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
}

void Taste::logout() {
    if (currentUser != nullptr) {
        currentUser = nullptr;
        cout << SUCCESSFUL_RESPONSE << endl;
    }
    else
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
}

District* Taste::findDistrictByName(std::string name) {
    for (auto district : districts) {
        if (name == district->getName())
            return district;
    }
    return nullptr;
}

vector<District*> Taste::handleNeighbors(vector<string> neighborsList) {
    vector<District*> districtNeighbors;
    for (auto name : neighborsList) {
        if (findDistrictByName(name) == nullptr) {
            districts.push_back(new District(name));
            districtNeighbors.push_back(districts[districts.size() - 1]);
        }
        else
            districtNeighbors.push_back(findDistrictByName(name));
    }
    return districtNeighbors;
}

void Taste::handleDistrict(std::string name, vector<string> neighborsList) {
    vector<District*> neighbors = handleNeighbors(neighborsList);
    if (findDistrictByName(name) == nullptr)
        districts.push_back(new District(name, neighbors));
    else {
        District* district = findDistrictByName(name);
        for (auto neighbor: neighbors) {
            district->addNeighbor(neighbor);
        }
    }
}

void Taste::handleRestaurant(vector<std::string> arguments, vector<map<std::string, std::string>> foods) {
    District* restaurantLocation = findDistrictByName(arguments[1]);
    restaurantLocation->newRestaurant(arguments, foods);
}

void Taste::sortDistricts() {
    sort(districts.begin(), districts.end(), [](District* a, District* b) {
        return a->getName() < b->getName();
    });
}

void Taste::showDistricts() {
    if (currentUser != nullptr) {
        if (districts.empty()) throw invalid_argument(EMPTY_RESPONSE);
        for (auto district : districts) {
            district->print();
        }
    }
    else
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
}

void Taste::showSpecificDistrict(std::string districtName) {
    if (currentUser != nullptr) {
        if (districts.empty()) throw invalid_argument(EMPTY_RESPONSE);
        District* district = findDistrictByName(districtName);
        if (district == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
        district->print();
    }
    else
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
}
