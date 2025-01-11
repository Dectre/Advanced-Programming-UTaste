#include "handlers.hpp"

#include <iostream>

// handlers.cpp
#include "handlers.hpp"

Response* HomePageHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    ifstream file("static/home.html");
    if (!file.is_open()) {
        throw Server::Exception("Could not open home.html");
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string html = buffer.str();
    cout << "HTML before replacement:\n" << html << endl;
    string username = currentUser->getUsername();
    size_t placeholder_pos = html.find("USERNAME_PLACEHOLDER");
    if (placeholder_pos != string::npos) {
        html.replace(placeholder_pos, strlen("USERNAME_PLACEHOLDER"), username);
    }
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(html);

    return res;
}

HomePageHandler::HomePageHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

Response* RegisterHandler::callback(Request* req) {
    if (this->uTaste->getCurrentUser() != nullptr) {
        return Response::redirect("/home");
    } else {
        return Response::redirect("/register-page");
    }
}

RegisterHandler::RegisterHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

Response* SignupHandler::callback(Request* req) {
    if (this->uTaste->getCurrentUser() != nullptr) {
        return Response::redirect("/");
    }
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try {
        this->uTaste->signUp(username, password);
        Response* res = Response::redirect("/");
        res->setSessionId(username);
        return res;
    } catch (invalid_argument& err) {
        string errorMessage = "This username already exists.";
        string redirectUrl = "/signup?error=" + errorMessage;
        return Response::redirect(redirectUrl);
    }
}

SignupHandler::SignupHandler(Taste* uTaste_) {
    this->uTaste = uTaste_;
}

Response* LoginHandler::callback(Request* req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");

    try {
        this->uTaste->login(username, password);
        Response* res = Response::redirect("/home");
        res->setSessionId(username);
        return res;
    } catch (invalid_argument& err) {
        string errorMessage = "Incorrect username or password.";
        if (err.what() == NON_EXISTENCE_RESPONSE) {
            errorMessage = "User does not exist.";
        }
        string redirectUrl = "/login?error=" + errorMessage;
        return Response::redirect(redirectUrl);
    }
}

LoginHandler::LoginHandler(Taste* uTaste_) {
    this->uTaste = uTaste_;
}

Response* LogoutHandler::callback(Request* req) {
    this->uTaste->logout();
    return Response::redirect("/register");
}

LogoutHandler::LogoutHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}
