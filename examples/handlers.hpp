#ifndef HANDLERS_HPP_INCLUDE
#define HANDLERS_HPP_INCLUDE

#include <map>
#include <string>
#include <iostream>
#include "../header/Taste.h"

#include "../server/server.hpp"

class HomePageHandler : public RequestHandler {
public:
    HomePageHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class RegisterHandler : public RequestHandler {
public:
    RegisterHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class Search : public RequestHandler {
public:
    Search(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class SignupHandler : public RequestHandler {
public:
    SignupHandler(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class SearchResult : public RequestHandler {
public:
    SearchResult(Taste* uTaste_);
    Response* callback(Request*);
private:
    Taste* uTaste;
};

class SearchFormHandler : public RequestHandler {
public:
    SearchFormHandler(Taste* uTaste_);
    Response* callback(Request* req);
private:
    Taste* uTaste;
};

class SearchHandler : public RequestHandler {
public:
    SearchHandler(Taste* uTaste_);
    Response* callback(Request* req) override;
private:
    Taste* uTaste;
};

class RestaurantHandler : public RequestHandler {
public:
    RestaurantHandler(Taste* uTaste_);
    Response* callback(Request* req);
private:
    Taste* uTaste;
};

class ReserveHandler : public RequestHandler {
public:
    ReserveHandler(Taste* uTaste_);
    Response* callback(Request* req);
private:
    Taste* uTaste;
};

class ReserveConfirmationHandler : public RequestHandler {
public:
    ReserveConfirmationHandler(Taste* uTaste_);
    Response* callback(Request* req);
private:
    Taste* uTaste;
};

#endif // HANDLERS_HPP_INCLUDE
