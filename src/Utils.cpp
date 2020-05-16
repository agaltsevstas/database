#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "Utils.h"

namespace utils
{
    std::string getNameWithoutExtension(const std::string &filePath)
    {
        boost::filesystem::path fileName(filePath);
        return fileName.stem().c_str();
    }

    std::string translit(const std::string &textRussian)
    {
        std::string textEnglish;
        for (size_t i = 0; i <= textRussian.length(); ++i)
        {
            char space = textRussian[i];
            std::string letter = textRussian.substr(i, 2);
            if (space == ' ')
                        textEnglish += " ";
            else if (translitSymbols.find(letter) != translitSymbols.end())
            {
                textEnglish += translitSymbols.find(letter)->second;
            }
        }
        return textEnglish;
    }
    
    std::string createEmail(const std::vector<std::string> &anthroponym)
    {
        std::string email;
        for (auto part: anthroponym)
        {
            toupperandtolower(part, 0);
            email += translit(part) + ".";
        }
        email.pop_back();
        return email += "@tradingcompany.ru";
    }
    
    std::vector<std::string> splitString(std::string source, std::string delim)
    {
        std::vector<std::string> result;

        source.erase(remove(source.begin(), source.end(), ' '), source.end());
        boost::split(result, source, boost::is_any_of(delim));
        return result;
    }

    std::string date()
    {
        std::stringstream ss;
        time_t t = std::time(nullptr);
        auto tm = *localtime(&t);
        ss << std::put_time(&tm, "%d.%m.%Y");
        return ss.str();
    }

    std::vector<uint> findAge(std::vector<std::string> &data, std::vector<std::string> &dateOfBirth)
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
        std::vector<uint> age = { calculatedYear, calculatedMonth, calculatedDay };
        return age;
    }

    std::string toUpperAndToLower(std::string str, uint numberUpper)
    {
        for (size_t i = 0; i < numberUpper; ++i)
        {
            toupper(str[i]);
        }
        std::wstring wstr = utf8ToWstring(str);
        wstr[0] = towupper(wstr[0]);
        transform(wstr.begin() + numberUpper, wstr.end(), wstr.begin() + numberUpper, std::towlower);
        str = wstringToUtf8(wstr);
        return str;
    }

    void toupperandtolower(std::string &str, uint numberUpper)
    {
        if (str.empty())
        {
            return;
        }
        for (size_t i = 0; i < numberUpper; ++i)
        {
            toupper(str[i]);
        }
        std::wstring wstr = utf8ToWstring(str);
        wstr[0] = towupper(wstr[0]);
        transform(wstr.begin() + numberUpper, wstr.end(), wstr.begin() + numberUpper, std::towlower);
        str = wstringToUtf8(wstr);
    }
}
