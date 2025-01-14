#include "handlers.hpp"
#include <iostream>

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
    if (this->uTaste->getCurrentUser() != nullptr)
        return Response::redirect("/");
    else
        return Response::redirect("/register-page");
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
    if (this->uTaste->getCurrentUser() != nullptr) {
        return Response::redirect("/");
    }
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    try {
        this->uTaste->login(username, password);
        Response* res = Response::redirect("/");
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
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == '%') {
            unsigned int j;
            sscanf(str.substr(i + 1, 2).c_str(), "%x", &j);
            result += static_cast<char>(j);
            i += 2;
        }
        else if (str[i] == '+') result += ' ';
        else result += str[i];
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
    restaurantName = urlDecode(restaurantName);
    Restaurant* restaurant = uTaste->findRestaurantByName(restaurantName);
    if (restaurant && restaurant->getName() == restaurantName) {
        ifstream file("static/restaurant.html");
        if (!file.is_open()) {
            throw Server::Exception("Could not open restaurant.html");
        }
        stringstream buffer;
        buffer << file.rdbuf();
        string html = buffer.str();
        html.replace(html.find("RESTAURANT_NAME_PLACEHOLDER"), strlen("RESTAURANT_NAME_PLACEHOLDER"), restaurant->getName());
        html.replace(html.find("DISTRICT_PLACEHOLDER"), strlen("DISTRICT_PLACEHOLDER"), restaurant->getLocation()->getName());
        html.replace(html.find("OPENING_TIME_PLACEHOLDER"), strlen("OPENING_TIME_PLACEHOLDER"), to_string(restaurant->getOpeningTime()));
        html.replace(html.find("CLOSING_TIME_PLACEHOLDER"), strlen("CLOSING_TIME_PLACEHOLDER"), to_string(restaurant->getClosingTime()));
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
        string reservations;
        for (const auto& table : restaurant->getTables()) {
            reservations += "<li>Table " + to_string(table->getId()) + ": ";
            if (table->getReserves().empty()) {
                reservations += "-";
            } else {
                for (const auto& reserve : table->getReserves()) {
                    reservations += "(" + to_string(reserve->getStartTime())  + "-" + to_string(reserve->getEndTime()) + ")" ", ";
                }
                reservations.pop_back();
                reservations.pop_back();
            }
            reservations += "</li>";
        }
        html.replace(html.find("RESERVATIONS_PLACEHOLDER"), strlen("RESERVATIONS_PLACEHOLDER"), reservations);
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

Response* ReserveHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    string restaurantName = req->getBodyParam("restaurant_name");
    string tableId = req->getBodyParam("table_id");
    string startTime = req->getBodyParam("start_time");
    string endTime = req->getBodyParam("end_time");
    string foods = req->getBodyParam("foods");
    if (restaurantName.empty() || tableId.empty() || startTime.empty() || endTime.empty()) {
        string errorMessage = "All fields except 'foods' are required.";
        string redirectUrl = "/reserve_form?error=" + errorMessage;
        return Response::redirect(redirectUrl);
    }
    try {
        Reserve* reserve = uTaste->reserveTableInRestaurant(restaurantName, tableId, startTime, endTime, foods);
        int ID = reserve->getID();
        string redirectUrl = "/reserve?ID=" + to_string(ID) + "&name=" + restaurantName;
        return Response::redirect(redirectUrl);
    } catch (const invalid_argument& e) {
        string errorMessage = e.what();
        string redirectUrl = "/reserve_form?error=" + errorMessage;
        return Response::redirect(redirectUrl);
    }
}

