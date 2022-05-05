#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "Utils.h"

namespace utils
{
    std::string translit(const std::string &textCyrillic)
    {
        std::string textLatin;
        for (size_t i = 0; i <= textCyrillic.length(); ++i)
        {
            char space = textCyrillic[i];
            std::string letter = textCyrillic.substr(i, 2); // Кириллица = 2 байта
            // Пробелы по-особенному считывает
            if (space == ' ')
                textLatin += " ";
            else if (translitSymbols.find(letter) != translitSymbols.end())
                textLatin += translitSymbols.find(letter)->second;
        }
        return textLatin;
    }
    
    std::string createEmail(const std::vector<std::string> &anthroponym)
    {
        std::string email;
        for (auto part: anthroponym) // Фамилия, имя, отчество
        {
            toupperandtolower(part, 0);
            email += translit(part) + ".";
        }
        email.pop_back(); // Удаление лишней точки в конце
        return email += "@tradingcompany.ru";
    }
    
    std::vector<std::string> splitString(std::string source, const std::string &delim)
    {
        std::vector<std::string> result;
        source.erase(remove(source.begin(), source.end(), ' '), source.end()); // Удаление пробелов
        boost::split(result, source, boost::is_any_of(delim));
        return result;
    }

    std::string localTime()
    {
        std::stringstream ss;
        time_t t = std::time(nullptr);
        auto tm = *localtime(&t);
        ss << std::put_time(&tm, "%d.%m.%Y_%H:%M:%S");
        return ss.str();
    }

    std::string date()
    {
        std::stringstream ss;
        time_t t = std::time(nullptr);
        auto tm = *localtime(&t);
        ss << std::put_time(&tm, "%d.%m.%Y");
        return ss.str();
    }

    std::vector<int> findAge(const std::vector<std::string> &data, const std::vector<std::string> &dateOfBirth)
    {
        uint currentDay = atoi(data[0].c_str());
        uint currentMonth = atoi(data[1].c_str());
        uint currentYear = atoi(data[2].c_str());
        uint birthDay = atoi(dateOfBirth[0].c_str());
        uint birthMonth = atoi(dateOfBirth[1].c_str());
        uint birthYear = atoi(dateOfBirth[2].c_str());

        const uint february = ((birthYear % 4) == 0) && (((birthYear % 100) != 0) || ((birthYear % 400) == 0)) ? 29 : 28;
        uint month[12] = { 31, february, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Кол-во дней в 12 месяцах
        if (birthDay > currentDay)
        {
            currentDay += month[birthMonth - 1];
            currentMonth -= 1;
        }
        if (birthMonth > currentMonth)
        {
            currentYear -= 1;
            currentMonth += 12;
        }
        int calculatedDay = currentDay - birthDay;
        int calculatedMonth = currentMonth - birthMonth;
        int calculatedYear = currentYear - birthYear;
        const std::vector<int> age = { calculatedYear, calculatedMonth, calculatedDay };
        return age;
    }

    std::string toUpperAndToLower(std::string source, uint numberUpper)
    {
        if (source.empty())
            return {};
        
        // Конвертирование кириллицы в wstd::string, чтобы перевести буквы нижнего регистра в верхний или обратно
        std::wstring wstr = utf8ToWstring(source);
        for (size_t i = 0; i < numberUpper; ++i)
            wstr[i] = towupper(wstr[i]);
        transform(wstr.begin() + numberUpper, wstr.end(), wstr.begin() + numberUpper, std::towlower);
        // Обратное конвертирование кириллицы в std::string
        source = wstringToUtf8(wstr);
        return source;
    }

    void toupperandtolower(std::string &source, uint numberUpper)
    {
        if (source.empty())
            return;
        
        // Конвертирование кириллицы в wstd::string, чтобы перевести буквы нижнего регистра в верхний или обратно
        std::wstring wstr = utf8ToWstring(source);
        for (size_t i = 0; i < numberUpper; ++i)
            wstr[i] = towupper(wstr[i]);
        transform(wstr.begin() + numberUpper, wstr.end(), wstr.begin() + numberUpper, std::towlower);
        // Обратное конвертирование кириллицы в std::string
        source = wstringToUtf8(wstr);
    }

    std::string formatDateToPostgres(std::string &iData)
    {
        if (iData.empty())
            return {};
        
        const char* delimiters = "./-";
        std::string day = std::strtok(iData.data(), delimiters);
        std::string month = std::strtok(nullptr, delimiters);
        std::string year = std::strtok(nullptr, delimiters);
    
        return year + "-" + month + "-" + day;
    }
}
