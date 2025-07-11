#include "../header/System.h"

System::System(Taste *uTaste_) {
    uTaste = uTaste_;
    initFiles();
    running = true;
}

void System::run() {
    try {
        inputWatcher();
    }catch (invalid_argument& err) {
        cout << err.what() << endl;
    }
}

void System::initFiles() {
    handleDistrictsFile();
    handleRestaurantsFile();
    handleDiscountsFile();
}

void System::handleDistrictsFile() {
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
        uTaste->handleDistrict(tempName, tempNeighborsList);
    }
    uTaste->sortDistricts();
    file.close();
}

void System::handleRestaurantsFile() {
    ifstream file(RESTAURANTS_FILE);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> tempRestaurant = splitStringBy(line, SEPARATOR_DELIMITER);
        vector<map<string, string>> tempFood = handleFood(tempRestaurant[2]);
        uTaste->handleRestaurant(tempRestaurant, tempFood);
    }
    file.close();
}

vector<map<string, string>> System::handleFood(const string& menu) {
    vector<string> seperatedMenu = splitStringBy(menu, ELEMENT_SEPARATOR_DELIMITER);
    vector<map<string, string>> finalMenu;
    for (const auto& item : seperatedMenu) {
        vector<string> seperatedFood = splitStringBy(item, EXPLANATION_DELIMITER);
        map<string, string> tempFood; tempFood[NAME_KEY] = seperatedFood[0]; tempFood[PRICE_KEY] = seperatedFood[1];
        finalMenu.push_back(tempFood);
    }
    return finalMenu;
}

void System::handleDiscountsFile() {
    ifstream file(DISCOUNTS_FILE);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream lineStream(line);
        vector<string> tempRestaurant = splitStringBy(line, SEPARATOR_DELIMITER);
        uTaste->handleDiscounts(tempRestaurant);
    }
    file.close();
}
void System::inputWatcher() {
    while (running) {
        string line;
        arguments.clear();
        if (!getline(cin, line)) {
            running = false;
            break;
        }
        try {
            if (line.find(COMMAND_DELIMITER) == string::npos)
                throw invalid_argument(BAD_REQUEST_RESPONSE);
            vector<string> command = splitStringBy(line, COMMAND_DELIMITER);
            inputSeperator(command);
        } catch(invalid_argument& err) {
            cout << err.what() << endl;
        }
    }
}

void System::inputSeperator(vector<string> command) {
    vector<string> mainCommands = splitStringBy(command[0], WORD_SEPARATOR_DELIMITER);
    if (mainCommands.size() != 2)
        throw invalid_argument(BAD_REQUEST_RESPONSE);

    const string& method = mainCommands[0];
    const string& cmd = mainCommands[1];
    string argument = command.size() == 2 ? command[1] : "";

    if (method == GET_METHOD)
        handleGetCommands(cmd, argument);
    else if (method == POST_METHOD)
        handlePostCommands(cmd, argument);
    else if (method == PUT_METHOD)
        handlePutCommands(cmd ,argument);
    else if (method == DELETE_METHOD)
        handleDeleteCommands(cmd, argument);
    else
        throw invalid_argument(BAD_REQUEST_RESPONSE);
}

void System::parseArguments(const string& argument, vector<string>& expectedArguments) {
    arguments.clear();
    istringstream iss(argument);
    string token;

    while (iss >> token) {
        if (token == AMOUNT) {
            string value;
            iss >> value;
            arguments[token] = value;
        } else {
            iss >> ws;
            char c;
            iss.get(c);
            string value;
            getline(iss, value, ARGUMENT_DELIMITER);
            arguments[token] = value;
        }
    }
    for (const string& arg : expectedArguments) {
        if (arguments.count(arg) == 0)
            throw invalid_argument(BAD_REQUEST_RESPONSE);
    }
}



