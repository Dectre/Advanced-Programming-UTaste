#include "Taste.h"
#include "User.h"


 Taste::Taste() {}
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
