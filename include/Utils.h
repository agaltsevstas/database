#ifndef Utils_h
#define Utils_h

#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <codecvt>
#include <boost/algorithm/string.hpp>

using namespace std;

namespace utils
{
    inline char* toLower(char *input)
    {
        std::string str(input);
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        input = &str[0];
        return input;
    }
    
    inline vector<string> splitString(string source, string delim)
    {
        vector<string> result;
        
//        source.erase(remove(source.begin(), source.end(), ' '), source.end());
        boost::split(result, source, boost::is_any_of(delim));
        return result;
    }
    string date()
    {
        stringstream ss;
        auto t = time(nullptr);
        auto tm = *localtime(&t);
        ss << put_time(&tm, "%d.%m.%Y");
        
        return ss.str();
    }
    
    vector<uint> findAge(vector<string> &data, vector<string> &dateOfBirth)
    {
        uint currentDay = atoi(data[0].c_str());
        uint currentMonth = atoi(data[1].c_str());
        uint currentYear = atoi(data[2].c_str());
        uint birthDay = atoi(dateOfBirth[0].c_str());
        uint birthMonth = atoi(dateOfBirth[1].c_str());
        uint birthYear = atoi(dateOfBirth[2].c_str());
        
        int month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (birthDay > currentDay)
        {
            currentDay = currentDay + month[birthMonth - 1];
            currentMonth = currentMonth - 1;
        }
        if (birthMonth > currentMonth)
        {
            currentYear = currentYear - 1;
            currentMonth = currentMonth + 12;
        }
        uint calculatedDay = currentDay - birthDay;
        uint calculatedMonth = currentMonth - birthMonth;
        uint calculatedYear = currentYear - birthYear;
        vector<uint> age = { calculatedYear, calculatedMonth, calculatedDay };
        return age;
    }
    
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

    inline void toUpperAndToLower(string &str)
    {
        wstring wstr = utf8ToWstring(str);
        wstr[0] = towupper(wstr[0]);
        transform(wstr.begin() + 1, wstr.end(), wstr.begin() + 1, towlower);
        str = wstringToUtf8(wstr);
    }
}

#endif // Utils_h
