#ifndef TradingCompany_h
#define TradingCompany_h

#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <memory>
#include <map>
#include <list>
#include <functional>

#include "Logger.h"

/// Номера полей класса TradingCompany
enum Field
{
    FIELD_ID = 0,
    FIELD_POSITION,
    FIELD_SURNAME,
    FIELD_NAME,
    FIELD_PATRONYMIC,
    FIELD_SEX,
    FIELD_DATE_OF_BIRTH,
    FIELD_PASSPORT,
    FIELD_PHONE,
    FIELD_EMAIL,
    FIELD_DATE_OF_HIRING,
    FIELD_WORKING_HOURS,
    FIELD_SALARY,
    FIELD_PASSWORD,
};

/// Статус данных
enum Status
{
    /// Успех
    ST_OK = 0,
    
    /// Перезаписывание данных
    ST_OVERWRITEDATA,

    /// Пусто
    ST_EMPTY,

    /// Проблема с данными
    ST_WRONGDATA,

    /// Дублирование данных
    ST_DUBLICATE
};

/*!
 * @brief Абстрактный класс
 */
class TradingCompany
{
    friend class Data;
    friend class Director;
    
private:
    /*!
     * @brief Структура данных
     */
    struct Type
    {
        /// Статус данных
        Status status;

        /*!
         * @brief Тип данных
         */
        
        /// 32-разрядное целое значение без знака
        uint32_t uintValue = 0;
        
        /// 64-разрядное целое значение без знака
        uint64_t uint64Value = 0;
        
        /// Строковое значение
        std::string stringValue;
    };
    
    /// Карта параметров и оберток инициализаций полей
    const std::map<std::string, std::function<void(TradingCompany&, std::string&)>> setParameters_ =
    {
        {"id",           nullptr},
        {"position",     &TradingCompany::setPosition},
        {"surname",      &TradingCompany::setSurname},
        {"name",         &TradingCompany::setName},
        {"patronymic",   &TradingCompany::setPatronymic},
        {"sex",          &TradingCompany::setSex},
        {"dateOfBirth",  &TradingCompany::setDateOfBirth},
        {"passport",     &TradingCompany::setPassport},
        {"phone",        &TradingCompany::setPhone},
        {"email",        &TradingCompany::setEmail},
        {"dateOfHiring", &TradingCompany::setDateOfHiring},
        {"workingHours", &TradingCompany::setWorkingHours},
        {"salary",       &TradingCompany::setSalary},
        {"password",     &TradingCompany::setPassword}
    };
    
    /// Карта полей с их статусом
    std::map<Field, Status> fieldStatus_
    {
        {FIELD_ID,             ST_EMPTY},
        {FIELD_POSITION,       ST_EMPTY},
        {FIELD_SURNAME,        ST_EMPTY},
        {FIELD_NAME,           ST_EMPTY},
        {FIELD_PATRONYMIC,     ST_EMPTY},
        {FIELD_SEX,            ST_EMPTY},
        {FIELD_DATE_OF_BIRTH,  ST_EMPTY},
        {FIELD_PASSPORT,       ST_EMPTY},
        {FIELD_PHONE,          ST_EMPTY},
        {FIELD_EMAIL,          ST_EMPTY},
        {FIELD_DATE_OF_HIRING, ST_EMPTY},
        {FIELD_WORKING_HOURS,  ST_EMPTY},
        {FIELD_SALARY,         ST_EMPTY},
        {FIELD_PASSWORD,       ST_EMPTY},
    };

public:
    virtual ~TradingCompany() {}

    /*!
     * @brief Перегрузка оператора = (присваивания).
     * Запись данных из одного объекта в другой
     * @param object - объект
     * @return Измененный объект
     */
    const TradingCompany& operator = (const TradingCompany &object);

    /*!
     * @brief Перегрузка оператора >> (ввода).
     * Запись данных в поля объекта
     * @param line - строка
     * @param object - объект
     */
    friend void operator >> (const std::string &line, TradingCompany &object);

    /*!
     * @brief Перегрузка оператора << (вывода).
     * Вывод полей объекта
     * @param out - поток вывода
     * @param object - объект
     * @return Поток вывода
     */
    friend std::ostream& operator << (std::ostream &out, const TradingCompany &object);

    /*!
     * @brief Перегрузка оператора == (сравнения).
     * Сравнение двух объектов на равенство
     * @param first - первый объект
     * @param second - второй объект
     * @return Логическое значение
     */
    friend bool operator == (const TradingCompany &first, const TradingCompany &second);

