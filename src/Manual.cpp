#include "Manual.h"

vector<string> splitStringBy(const string& sentence, const char& delimiter) {
    vector<string> words;
    istringstream stream(sentence);
    string word;
    while(getline(stream, word, delimiter))
        words.push_back(word);
    return words;
}