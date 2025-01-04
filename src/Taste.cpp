#include "../header/Taste.h"

Taste::Taste() {}
Taste::~Taste() {}

void Taste::checkIfLoggedIn() {
    if (currentUser == nullptr)
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
}

bool Taste::usernameExists(const string &username) {
    for (auto user : users){
        if (user->getUsername() == username)
            return true;
    }
    return false;
}

void Taste::signUp(const string &username, const string &password) {
    if (currentUser != nullptr)
        throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    if (usernameExists(username))
        throw invalid_argument(BAD_REQUEST_RESPONSE);
    users.push_back(new User(username, password));
    currentUser = users[users.size()-1];
    cout << SUCCESSFUL_RESPONSE << endl;
}

void Taste::login(const string &username, const string &password) {
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
    checkIfLoggedIn();
    currentUser = nullptr;
    cout << SUCCESSFUL_RESPONSE << endl;
}

District* Taste::findDistrictByName(const string& name) {
    for (auto district : districts) {
        if (name == district->getName())
            return district;
    }
    return nullptr;
}

vector<District*> Taste::handleNeighbors(const vector<string>& neighborsList) {
    vector<District*> districtNeighbors;
    for (const auto& name : neighborsList) {
        if (findDistrictByName(name) == nullptr) {
            districts.push_back(new District(name));
            districtNeighbors.push_back(districts[districts.size() - 1]);
        }
        else
            districtNeighbors.push_back(findDistrictByName(name));
    }
    return districtNeighbors;
}

