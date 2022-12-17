#pragma once
#include "commons.h"


vector<string> split(const string& s, const string& delimiter) {
    vector<string> elements;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter, pos)) != string::npos) {
        token = s.substr(0, pos);
        elements.push_back(token);
        pos += delimiter.length();
    }
    elements.push_back(s.substr(pos));
    return elements;
}