#include "../header/Manual.h"

vector<string> splitStringBy(const string& sentence, const char& delimiter) {
    vector<string> words;
    istringstream stream(sentence);
    string word;
    while(getline(stream, word, delimiter))
        words.push_back(word);
    return words;
}

int safeStoi(const string& str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        throw invalid_argument(BAD_REQUEST_RESPONSE);
    } catch (const out_of_range& e) {
        throw invalid_argument(BAD_REQUEST_RESPONSE);
    }
}
