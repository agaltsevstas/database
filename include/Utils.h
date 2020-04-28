#ifndef Utils_h
#define Utils_h

#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <codecvt>

#define EXIT(object) Logger::info << "Выход из аккаунта << " << object->getPosition()   << " "   \
                                  << object->getSurname()    << " "   \
                                  << object->getName()       << " "   \
                                  << object->getPatronymic() << std::endl; \
                     std::cout << "Вы вышли из аккаунта" << std::endl; \
                     exit(0);

namespace utils
{
    const std::map<std::string, std::string> translitSymbols =
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
    
    std::string getNameWithoutExtension(const std::string &filePath);
    
    std::string translit(const std::string &textRussian);
    
    std::string createEmail(const std::vector<std::string> &anthroponym);
    
    inline unsigned constexpr str(const char *input)
    {
        return *input ? static_cast<unsigned int>(*input) + 33 * str(input + 1) : 5381;
    }

    inline std::string toLower(std::string &str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    std::vector<std::string> splitString(std::string source, std::string delim);

    std::string date();
    
    std::vector<uint> findAge(std::vector<std::string> &data, std::vector<std::string> &dateOfBirth);

    // convert wstd::string to UTF-8 std::string
    inline std::string wstringToUtf8(const std::wstring &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        return convert.to_bytes(str);
    }

    // convert UTF-8 std::string to wstd::string
    inline std::wstring utf8ToWstring(const std::string &str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        return convert.from_bytes(str);
    }

    void toUpperAndToLower(std::string &str, uint numberUpper = 1);

    std::string convertToString(const std::string &input);

    std::string convertToString(const uint &input);

    std::string convertToString(const uint64_t &input);
}

#endif // Utils_h
