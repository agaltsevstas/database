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

#define LOGIN(object) Logger::info << "Вход в аккаунт >> " << object->GetPosition()   << " "        \
                                                           << object->GetSurname()    << " "        \
                                                           << object->GetName()       << " "        \
                                                           << object->GetPatronymic() << std::endl; \
                      std::cout << "Вы зашли за " << object->GetPosition() << "'a. " << std::endl;  \
                      std::cout << "Приветствуем вас, " << object->GetSurname()    << " "           \
                                                        << object->GetName()       << " "           \
                                                        << object->GetPatronymic() << "!"           \
                                                        << std::endl;
 
#define LOGOUT(object) Logger::info << "Выход из аккаунта << " << object->GetPosition()   << " "        \
                                                               << object->GetSurname()    << " "        \
                                                               << object->GetName()       << " "        \
                                                               << object->GetPatronymic() << std::endl; \
                       std::cout << std::endl << "Вы вышли из аккаунта" << std::endl;

#define EXIT(object) Logger::info << "Выход из аккаунта << " << object->GetPosition()   << " "        \
                                                             << object->GetSurname()    << " "        \
                                                             << object->GetName()       << " "        \
                                                             << object->GetPatronymic() << std::endl; \
                     Logger::info << "Выход из программы" << std::endl;                               \
                     std::cout << std::endl;                                                          \
                     std::cout << "Вы вышли из аккаунта" << std::endl;                                \
                     std::cout << "Вы вышли из программы" << std::endl;                               \
                     exit(0);

namespace Utils
{
    // Карта перевода из кириллицы в латиницу
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
    
    /*!
     * @brief Перевод кирилицы латинскими буквами
     * @param textCyrillic - Кириллица
     * @return Латиница
     */
    std::string Translit(const std::string &textCyrillic);
    
    /*!
     * @brief Создание почты, используя фамилию, имя и отчество
     * @param anthroponym - Вектор антропононимов
     * @return Готовая почта
     */
    std::string CreateEmail(const std::vector<std::string> &anthroponym);
    
    /*!
     * @brief Хэширование текста
     * @param source - Исходный текст
     * @return Готовый текст
     */
    inline unsigned constexpr Hash(const char *source)
    {
        return *source ? static_cast<unsigned int>(*source) + 33 * Hash(source + 1) : 5381;
    }

    /*!
     * @brief Конвертирование прописных букв в строчные
     * @param source - Исходный текст
     * @return Готовый текст
     */
    inline std::string toLower(std::string source)
    {
        std::transform(source.begin(), source.end(), source.begin(), ::tolower);
        return source;
    }

    /*!
     * @brief Конвертирование прописных букв в строчные
     * @param source - Исходный текст
     */
    inline void tolower(std::string &source)
    {
        std::transform(source.begin(), source.end(), source.begin(), ::tolower);
    }

    /*!
     * @brief Разбиение текста на части
     * @param source - Исходный текст
     */
    std::vector<std::string> SplitString(std::string source, const std::string &delim);

    /*!
     * @brief Получение локального времени
     * @return - Локальное время
     */
    std::string LocalTime();

    /*!
     * @brief Получение текущей даты
     * @return - Текущая дата
     */
    std::string Date();
    
    /*!
     * @brief Получение возраста
     * @param data - Вектор, хранящий текущую дату (день, месяц, год)
     * @param dateOfBirth - Вектор, хранящий дату рождения (день, месяц, год)
     * @return - Найденный возраст
     */
    std::vector<int> FindAge(const std::vector<std::string> &data, const std::vector<std::string> &dateOfBirth);

    /*!
     * @brief Конвертирование wstd::string в UTF-8 std::string
     * @param source - Исходный текст
     * @return Готовый текст
     */
    inline std::string WstringToUtf8(const std::wstring &source)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        return convert.to_bytes(source);
    }

    /*!
     * @brief Конвертирование UTF-8 std::string в wstd::string
     * @param source - Исходный текст
     * @return Готовый текст
     */
    inline std::wstring UTF8ToWstring(const std::string &source)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
        return convert.from_bytes(source);
    }

    /*!
     * @brief Конвертирование текста в прописные и строчные буквы
     * @param source - Исходный текст
     * @param numberUpper - Кол-во прописных букв в начале текста, остальные буквы переводятся в строчные
     * @return Готовый текст
     */
    std::string ToUpperAndToLower(std::string source, uint numberUpper = 1);

    /*!
     * @brief Конвертирование текста в прописные и строчные буквы
     * @param source - Исходный текст
     * @param numberUpper - Кол-во прописных букв в начале текста, остальные буквы переводятся в строчные
     */
    void ToUpperandtolower(std::string &source, uint numberUpper = 1);

    /*!
     * @brief Получение имени класса в строковом виде
     * @param object - Объект класса
     * @return Имя класса
     */
    template <class C>
    inline std::string GetClassName(const C &object)
    {
        std::string source = typeid(object).name();
        // Удаление числа, которое указывает на кол-во символов
        source.erase(std::remove_if(std::begin(source), std::end(source), [](auto c) { return std::isdigit(c); }), source.end());
        return source;
    }
}

#endif // Utils_h