Response* ReserveConfirmationHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    string reservationID = req->getQueryParam("ID");
    string restaurantName = req->getQueryParam("name");
    if (reservationID.empty() || restaurantName.empty()) {
        return Response::redirect("/reserve_form?error=Reservation%20ID%20or%20restaurant%20name%20is%20missing.");
    }
    try {
        Reserve* reserve = currentUser->showReserve(restaurantName, reservationID);
        if (!reserve) {
            throw invalid_argument("Reservation not found.");
        }
        Restaurant* restaurant = uTaste->findRestaurantByName(restaurantName);
        if (!restaurant) {
            throw invalid_argument("Restaurant not found.");
        }
        ifstream file("static/reserve.html");
        if (!file.is_open()) {
            throw Server::Exception("Could not open reserve.html");
        }
        stringstream buffer;
        buffer << file.rdbuf();
        string html = buffer.str();
        html.replace(html.find("RESTAURANT_NAME_PLACEHOLDER"), strlen("RESTAURANT_NAME_PLACEHOLDER"), restaurant->getName());
        html.replace(html.find("DISTRICT_PLACEHOLDER"), strlen("DISTRICT_PLACEHOLDER"), restaurant->getLocation()->getName());
        string orderedFoods;
        for (const auto& food : reserve->getOrder()) {
            orderedFoods += "<div class='menu-item'>";
            orderedFoods += "<img src='dish.png' alt='" + food->getName() + "'>";
            orderedFoods += "<div class='menu-item-details'>";
            orderedFoods += "<h3>" + food->getName() + "</h3>";
            orderedFoods += "<p>Price: " + to_string(food->getPrice()) + " Toman</p>";
            if (food->getDiscount()) {
                string disType = food->getDiscount()->getType() == "amount" ? " Toman" : "%";
                orderedFoods += "<p class='discount-info'>Discount: " + to_string(food->getDiscount()->getValue()) + disType + "</p>";
            }
            orderedFoods += "</div></div>";
        }
        html.replace(html.find("MENU_ITEMS_PLACEHOLDER"), strlen("MENU_ITEMS_PLACEHOLDER"), orderedFoods);
        html.replace(html.find("TABLE_ID_PLACEHOLDER"), strlen("TABLE_ID_PLACEHOLDER"), to_string(reserve->getTable()->getId()));
        html.replace(html.find("START_TIME_PLACEHOLDER"), strlen("START_TIME_PLACEHOLDER"), to_string(reserve->getStartTime()));
        html.replace(html.find("END_TIME_PLACEHOLDER"), strlen("END_TIME_PLACEHOLDER"), to_string(reserve->getEndTime()));
        html.replace(html.find("ORIGINAL_PRICE_PLACEHOLDER"), strlen("ORIGINAL_PRICE_PLACEHOLDER"), to_string(reserve->getPriceBeforeDiscount()));
        html.replace(html.find("ORDER_AMOUNT_DISCOUNT_PLACEHOLDER"), strlen("ORDER_AMOUNT_DISCOUNT_PLACEHOLDER"), to_string(reserve->getDiscounts()[2]));
        html.replace(html.find("ITEM_SPECIFIC_DISCOUNT_PLACEHOLDER"), strlen("ITEM_SPECIFIC_DISCOUNT_PLACEHOLDER"), to_string(reserve->getDiscounts()[0]));
        html.replace(html.find("FIRST_ORDER_DISCOUNT_PLACEHOLDER"), strlen("FIRST_ORDER_DISCOUNT_PLACEHOLDER"), to_string(reserve->getDiscounts()[1]));
        html.replace(html.find("TOTAL_DISCOUNT_PLACEHOLDER"), strlen("TOTAL_DISCOUNT_PLACEHOLDER"), to_string(reserve->getTotalDiscount()));
        html.replace(html.find("TOTAL_PRICE_PLACEHOLDER"), strlen("TOTAL_PRICE_PLACEHOLDER"), to_string(reserve->getPriceAfterDiscount()));
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(html);
        return res;
    } catch (const invalid_argument& e) {
        stringstream html;
        html << "<!DOCTYPE html>\n";
        html << "<html>\n";
        html << "<head>\n";
        html << "<title>Error</title>\n";
        html << "<link href='https://fonts.googleapis.com/css2?family=Raleway:wght@400;600&display=swap' rel='stylesheet'>\n";
        html << "<style>\n";
        html << "body { font-family: 'Raleway', sans-serif; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; color: #333; background: linear-gradient(135deg, #d4af37, #f9d976); }\n";
        html << ".error-container { background: rgba(255, 255, 255, 0.9); padding: 30px; border-radius: 12px; box-shadow: 0 4px 10px rgba(0, 0, 0, 0.2); text-align: center; }\n";
        html << "h1 { color: #ff4444; font-size: 2.5vw; margin-bottom: 20px; }\n";
        html << "</style>\n";
        html << "</head>\n";
        html << "<body>\n";
        html << "<div class='error-container'>\n";
        html << "<h1>Error</h1>\n";
        html << "<p>" << e.what() << "</p>\n";
        html << "</div>\n";
        html << "</body>\n";
        html << "</html>\n";
        Response* res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(html.str());
        return res;
    }
}

