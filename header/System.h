#ifndef UTASTE_SYSTEM_H
#define UTASTE_SYSTEM_H

#include "Manual.h"
#include "Taste.h"
#include "User.h"

class System {
public:
    System(Taste *uTaste_);
    void run();

private:
    Taste *uTaste;
    unordered_map<string, string> arguments;
    bool running;

    void inputWatcher();
    void inputSeperator(vector<string> command);
    void parseArguments(const string& argument, vector<string> &expectedArguments);

    void handleGetCommands(const string& command, const string& argument);
    void handlePostCommands(const string& command, const string& argument);
    void handlePutCommands(const string& command, const string& argument);
    void handleDeleteCommands(const string& command, const string& argument);

    void initFiles();
    void handleDistrictsFile();
    void handleRestaurantsFile();
    vector<map<string, string>> handleFood(const string& menu);
    void handleDiscountsFile();
    vector<map<string, string>> handleFoodDiscounts(const string& foods);

    void uTasteSignUp(const string& argument);
    void uTasteLogin(const string& argument);
    void uTasteLogout(const string& argument);

    void uTasteGetDistricts(const string& argument);
    void uTasteSetLocation(const string& argument);

    void uTasteGetRestaurants(const string& argument);
    void uTasteGetRestaurantDetail(const string& argument);

    void uTasteReserve(const string& argument);

    void uTasteGetUserReserves(const string& argument);

    void uTasteDeleteReserve(const string& argument);
};

#endif //UTASTE_SYSTEM_H
