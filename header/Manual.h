#ifndef UTASTE_MANUAL_H
#define UTASTE_MANUAL_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <iomanip>


using namespace std;

typedef const string Method;
typedef const string Responses;
typedef const string Command;
typedef const string Argument;
typedef const string Output;
typedef const char Delimiter;
typedef const string Key;
typedef const string Type;

extern string RESTAURANTS_FILE;
extern string DISTRICTS_FILE;
extern string DISCOUNTS_FILE;

Key NAME_KEY = "Name";
Key PRICE_KEY = "Price";

Method GET_METHOD = "GET";
Method PUT_METHOD = "PUT";
Method POST_METHOD = "POST";
Method DELETE_METHOD = "DELETE";

Responses SUCCESSFUL_RESPONSE = "OK";
Responses EMPTY_RESPONSE = "Empty";
Responses NON_EXISTENCE_RESPONSE = "Not Found";
Responses BAD_REQUEST_RESPONSE = "Bad Request";
Responses UNABLE_TO_ACCESS_RESPONSE = "Permission Denied";

Command SIGNUP_COMMAND = "signup";
Command LOGIN_COMMAND = "login";
Command LOGOUT_COMMAND = "logout";
Command DISTRICTS_COMMAND = "districts";
Command MY_DISTRICT_COMMAND = "my_district";
Command RESTAURANTS_COMMAND = "restaurants";
Command RESTAURANT_DETAIL_COMMAND = "restaurant_detail";
Command RESERVE_COMMAND = "reserve";
Command RESERVES_COMMAND = "reserves";
Command INCREASE_BUDGET_COMMAND = "increase_budget";
Command SHOW_BUDGET_COMMAND = "show_budget";

Argument USERNAME = "username";
Argument PASSWORD = "password";
Argument DISTRICT = "district";
Argument FOOD_NAME = "food_name";
Argument RESTAURANT_NAME = "restaurant_name";
Argument TABLE_ID = "table_id";
Argument START_TIME = "start_time";
Argument END_TIME = "end_time";
Argument FOODS = "foods";
Argument RESERVE_ID = "reserve_id";
Argument AMOUNT = "amount";

Output NAME_OUTPUT = "Name";
Output DISTRICT_OUTPUT = "District";
Output TIME_OUTPUT = "Time";
Output MENU_OUTPUT = "Menu";
Output RESERVE_ID_OUTPUT = "Reserve ID";
Output TABLE_OUTPUT = "Table";
Output FOR_OUTPUT = "for";
Output TO_OUTPUT = "to";
Output IN_OUTPUT = "in";
Output PRICE_OUTPUT = "Price";
Output ORIGINAL_PRICE_OUTPUT = "Original Price";
Output TOTAL_ORDER_DISCOUNT_OUTPUT = "Order Amount Discount";
Output ITEM_SPECIFIC_DISCOUNT_OUTPUT = "Item Specific Discount";
Output FIRST_ORDER_DISCOUNT_OUTPUT = "First Order Discount";
Output TOTAL_ITEM_SPECIFIC_DISCOUNT_OUTPUT = "Total ItemSpecific Discount";
Output TOTAL_PRICE_OUTPUT = "Total Price";
Output TOTAL_DISCOUNT_OUTPUT = "Total Discount";

Delimiter COMMAND_DELIMITER = '?';
Delimiter ARGUMENT_DELIMITER = '"';
Delimiter SEPARATOR_DELIMITER = ',';
Delimiter ELEMENT_SEPARATOR_DELIMITER = ';';
Delimiter WORD_SEPARATOR_DELIMITER = ' ';
Delimiter EXPLANATION_DELIMITER = ':';
Delimiter IN_DELIMITER = '(';
Delimiter OUT_DELIMITER = ')';
Delimiter TO_DELIMITER = '-';
Delimiter FOOD_SEPERATOR_DELIMITER = '|';

Type byPERCENT = "percent";
Type PERCENTAGE = "percentage";
Type byAMOUNT = "amount";
Type NONE = "none";

const double returnRate = 0.6;

vector<string> splitStringBy(const string& sentence, const char& delimiter);
int safeStoi(const string& str);

#endif //UTASTE_MANUAL_H
