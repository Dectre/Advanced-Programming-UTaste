#include <iostream>
#include <string>

#include "../server/server.hpp"
#include "handlers.hpp"
#include "../header/Taste.h"

string RESTAURANTS_FILE;
string DISTRICTS_FILE;
string DISCOUNTS_FILE;

void mapServerPaths(Server& server, Taste& uTaste) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new HomePageHandler(&uTaste));
    server.get("/home", new HomePageHandler(&uTaste));
    server.get("/register", new RegisterHandler(&uTaste));
    server.get("/register-page", new ShowPage("static/register.html"));
    server.get("/uTaste.png", new ShowImage("static/uTaste.png"));
    server.get("/signup", new ShowPage("static/signup.html"));
    server.post("/signup", new SignupHandler(&uTaste));
    server.get("/login", new ShowPage("static/login.html"));
    server.post("/login", new LoginHandler(&uTaste));
    server.get("/logout", new LogoutHandler(&uTaste));
}

int main(int argc, char** argv) {
    try {
        int port = std::stoi(argv[1]);
        Server server(port);
        Taste uTaste;
        RESTAURANTS_FILE = argv[2];
        DISTRICTS_FILE = argv[3];
        DISCOUNTS_FILE = argv[4];
        mapServerPaths(server, uTaste);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}