void Taste::handleDistrict(const string& name, const vector<string>& neighborsList) {
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

void Taste::handleRestaurant(vector<string> arguments, const vector<map<string, string>>& foods) {
    District* restaurantLocation = findDistrictByName(arguments[1]);
    restaurantLocation->newRestaurant(arguments, foods);
}


void Taste::sortDistricts() {
    sort(districts.begin(), districts.end(), [](District* a, District* b) {
        return a->getName() < b->getName();
    });
}

void Taste::showDistricts() {
    checkIfLoggedIn();
    if (districts.empty()) throw invalid_argument(EMPTY_RESPONSE);
    for (auto district : districts)
        district->print();
}

void Taste::showSpecificDistrict(const string& districtName) {
    checkIfLoggedIn();
    if (districts.empty()) throw invalid_argument(EMPTY_RESPONSE);
    District* district = findDistrictByName(districtName);
    if (district == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    district->print();
}

void Taste::setUserLocation(const string& districtName) {
    checkIfLoggedIn();
    District* district = findDistrictByName(districtName);
    if (district == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    currentUser->setLocation(district);
    cout << SUCCESSFUL_RESPONSE << endl;
}

void Taste::showRestaurants() {
    checkIfLoggedIn();
    District* currentLocation = getUserLocation();
    checkLocationExists(currentLocation);
    set<District*> visited;
    queue<District*> toVisit;
    initializeTraversal(currentLocation, visited, toVisit);
    processDistrictsForRestaurants(visited, toVisit);
}

void Taste::showSpecificRestaurants(const string& foodName) {
    checkIfLoggedIn();
    District* currentLocation = getUserLocation();
    checkLocationExists(currentLocation);

    set<District*> visited;
    queue<District*> toVisit;

    initializeTraversal(currentLocation, visited, toVisit);
    bool foundRestaurants = processSpecificDistrictsForRestaurants(foodName, visited, toVisit);

    if (!foundRestaurants) {
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
    }
}

void Taste::checkLocationExists(District* location) {
    if (location == nullptr)
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

void Taste::initializeTraversal(District* startDistrict, set<District*>& visited, queue<District*>& toVisit) {
    toVisit.push(startDistrict);
    visited.insert(startDistrict);
}

void Taste::processDistrictsForRestaurants(set<District*>& visited, queue<District*>& toVisit) {
    while (!toVisit.empty()) {
        District* currentDistrict = toVisit.front();
        toVisit.pop();
        currentDistrict->showRestaurants();
        for (auto neighbor : currentDistrict->getNeighbors()) {
            if (visited.find(neighbor) == visited.end()) {
                toVisit.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}

bool Taste::processSpecificDistrictsForRestaurants(const string& foodName, set<District*>& visited, queue<District*>& toVisit) {
    bool foundRestaurants = false;
    while (!toVisit.empty()) {
        District* currentDistrict = toVisit.front();
        toVisit.pop();
        if (currentDistrict->showRestaurantsByFood(foodName)) foundRestaurants = true;
        for (auto neighbor : currentDistrict->getNeighbors()) {
            if (visited.find(neighbor) == visited.end()) {
                toVisit.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
    return foundRestaurants;
}

void Taste::districtsShowRestaurantDetail(const string &restaurantName) {
    checkIfLoggedIn();
    bool foundRestaurant = false;
    for (auto district : districts) {
        try {
            district->showRestaurantDetail(restaurantName);
            foundRestaurant = true;
            break;
        } catch (const invalid_argument& err) {}
    }
    if (!foundRestaurant)
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

void Taste::reserveTableInRestaurant(const string &restaurantName, const string &tableId, const string &startTime,
                                     const string &endTime, const string &foods) {
    checkIfLoggedIn();
    if (currentUser->checkConflicts(startTime, endTime)) throw invalid_argument(UNABLE_TO_ACCESS_RESPONSE);
    District* district = getDistrictWithTheRestaurant(restaurantName);
    if (district == nullptr) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    district->reserveTableInRestaurant(restaurantName, tableId, startTime, endTime, foods, currentUser);
    Reserve* reserve = getLastReserve(district, restaurantName, tableId);
    currentUser->addReserve(reserve);
    district->findRestaurantByName(restaurantName)->addCustomer(currentUser);
    reserve->print();
}

District* Taste::getDistrictWithTheRestaurant(const string& restaurantName) {
    District* districtWithTheRestaurant;
    for (auto district:districts) {
        districtWithTheRestaurant = district->checkIfItHasRestaurant(restaurantName);
        if (districtWithTheRestaurant != nullptr)
            return districtWithTheRestaurant;
    }
    return nullptr;
}

Reserve *Taste::getLastReserve(District* district, const string &restaurantName, const string &tableId) {
    Restaurant* restaurant = district->findRestaurantByName(restaurantName);
    Table* table = restaurant->findTableByID(tableId);
    Reserve* reserve = table->getLastReserve();
    return reserve;
}

void Taste::getUserReserves(const string &restaurantName, const string &reserveID) {
    checkIfLoggedIn();
    if (!reserveID.empty() && restaurantName.empty()) throw invalid_argument(BAD_REQUEST_RESPONSE);
    else if (restaurantName.empty() && reserveID.empty())
        currentUser->showReserves();
    else if (!restaurantName.empty() && reserveID.empty())
        currentUser->showReservesForRestaurant(restaurantName);
    else {
        if (!checkRestaurantForReserve(restaurantName, reserveID)) throw invalid_argument(NON_EXISTENCE_RESPONSE);
        currentUser->showReserve(restaurantName, reserveID);
    }
}

bool Taste::checkRestaurantForReserve(const string &restaurantName, const string &reserveID) {
    District* district = getDistrictWithTheRestaurant(restaurantName);
    if (!district) return false;
    Restaurant* restaurant = district->findRestaurantByName(restaurantName);
    return restaurant->checkReserve(reserveID);
}

void Taste::deleteUserReserve(const string &restaurantName, const string &reserveID) {
    checkIfLoggedIn();
    if (!checkRestaurantForReserve(restaurantName, reserveID)) throw invalid_argument(NON_EXISTENCE_RESPONSE);
    currentUser->deleteReserve(restaurantName, reserveID);
    cout << SUCCESSFUL_RESPONSE << endl;
}

void Taste::handleDiscounts(vector<string> arguments) {
    string restaurantName = arguments[0];
    vector<string> discounts = vector<string>(arguments.begin() + 1, arguments.end());
    District* district = getDistrictWithTheRestaurant(restaurantName);
    Restaurant* restaurant = district->findRestaurantByName(restaurantName);
    restaurant->setDiscounts(discounts);
}

void Taste::increaseUserBudget(string amount) {
    checkIfLoggedIn();
    currentUser->increaseBudget(amount);
}

void Taste::showUserBudget() {
    checkIfLoggedIn();
    currentUser->showBudget();
}
