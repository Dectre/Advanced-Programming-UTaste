#include "System.h"

System::System(Taste *uTaste_) {
    uTaste = uTaste_;
    // uTaste->initFiles();
    running = true;
}

vector<string> System::splitStringBy(const string& sentence, const char& delimiter) {
    vector<string> words;
    istringstream stream(sentence);
    string word;
    while(getline(stream, word, delimiter))
        words.push_back(word);
    return words;
}

void System::run() {
    try {
        inputWatcher();
    }catch (invalid_argument& err) {
        cout << err.what() << endl;
    }
}

void System::inputWatcher() {
    while (running) {
        string line;
        getline(cin, line);

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
    vector<string> mainCommands = splitStringBy(command[0], WORD_SEPERATOR_DELIMITER);
    if (mainCommands.size() != 2)
        throw invalid_argument(BAD_REQUEST_RESPONSE);

    string method = mainCommands[0];
    string cmd = mainCommands[1];
    string arguments = command.size() == 2 ? command[1] : "";

    if (method == POST_METHOD)
        handlePostCommands(cmd, arguments);
    else
        throw invalid_argument(BAD_REQUEST_RESPONSE);
}

void System::parseArguments(string argument, vector<string> &expectedArguments) {
    arguments.clear();
    vector<string> tokens = splitStringBy(argument, WORD_SEPERATOR_DELIMITER);
    for (size_t i = 0; i < tokens.size(); i++) {
        if (i + 1 < tokens.size() && tokens[i + 1][0] == ARGUMENT_DELIMITER) {
            string key = tokens[i];
            string value = tokens[i + 1].substr(1, tokens[i + 1].size() - 2);
            arguments[key] = value;
            i++;
        }
    }
    for (const string& arg : expectedArguments) {
        if (arguments.count(arg) == 0)
            throw invalid_argument(BAD_REQUEST_RESPONSE);
    }
}


void System::handleGetCommands(string command, string argument) {
}

void System::handlePostCommands(string command, string arguments) {
    if (command == SIGNUP_COMMAND)
        uTasteSignUp(arguments);
    else if (command == LOGIN_COMMAND)
        uTasteLogin(arguments);
    else if (command == LOGOUT_COMMAND)
        uTasteLogout(arguments);
    else
        throw invalid_argument(BAD_REQUEST_RESPONSE);
}

void System::uTasteSignUp(string argument) {
    vector<string> expectedArguments = {USERNAME, PASSWORD};
    parseArguments(argument, expectedArguments);
    uTaste->signUp(arguments[USERNAME], arguments[PASSWORD]);
}

void System::uTasteLogin(string argument) {
    vector<string> expectedArguments = {USERNAME, PASSWORD};
    parseArguments(argument, expectedArguments);
    uTaste->login(arguments[USERNAME], arguments[PASSWORD]);
}

void System::uTasteLogout(string argument) {
    vector<string> expectedArguments = {};
    parseArguments(argument, expectedArguments);
    uTaste->logout();
}
