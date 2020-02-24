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

#include "Logger.h"

class Director;
class ChiefAccountant;
class ChiefLegalCounsel;
class HeadOfProcurement;
class HeadOfWarehouse;
class SalesManager;
class Cashier;
class Accountant;
class Logistician;
class Lawyer;
class PurchasingManager;
class Stevedore;
class Driver;
class Vector;

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

const list<string> positions
{
    "Бухгалтер",
    "Водитель",
    "Главный_бухгалтер",
    "Главный_юрист-консультант",
    "Грузчик",
    "Директор",
    "Логист",
    "Менеджер_по_закупкам",
    "Менеджер_по_продажам",
    "Кассир",
    "Начальник_отдела_закупок",
    "Начальник_склада",
    "Юрист"
};

class TradingCompany
{
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
        
        unsigned long long ulonglongValue = 0;
        
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
//    virtual void functional();
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
    
    uint               getId();
    string             getPosition();
    string             getSurname();
    string             getName();
    string             getPatronymic();
    string             getSex();
    string             getDateOfBirth();
    string             getAge();
    unsigned long long getPhone();
    string             getDateOfHiring();
    string             getWorkingHours();
    unsigned long long getPassport();
    uint               getSalary();
    string             getPassword();
    uint               getPremium();
    uint               getFine();
    
    void displayUser();
    void changePersonalData();
    
    friend class Director;
    friend class ChiefSccountant;
    friend class ChiefLegalCounsel;
    friend class HeadOfProcurement;
    friend class HeadOfWarehouse;
    friend class SalesManager;
    friend class Cashier;
    friend class Accountant;
    friend class Logistician;
    friend class Lawyer;
    friend class PurchasingManager;
    friend class Stevedore;
    friend class Driver;
    friend class Vector;
    friend ostream& operator << (ostream &out, const TradingCompany &tradingCompany);
    friend void operator >> (const string &line, TradingCompany &tradingCompany);
    
protected:
    uint id_;
    string position_;
    string surname_;
    string name_;
    string patronymic_;
    string sex_;
    string dateOfBirth_;
    unsigned long long passport_;
    unsigned long long phone_;
    string email_;
    string dateOfHiring_;
    string workingHours_;
    uint salary_;
    string password_;

private:
    template<typename T> T get(string &value, const Field field);
    /// Пустое поле для возврата в качестве отсутствия результата поиска
    const Type empty = Type();
    const Type checkField(string &value, const Field &numberField);
};

//enum class classes { directors, chief_accountant };

#endif // TradingCompany_h
