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

enum Numbers
{
    ONE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
};

class TradingCompany
{
    friend class Director;
    
private:

    enum Status
    {
        /// Успех
        ST_OK = 0,

        /// Неудача
        ST_FAIL,

        /// Пусто
        ST_EMPTY,

        /// Проблема с данными
        ST_WRONGDATA,

        /// Дублирование данных
        ST_DUBLICATE
    };
    /*
     * Внутренняя структура параметра
     */
    struct Type
    {
        /// Статус данных
        Status status;
        
        /// Целочисленное значение
        uint uintValue = 0;
        
        uint64_t uint64Value = 0;
        
        /// Строковое значение
        string stringValue;
    };
    const map<string, Field> parameters =
    {
        {"id",           FIELD_ID},
        {"position",     FIELD_POSITION},
        {"surname",      FIELD_SURNAME},
        {"name",         FIELD_NAME},
        {"patronymic",   FIELD_PATRONYMIC},
        {"sex",          FIELD_SEX},
        {"dateOfBirth",  FIELD_DATE_OF_BIRTH},
        {"passport",     FIELD_PASSPORT},
        {"phone",        FIELD_PHONE},
        {"email",        FIELD_EMAIL},
        {"dateOfHiring", FIELD_DATE_OF_HIRING},
        {"workingHours", FIELD_WORKING_HOURS},
        {"salary",       FIELD_SALARY},
        {"password",     FIELD_PASSWORD}
    };
    /// Карта параметров
    map<Field, Status> fieldStatus_
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
//    TradingCompany() {}
    virtual ~TradingCompany() {}
    virtual void functional() = 0;
//    ~TradingCompany();
    void setId(string &id);
    void setPosition(string &position);
    void setSurname(string &surname);
    void setName(string &name);
    void setPatronymic(string &patronymic);
    void setSex(string &sex);
    void setDateOfBirth(string &dateOfBirth);
    void setAge(string &dateOfBirth);
    void setPhone(string &phone);
    void setEmail(string &phone);
    void setDateOfHiring(string &dateOfHiring);
    void setWorkingHours(string &workingHours);
    void setPassport(string &passport);
    void setSalary(string &salary);
    void setPassword(string &password);
    
    uint     getId();
    string   getPosition();
    string   getSurname();
    string   getName();
    string   getPatronymic();
    string   getSex();
    string   getDateOfBirth();
    uint64_t getPhone();
    string   getEmail();
    string   getDateOfHiring();
    string   getWorkingHours();
    uint64_t getPassport();
    uint     getSalary();
    string   getPassword();
    uint     getPremium();
    uint     getFine();
    
    void changeStatusId();
    void changeStatusPassport();
    void changeStatusPhone();
    void changeStatusPassword(bool isWrite);
    void checkPhone(const string &warning = {});
    void checkEmail(const string &warning = {});
    void checkPassword(const string &warning = {});
    void displayUser();
    void changePersonalData();
    
    friend void operator >> (const string &line, TradingCompany &tradingCompany);
    friend ostream& operator << (ostream &out, const TradingCompany &tradingCompany);
    friend bool operator == (const TradingCompany &first, const TradingCompany &second);

private:
    uint     id_;
    string   position_;
    string   surname_;
    string   name_;
    string   patronymic_;
    string   sex_;
    string   dateOfBirth_;
    uint64_t passport_;
    uint64_t phone_;
    string   email_;
    string   dateOfHiring_;
    string   workingHours_;
    uint     salary_;
    string   password_;
    
    void switchCaseParameter(string &parameter, const Field &field);
    void checkId(const string &warning = {});
    void checkPosition(const string &warning = {});
    void checkSurname(const string &warning = {});
    void checkName(const string &warning = {});
    void checkPatronymic(const string &warning = {});
    void checkSex(const string &warning = {});
    void checkDateOfBirth(const string &warning = {});
    void checkPassport(const string &warning = {});
    void checkDateOfHiring(const string &warning = {});
    void checkWorkingHours(const string &warning = {});
    void checkSalary(const string &warning = {});
    template <typename T> void recursion(const Field &field, const string &message, const T &parameter);
    template<typename T> T get(string &value, const Field field);
    /// Пустое поле для возврата в качестве отсутствия результата поиска
    const Type empty = Type();
    const Type checkField(string &value, const Field &numberField);
};

//enum class classes { directors, chief_accountant };

#endif // TradingCompany_h
