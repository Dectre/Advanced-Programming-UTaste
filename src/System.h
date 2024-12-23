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

    vector<string> splitStringBy(const string &sentence, const char &delimiter);

    void inputWatcher();
    void inputSeperator(vector<string> command);
    void parseArguments(string argument, vector<string> &expectedArguments);

    void handleGetCommands(string command, string arguments);
    void handlePostCommands(string command, string arguments);

    void uTasteSignUp(string argument);
    void uTasteLogin(string argument);
    void uTasteLogout(string argument);
};

#endif //UTASTE_SYSTEM_H
