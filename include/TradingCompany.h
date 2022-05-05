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
    const std::map<std::string, std::function<void(TradingCompany&, std::string&)>> _setParameters =
    {
        {"id",           nullptr},
        {"position",     &TradingCompany::SetPosition},
        {"surname",      &TradingCompany::SetSurname},
        {"name",         &TradingCompany::SetName},
        {"patronymic",   &TradingCompany::SetPatronymic},
        {"sex",          &TradingCompany::SetSex},
        {"dateOfBirth",  &TradingCompany::SetDateOfBirth},
        {"passport",     &TradingCompany::SetPassport},
        {"phone",        &TradingCompany::SetPhone},
        {"email",        &TradingCompany::SetEmail},
        {"dateOfHiring", &TradingCompany::SetDateOfHiring},
        {"workingHours", &TradingCompany::SetWorkingHours},
        {"salary",       &TradingCompany::SetSalary},
        {"password",     &TradingCompany::SetPassword}
    };
    
    /// Карта полей с их статусом
    std::map<Field, Status> _fieldStatus
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
     * @param iLine - строка
     * @param object - объект
     */
    friend void operator >> (const std::string &iLine, TradingCompany &object);

    /*!
     * @brief Перегрузка оператора << (вывода).
     * Вывод полей объекта
     * @param ioOut - поток вывода
     * @param object - объект
     * @return Поток вывода
     */
    friend std::ostream& operator << (std::ostream &ioOut, const TradingCompany &object);

    /*!
     * @brief Перегрузка оператора == (сравнения).
     * Сравнение двух объектов на равенство
     * @param first - первый объект
     * @param second - второй объект
     * @return Логическое значение
     */
    friend bool operator == (const TradingCompany &first, const TradingCompany &second);

    /// Функционал каждого производного класса
    virtual void Functional() = 0;

    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    std::string GetPosition() const;
    std::string GetSurname() const;
    std::string GetName() const;
    std::string GetPatronymic() const;
    
protected:
    /*!
     * @brief Получение значений полей
     * @return Значение поля
     */
    uint32_t    GetId() const;
    std::string GetSex() const;
    std::string GetDateOfBirth() const;
    uint64_t    GetPassport() const;
    uint64_t    GetPhone() const;
    std::string GetEmail() const;
    std::string GetDateOfHiring() const;
    std::string GetWorkingHours() const;
    uint32_t    GetSalary() const;
    std::string GetPassword() const;

private:
    uint32_t    _id = 0;       /// ID
    std::string _position;     /// Должность
    std::string _surname;      /// Фамилия
    std::string _name;         /// Имя
    std::string _patronymic;   /// Отчество
    std::string _sex;          /// Пол
    std::string _dateOfBirth;  /// Дата рождения
    uint64_t    _passport = 0; /// Паспорт
    uint64_t    _phone = 0;    /// Телефон
    std::string _email;        /// Почта
    std::string _dateOfHiring; /// Дата принятия на работу
    std::string _workingHours; /// Часы работы
    uint32_t    _salary = 0;   /// Зарплата
    std::string _password;     /// Пароль
    
    /*!
     * @brief Инициализация полей
     * @param Значение поля
     */
    void SetId(const std::string &iID);
    void SetPosition(const std::string &iPosition);
    void SetSurname(const std::string &iSurname);
    void SetName(const std::string &iName);
    void SetPatronymic(const std::string &iPatronymic);
    void SetSex(const std::string &iSex);
    void SetDateOfBirth(const std::string &iDateOfBirth);
    void SetPhone(const std::string &iPhone);
    void SetEmail(const std::string &iEmail);
    void SetDateOfHiring(const std::string &iDateOfHiring);
    void SetWorkingHours(const std::string &iWorkingHours);
    void SetPassport(const std::string &iPassport);
    void SetSalary(const std::string &iSalary);
    void SetPassword(const std::string &iPassword);

    /*!
     * @brief Проверка полей на повреждение/перезапись данных
     * @param iWarning - Предупреждение о невалидности данных поля
     */
    void CheckId(const std::string &iWarning = {}); /// Не используется!
    void CheckPosition(const std::string &iWarning = {});
    void CheckSurname(const std::string &iWarning = {});
    void CheckName(const std::string &iWarning = {});
    void CheckPatronymic(const std::string &iWarning = {});
    void CheckSex(const std::string &iWarning = {});
    void CheckDateOfBirth(const std::string &iWarning = {});
    void CheckPassport(const std::string &iWarning = {});
    void CheckPhone(const std::string &iWarning = {});
    void CheckEmail(const std::string &iWarning = {});
    void CheckDateOfHiring(const std::string &iWarning = {});
    void CheckWorkingHours(const std::string &iWarning = {});
    void CheckSalary(const std::string &iWarning = {});
    void CheckPassword(const std::string &iWarning = {});

    /*!
     * @brief Изменение статуса полей на перезапись/дублирование данных
     */
    void ChangeStatusPosition();
    void ChangeStatusSurname();
    void ChangeStatusName();
    void ChangeStatusPatronymic();
    void ChangeStatusSex();
    void ChangeStatusDateOfBirth();
    /// @param canOverwrite - true-перезапись/false-дублирование
    void ChangeStatusPassport(const bool canOverwrite = false);
    /// @param canOverwrite - true-перезапись/false-дублирование
    void ChangeStatusPhone(const bool canOverwrite = false);
    /// @param canOverwrite - true-перезапись/false-дублирование
    void ChangeStatusEmail(const bool canOverwrite);
    void ChangeStatusDateOfHiring();
    void ChangeStatusWorkingHours();
    void ChangeStatusSalary();
    void ChangeStatusPassword();

    /*!
     * @brief Рекурсия, которая вызывается в случае неверного введения данных.
     * Валидация ввода данных
     * @param iField - Номер поля
     * @param setParameter - Инициализация одного из полей
     * @param iMessage - Сообщение, которое подказывает в каком формате вводить данные
     */
    void Recursion(const Field iField,
                   std::function<void(TradingCompany&, std::string&)> setParameter,
                   const std::string &iMessage);
    /*!
     * @brief Получение определенного типа данных (uint32_t/uint64_t/string)
     * @param iValue - Значение поля
     * @param iField - Номер поля
     * @return Значение поля с определенным типом (uint32_t/uint64_t/string)
     */
    template<typename T> T Get(const std::string &iValue, const Field iField);

    /// Пустая структура для возврата из метода в случае неудачи (затычка)
    const Type empty = Type();

    /*!
     * @details Валидация данных.
     * Проверка данных каждого поля в соответствии с требованиями
     * в зависимости от номера поля. Значение поля устанавливается
     * в одно из полей струтуры данных (uint32_t/uint64_t/string).
     * Устанавливается статус поля (ST_EMPTY/ST_WRONGDATA/ST_OK)
     * @param iValue - Значение поля
     * @param iField - Номер поля
     * @return Структура данных
     */
    const Type CheckField(std::string iValue, const Field iField);

    /*!
     * @TODO: Установление премии
     * @param premium - Премия
     */
    void SetPremium(int premium);

    /*!
     * @TODO: Установление штрафа
     * @param fine - Штраф
     */
    void SetFine(int fine);

    /*!
     * @TODO: Получение премии
     * @return Премия
     */
    uint GetPremium() const;
    /*!
     * @TODO: Получение штрафа
     * @return Штраф
     */
    uint GetFine() const;
};

#endif // TradingCompany_h