ReserveConfirmationHandler::ReserveConfirmationHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

ReserveHandler::ReserveHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}

Response* ShowReservesHandler::callback(Request* req) {
    User* currentUser = this->uTaste->getCurrentUser();
    if (currentUser == nullptr) {
        return Response::redirect("/register");
    }
    string restaurantName = req->getQueryParam("restaurant_name");
    string reservationID = req->getQueryParam("reservation_id");
    if (!reservationID.empty() && restaurantName.empty()) {
        string errorMessage = "Restaurant name is required when reservation ID is provided.";
        return Response::redirect("/show_reserves?error=" + errorMessage);
    }
    vector<Reserve*> reservations;
    string errorMessage;

    if (restaurantName.empty() && reservationID.empty())
        reservations = currentUser->getReserves();
    else if (!restaurantName.empty() && reservationID.empty()) {
        reservations = currentUser->getSpecificRestaurantReserves(restaurantName);
        if (reservations.empty())
            errorMessage = "No reservations found for the specified restaurant.";
    } else if (!restaurantName.empty() && !reservationID.empty()) {
        try {
            Reserve* reserve = currentUser->showReserve(restaurantName, reservationID);
            if (reserve) {
                reservations.push_back(reserve);
            } else {
                errorMessage = "Reservation not found.";
            }
        } catch (const std::exception& e) {
            errorMessage = e.what();
        }
    }
    ifstream file("static/show_reserves.html");
    if (!file.is_open()) throw Server::Exception("Could not open show_reserves.html");
    stringstream buffer;
    buffer << file.rdbuf();
    string html = buffer.str();
    string reservesList;
    if (reservations.empty()) {
        reservesList = "<p>No reservations found.</p>";
    } else {
        for (const auto& reserve : reservations) {
            reservesList += "<div class='reserve-item'>";
            reservesList += "<h3>Restaurant: " + reserve->getTable()->getRestaurant()->getName() + "</h3>";
            reservesList += "<p>Reservation ID: " + to_string(reserve->getID()) + "</p>";
            reservesList += "<p>Table: " + to_string(reserve->getTable()->getId()) + "</p>";
            reservesList += "<p>Time: " + to_string(reserve->getStartTime()) + " - " + to_string(reserve->getEndTime()) + "</p>";
            reservesList += "<a href='/reserve?ID=" + to_string(reserve->getID()) + "&name=" + reserve->getTable()->getRestaurant()->getName() + "'>View Details</a>";
            reservesList += "</div>";
        }
    }
    html.replace(html.find("RESERVES_LIST_PLACEHOLDER"), strlen("RESERVES_LIST_PLACEHOLDER"), reservesList);
    string queryErrorMessage = req->getQueryParam("error");
    if (!queryErrorMessage.empty()) errorMessage = queryErrorMessage;
    if (!errorMessage.empty()) html.replace(html.find("ERROR_MESSAGE_PLACEHOLDER"), strlen("ERROR_MESSAGE_PLACEHOLDER"), "<p style='color: red;'>" + errorMessage + "</p>");
    else html.replace(html.find("ERROR_MESSAGE_PLACEHOLDER"), strlen("ERROR_MESSAGE_PLACEHOLDER"), "");
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(html);
    return res;
}

ShowReservesHandler::ShowReservesHandler(Taste *uTaste_) {
    this->uTaste = uTaste_;
}