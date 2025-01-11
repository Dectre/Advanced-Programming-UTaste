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

SearchFormHandler::SearchFormHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

Response* SearchFormHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    string errorMessage = req->getQueryParam("error");
    ifstream file("static/search.html");
    if (!file.is_open()) {
        throw Server::Exception("Could not open search.html");
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string html = buffer.str();
    if (!errorMessage.empty()) {
        size_t errorPos = html.find("</body>");
        if (errorPos != string::npos) {
            string errorHtml = "<p style='color: red;'>" + errorMessage + "</p>";
            html.insert(errorPos, errorHtml);
        }
    }
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(html);
    return res;
}

SearchHandler::SearchHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

Response* SearchHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    string restaurantName = req->getBodyParam("restaurant_name");
    // Encode the restaurant name for URL
    string encodedRestaurantName;
    for (char c : restaurantName) {
        if (c == ' ') {
            encodedRestaurantName += "%20";
        } else if (c == '&') {
            encodedRestaurantName += "%26";
        } else {
            encodedRestaurantName += c;
        }
    }
    Restaurant* restaurant = uTaste->findRestaurantByName(restaurantName);
    if (restaurant) {
        string redirectUrl = "/restaurant?name=" + encodedRestaurantName;
        return Response::redirect(redirectUrl);
    } else {
        string errorMessage = "Restaurant not found.";
        string redirectUrl = "/search?error=" + errorMessage;
        return Response::redirect(redirectUrl);
    }
}

RestaurantHandler::RestaurantHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

std::string urlDecode(const std::string& str) {
    std::string result;
    char ch;
    int i, j;
    for (i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &j);
            ch = static_cast<char>(j);
            result += ch;
            i += 2;
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

Response* RestaurantHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    string restaurantName = req->getQueryParam("name");
    if (restaurantName.empty()) {
        return Response::redirect("/search");
    }

    // Decode the restaurant name
    restaurantName = urlDecode(restaurantName);

    Restaurant* restaurant = uTaste->findRestaurantByName(restaurantName);
    if (restaurant && restaurant->getName() == restaurantName) {
        ifstream file("static/restaurant.html");
        if (!file.is_open()) {
            throw Server::Exception("Could not open restaurant.html");
        }

        // خواندن کل فایل HTML
        stringstream buffer;
        buffer << file.rdbuf();
        string html = buffer.str();

        // جای‌گذاری اطلاعات رستوران
        html.replace(html.find("RESTAURANT_NAME_PLACEHOLDER"), strlen("RESTAURANT_NAME_PLACEHOLDER"), restaurant->getName());
        html.replace(html.find("DISTRICT_PLACEHOLDER"), strlen("DISTRICT_PLACEHOLDER"), restaurant->getLocation()->getName());
        html.replace(html.find("OPENING_TIME_PLACEHOLDER"), strlen("OPENING_TIME_PLACEHOLDER"), to_string(restaurant->getOpeningTime()));
        html.replace(html.find("CLOSING_TIME_PLACEHOLDER"), strlen("CLOSING_TIME_PLACEHOLDER"), to_string(restaurant->getClosingTime()));

        // جای‌گذاری منو
        string menuItems;
        for (const auto& food : restaurant->getMenu()) {
            menuItems += "<div class='menu-item'>";
            menuItems += "<img src='dish.png' alt='" + food->getName() + "'>";
            menuItems += "<div class='menu-item-details'>";
            menuItems += "<h3>" + food->getName() + "</h3>";
            menuItems += "<p>Price: " + to_string(food->getPrice()) + " Toman</p>";
            if (food->getDiscount()) {
                string disType = food->getDiscount()->getType() == "amount" ? " Toman" : "%";
                menuItems += "<p class='discount-info'>Discount: " + to_string(food->getDiscount()->getValue()) + disType + "</p>";
            }
            menuItems += "</div></div>";
        }
        html.replace(html.find("MENU_ITEMS_PLACEHOLDER"), strlen("MENU_ITEMS_PLACEHOLDER"), menuItems);

        // جای‌گذاری رزروها
        string reservations;
        for (const auto& table : restaurant->getTables()) {
            reservations += "<li>Table " + to_string(table->getId()) + ": ";
            if (table->getReserves().empty()) {
                reservations += "-";
            } else {
                for (const auto& reserve : table->getReserves()) {
                    reservations += to_string(reserve->getStartTime())  + ", ";
                }
                reservations.pop_back(); // حذف کامای آخر
                reservations.pop_back();
            }
            reservations += "</li>";
        }
        html.replace(html.find("RESERVATIONS_PLACEHOLDER"), strlen("RESERVATIONS_PLACEHOLDER"), reservations);

        // جای‌گذاری تخفیف‌ها
        string orderDiscount = "-";
        if (restaurant->getTotalPriceDiscount()) {
            orderDiscount = to_string(restaurant->getTotalPriceDiscount()->getValue()) +
                            (restaurant->getTotalPriceDiscount()->getType() == "amount" ? " Toman" : "%") +
                            " Minimum: " + to_string(restaurant->getTotalPriceDiscount()->getMinimum()) + " Toman";
        }
        html.replace(html.find("ORDER_DISCOUNT_PLACEHOLDER"), strlen("ORDER_DISCOUNT_PLACEHOLDER"), orderDiscount);

        string firstOrderDiscount = "-";
        if (restaurant->getFirstOrderDiscount()) {
            firstOrderDiscount = to_string(restaurant->getFirstOrderDiscount()->getValue()) +
                                 (restaurant->getFirstOrderDiscount()->getType() == "amount" ? " Toman" : "%");
        }
        html.replace(html.find("FIRST_ORDER_DISCOUNT_PLACEHOLDER"), strlen("FIRST_ORDER_DISCOUNT_PLACEHOLDER"), firstOrderDiscount);

        // ایجاد پاسخ
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(html);
        return res;
    } else {
        string errorMessage = "Restaurant not found.";
        string redirectUrl = "/search?error=" + errorMessage;
        return Response::redirect(redirectUrl);
    }
}