void System::handleGetCommands(const string& command, const string& argument) {
    if (command == DISTRICTS_COMMAND)
        uTasteGetDistricts(argument);
    else if (command == RESTAURANTS_COMMAND)
        uTasteGetRestaurants(argument);
    else if (command == RESTAURANT_DETAIL_COMMAND)
        uTasteGetRestaurantDetail(argument);
    else if (command == RESERVES_COMMAND)
        uTasteGetUserReserves(argument);
    else if (command == SHOW_BUDGET_COMMAND)
        uTasteShowUserBudget(argument);
    else
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

void System::handlePostCommands(const string& command, const string& argument) {
    if (command == SIGNUP_COMMAND)
        uTasteSignUp(argument);
    else if (command == LOGIN_COMMAND)
        uTasteLogin(argument);
    else if (command == LOGOUT_COMMAND)
        uTasteLogout(argument);
    else if (command == RESERVE_COMMAND)
        uTasteReserve(argument);
    else if (command == INCREASE_BUDGET_COMMAND)
        uTasteIncreaseUserBudget(argument);
    else
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

void System::handlePutCommands(const string& command, const string& argument) {
    if (command == MY_DISTRICT_COMMAND)
        uTasteSetLocation(argument);
    else
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

void System::handleDeleteCommands(const string &command, const string &argument) {
    if (command == RESERVE_COMMAND)
        uTasteDeleteReserve(argument);
    else
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
}

void System::uTasteSignUp(const string& argument) {
    vector<string> expectedArguments = {USERNAME, PASSWORD};
    parseArguments(argument, expectedArguments);
    uTaste->signUp(arguments[USERNAME], arguments[PASSWORD]);
}

void System::uTasteLogin(const string& argument) {
    vector<string> expectedArguments = {USERNAME, PASSWORD};
    parseArguments(argument, expectedArguments);
    uTaste->login(arguments[USERNAME], arguments[PASSWORD]);
}

void System::uTasteLogout(const string& argument) {
    vector<string> expectedArguments = {};
    parseArguments(argument, expectedArguments);
    uTaste->logout();
}

void System::uTasteGetDistricts(const string& argument) {
    vector<string> expectedArguments = {};
    parseArguments(argument, expectedArguments);
    if (arguments[DISTRICT].empty())
        uTaste->showDistricts();
    else
        uTaste->showSpecificDistrict(arguments[DISTRICT]);
}

void System::uTasteSetLocation(const string& argument) {
    vector<string> expectedArguments = {DISTRICT};
    parseArguments(argument, expectedArguments);
    uTaste->setUserLocation(arguments[DISTRICT]);
}

void System::uTasteGetRestaurants(const string& argument) {
    vector<string> expectedArguments = {};
    parseArguments(argument, expectedArguments);
    if (arguments[FOOD_NAME].empty())
        uTaste->showRestaurants();
    else
        uTaste->showSpecificRestaurants(arguments[FOOD_NAME]);
}

void System::uTasteGetRestaurantDetail(const string &argument) {
    vector<string> expectedArguments = {RESTAURANT_NAME};
    parseArguments(argument, expectedArguments);
    try {
        uTaste->districtsShowRestaurantDetail(arguments[RESTAURANT_NAME]);
    } catch (const invalid_argument& error) {
        throw invalid_argument(NON_EXISTENCE_RESPONSE);
    }
}

void System::uTasteReserve(const string &argument) {
    vector<string> expectedArguments = {RESTAURANT_NAME, TABLE_ID, START_TIME, END_TIME};
    parseArguments(argument, expectedArguments);
    uTaste->reserveTableInRestaurant(arguments[RESTAURANT_NAME] ,arguments[TABLE_ID], arguments[START_TIME], arguments[END_TIME], arguments[FOODS]);
}

void System::uTasteGetUserReserves(const string &argument) {
    vector<string> expectedArguments = {};
    parseArguments(argument, expectedArguments);
    uTaste->getUserReserves(arguments[RESTAURANT_NAME], arguments[RESERVE_ID]);
}

void System::uTasteDeleteReserve(const string &argument) {
    vector<string> expectedArguments = {RESTAURANT_NAME, RESERVE_ID};
    parseArguments(argument, expectedArguments);
    uTaste->deleteUserReserve(arguments[RESTAURANT_NAME], arguments[RESERVE_ID]);
}

void System::uTasteIncreaseUserBudget(const string &argument) {
    vector<string> expectedArguments = {AMOUNT};
    parseArguments(argument, expectedArguments);
    uTaste->increaseUserBudget(arguments[AMOUNT]);
}

void System::uTasteShowUserBudget(const string &argument) {
    vector<string> expectedArguments = {};
    parseArguments(argument, expectedArguments);
    uTaste->showUserBudget();
}
