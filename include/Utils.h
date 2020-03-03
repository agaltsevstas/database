#ifndef Utils_h
#define Utils_h

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <codecvt>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace utils
{
    const map<string, string> translitSymbols =
    {
        {"а", "a"},
        {"б", "b"},
        {"в", "v"},
        {"г", "g"},
        {"д", "d"},
        {"е", "e"},
        {"ё", "e"},
        {"ж", "zh"},
        {"з", "z"},
        {"и", "i"},
        {"й", "j"},
        {"к", "k"},
        {"л", "l"},
        {"м", "m"},
        {"н", "n"},
        {"о", "o"},
        {"п", "p"},
        {"р", "r"},
        {"с", "s"},
        {"т", "t"},
        {"у", "u"},
        {"ф", "f"},
        {"х", "h"},
        {"ц", "ts"},
        {"ч", "ch"},
        {"ш", "sh"},
        {"щ", "sch"},
        {"ъ", ""},
        {"ы", "j"},
        {"ь", ""},
        {"э", "e"},
        {"ю", "ju"},
        {"я", "ja"},
    };
    
    string translit(const string& ru_word);
    
    inline unsigned constexpr str(const char *input)
    {
        return *input ? static_cast<unsigned int>(*input) + 33 * str(input + 1) : 5381;
    }

    inline void toLower(string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    vector<string> splitString(string source, string delim);

    string date();
    
    vector<uint> findAge(vector<string> &data, vector<string> &dateOfBirth);

    // convert wstring to UTF-8 string
    inline string wstringToUtf8(const wstring &str)
    {
        wstring_convert<codecvt_utf8<wchar_t>> convert;
        return convert.to_bytes(str);
    }

    // convert UTF-8 string to wstring
    inline wstring utf8ToWstring(const string &str)
    {
        wstring_convert<codecvt_utf8<wchar_t>> convert;
        return convert.from_bytes(str);
    }

    void toUpperAndToLower(string &str);
}

#endif // Utils_h