    /// Функционал каждого производного класса
    virtual void functional() = 0;

    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    std::string getPosition() const;
    std::string getSurname() const;
    std::string getName() const;
    std::string getPatronymic() const;
    
protected:
    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    uint32_t    getId() const;
    std::string getSex() const;
    std::string getDateOfBirth() const;
    uint64_t    getPassport() const;
    uint64_t    getPhone() const;
    std::string getEmail() const;
    std::string getDateOfHiring() const;
    std::string getWorkingHours() const;
    uint32_t    getSalary() const;
    std::string getPassword() const;

private:
    uint32_t    id_ = 0;       /// ID
    std::string position_;     /// Должность
    std::string surname_;      /// Фамилия
    std::string name_;         /// Имя
    std::string patronymic_;   /// Отчество
    std::string sex_;          /// Пол
    std::string dateOfBirth_;  /// Дата рождения
    uint64_t    passport_ = 0; /// Паспорт
    uint64_t    phone_ = 0;    /// Телефон
    std::string email_;        /// Почта
    std::string dateOfHiring_; /// Дата принятия на работу
    std::string workingHours_; /// Часы работы
    uint32_t    salary_ = 0;   /// Зарплата
    std::string password_;     /// Пароль
    
    /*!
     * @brief Инициализация полей
     * @param Значение поля
     */
    void setId(const std::string &id);
    void setPosition(const std::string &position);
    void setSurname(const std::string &surname);
    void setName(const std::string &name);
    void setPatronymic(const std::string &patronymic);
    void setSex(const std::string &sex);
    void setDateOfBirth(const std::string &dateOfBirth);
    void setPhone(const std::string &phone);
    void setEmail(const std::string &email);
    void setDateOfHiring(const std::string &dateOfHiring);
    void setWorkingHours(const std::string &workingHours);
    void setPassport(const std::string &passport);
    void setSalary(const std::string &salary);
    void setPassword(const std::string &password);

    /*!
     * @brief Проверка полей на повреждение/перезапись данных
     * @param warning - Предупреждение о невалидности данных поля
     */
    void checkId(const std::string &warning = {}); /// Не используется!
    void checkPosition(const std::string &warning = {});
    void checkSurname(const std::string &warning = {});
    void checkName(const std::string &warning = {});
    void checkPatronymic(const std::string &warning = {});
    void checkSex(const std::string &warning = {});
    void checkDateOfBirth(const std::string &warning = {});
    void checkPassport(const std::string &warning = {});
    void checkPhone(const std::string &warning = {});
    void checkEmail(const std::string &warning = {});
    void checkDateOfHiring(const std::string &warning = {});
    void checkWorkingHours(const std::string &warning = {});
    void checkSalary(const std::string &warning = {});
    void checkPassword(const std::string &warning = {});

    /*!
     * @brief Изменение статуса полей на перезапись/дублирование данных
     */
    void changeStatusPosition();
    void changeStatusSurname();
    void changeStatusName();
    void changeStatusPatronymic();
    void changeStatusSex();
    void changeStatusDateOfBirth();
    /// @param canOverwrite - true-перезапись/false-дублирование
    void changeStatusPassport(const bool canOverwrite = false);
    /// @param canOverwrite - true-перезапись/false-дублирование
    void changeStatusPhone(const bool canOverwrite = false);
    /// @param canOverwrite - true-перезапись/false-дублирование
    void changeStatusEmail(const bool canOverwrite);
    void changeStatusDateOfHiring();
    void changeStatusWorkingHours();
    void changeStatusSalary();
    void changeStatusPassword();

    /*!
     * @brief Рекурсия, которая вызывается в случае неверного введения данных.
     * Валидация ввода данных
     * @param field - Номер поля
     * @param setParameter - Инициализация одного из полей
     * @param message - Сообщение, которое подказывает в каком формате вводить данные
     */
    void recursion(const Field field,
                   std::function<void(TradingCompany&, std::string&)> setParameter,
                   const std::string &message);
    /*!
     * @brief Получение определенного типа данных (uint32_t/uint64_t/string)
     * @param field - Номер поля
     * @param value - Значение поля
     * @return Значение поля с определенным типом (uint32_t/uint64_t/string)
     */
    template<typename T> T get(const std::string &value, const Field field);

    /// Пустая структура для возврата из метода в случае неудачи (затычка)
    const Type empty = Type();

    /*!
     * @details Валидация данных.
     * Проверка данных каждого поля в соответствии с требованиями
     * в зависимости от номера поля. Значение поля устанавливается
     * в одно из полей струтуры данных (uint32_t/uint64_t/string).
     * Устанавливается статус поля (ST_EMPTY/ST_WRONGDATA/ST_OK)
     * @param value - Значение поля
     * @param field - Номер поля
     * @return Структура данных
     */
    const Type checkField(std::string value, const Field field);

    /*!
     * @TODO: Установление премии
     * @param premium - Премия
     */
    void setPremium(int premium);

    /*!
     * @TODO: Установление штрафа
     * @param fine - Штраф
     */
    void setFine(int fine);

    /*!
     * @TODO: Получение премии
     * @return Премия
     */
    uint getPremium() const;
    /*!
     * @TODO: Получение штрафа
     * @return Штраф
     */
    uint getFine() const;
};

#endif // TradingCompany_h
