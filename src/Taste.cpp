#include "../header/Taste.h"

Taste::Taste() {
    handleDistrictsFile();
    handleRestaurantsFile();
    handleDiscountsFile();
}
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
        throw invalid_argument(EMPTY_RESPONSE);
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

void Taste::districtsShowRestaurantDetail(const string& restaurantName) {
    checkIfLoggedIn();
    for (auto district : districts) {
        try {
            Restaurant* restaurant = district->showRestaurantDetail(restaurantName);
            return;
        } catch (const invalid_argument& err) {
        }
    }
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
    else if (!restaurantName.empty() && reserveID.empty()) {
        checkIfRestaurantExist(restaurantName);
        currentUser->showReservesForRestaurant(restaurantName);
    }
    else {
        if (!checkRestaurantForReserve(restaurantName, reserveID)) throw invalid_argument(NON_EXISTENCE_RESPONSE);
        currentUser->showReserve(restaurantName, reserveID);
    }
}

void Taste::checkIfRestaurantExist(const std::string &restaurantName) {
    District* district = getDistrictWithTheRestaurant(restaurantName);
    if (!district) throw invalid_argument(NON_EXISTENCE_RESPONSE);
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

void Taste::increaseUserBudget(const string& amount) {
    checkIfLoggedIn();
    currentUser->increaseBudget(amount);
}

void Taste::showUserBudget() {
    checkIfLoggedIn();
    currentUser->showBudget();
}

void Taste::handleDistrictsFile() {
    ifstream file(DISTRICTS_FILE);
    string line;
    getline(file, line);
    while(getline(file, line)) {
        string tempName;
        string tempNeighbors;
        stringstream lineStream(line);
        getline(lineStream, tempName, ',');
        getline(lineStream, tempNeighbors, ',');
        vector<string> tempNeighborsList = splitStringBy(tempNeighbors, ELEMENT_SEPARATOR_DELIMITER);
        this->handleDistrict(tempName, tempNeighborsList);
    }
    this->sortDistricts();
    file.close();
}

void Taste::handleRestaurantsFile() {
    ifstream file(RESTAURANTS_FILE);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> tempRestaurant = splitStringBy(line, SEPARATOR_DELIMITER);
        vector<map<string, string>> tempFood = handleFood(tempRestaurant[2]);
        this->handleRestaurant(tempRestaurant, tempFood);
    }
    file.close();
}

vector<map<string, string>> Taste::handleFood(const string& menu) {
    vector<string> seperatedMenu = splitStringBy(menu, ELEMENT_SEPARATOR_DELIMITER);
    vector<map<string, string>> finalMenu;
    for (const auto& item : seperatedMenu) {
        vector<string> seperatedFood = splitStringBy(item, EXPLANATION_DELIMITER);
        map<string, string> tempFood; tempFood[NAME_KEY] = seperatedFood[0]; tempFood[PRICE_KEY] = seperatedFood[1];
        finalMenu.push_back(tempFood);
    }
    return finalMenu;
}

void Taste::handleDiscountsFile() {
    ifstream file(DISCOUNTS_FILE);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> tempRestaurant = splitStringBy(line, SEPARATOR_DELIMITER);
        this->handleDiscounts(tempRestaurant);
    }
    file.close();
}


Restaurant* Taste::findRestaurantByName(const string& name) {
    for (District* district : districts) {
        Restaurant* restaurant = district->findRestaurantByName(name);
        if (restaurant) {
            return restaurant;
        }
    }
    return nullptr;
}