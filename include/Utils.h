#ifndef Utils_h
#define Utils_h

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <codecvt>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace utils
{
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
