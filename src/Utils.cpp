#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "Utils.h"

using namespace boost::filesystem;

namespace utils
{

    string getNameWithoutExtension(const string &filePath)
    {
        path fileName(filePath);
        return fileName.stem().c_str();
    }

    string translit(const string &textRussian)
    {
        string textEnglish;
        for (size_t i = 0; i <= textRussian.length(); ++i)
        {
            char space = textRussian[i];
            string letter = textRussian.substr(i, 2);
            if (space == ' ')
                        textEnglish += " ";
            else if (translitSymbols.find(letter) != translitSymbols.end())
            {
                textEnglish += translitSymbols.find(letter)->second;
            }
        }
        return textEnglish;
    }
    
    string createEmail(const vector<string> &anthroponym)
    {
        string email;
        for (auto part: anthroponym)
        {
            toUpperAndToLower(part, 0);
            email += translit(part) + ".";
        }
        email.pop_back();
        return email += "@tradingcompany.ru";
    }
    
    vector<string> splitString(string source, string delim)
    {
        vector<string> result;

        source.erase(remove(source.begin(), source.end(), ' '), source.end());
        boost::split(result, source, boost::is_any_of(delim));
        return result;
    }

    string date()
    {
        stringstream ss;
        time_t t = std::time(nullptr);
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

    void toUpperAndToLower(string &str, uint numberUpper)
    {
        for (size_t i = 0; i < numberUpper; ++i)
        {
            toupper(str[i]);
        }
        wstring wstr = utf8ToWstring(str);
        wstr[0] = towupper(wstr[0]);
        transform(wstr.begin() + numberUpper, wstr.end(), wstr.begin() + numberUpper, towlower);
        str = wstringToUtf8(wstr);
    }
}
