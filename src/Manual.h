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


using namespace std;

typedef const string Method;
typedef const string Response;
typedef const string Command;
typedef const string Argument;
typedef const string Output;
typedef const char Delimiter;
typedef const string Key;

extern string RESTAURANTS_FILE;
extern string DISTRICTS_FILE;

Key NAME_KEY = "Name";
Key PRICE_KEY = "Price";

Method GET_METHOD = "GET";
Method PUT_METHOD = "PUT";
Method POST_METHOD = "POST";
Method DELETE_METHOD = "DELETE";

Response SUCCESSFUL_RESPONSE = "OK";
Response EMPTY_RESPONSE = "Empty";
Response NON_EXISTENCE_RESPONSE = "Not Found";
Response BAD_REQUEST_RESPONSE = "Bad Request";
Response UNABLE_TO_ACCESS_RESPONSE = "Permission Denied";

Command SIGNUP_COMMAND = "signup";
Command LOGIN_COMMAND = "login";
Command LOGOUT_COMMAND = "logout";
Command DISTRICTS_COMMAND = "districts";
Command MY_DISTRICT_COMMAND = "my_district";
Command RESTAURANTS_COMMAND = "restaurants";
Command RESTAURANT_DETAIL_COMMAND = "restaurant_detail";
Command RESERVE_COMMAND = "reserve";
Command RESERVES_COMMAND = "reserves";

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

Delimiter COMMAND_DELIMITER = '?';
Delimiter ARGUMENT_DELIMITER = '"';
Delimiter SEPARATOR_DELIMITER = ',';
Delimiter ELEMENT_SEPARATOR_DELIMITER = ';';
Delimiter WORD_SEPARATOR_DELIMITER = ' ';
Delimiter EXPLANATION_DELIMITER = ':';
Delimiter IN_DELIMITER = '(';
Delimiter OUT_DELIMITER = ')';
Delimiter TO_DELIMITER = '-';

vector<string> splitStringBy(const string& sentence, const char& delimiter);
#endif //UTASTE_MANUAL_H
