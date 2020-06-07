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

enum Status
{
    /// Успех
    ST_OK = 0,
    
    // Перезаписывание данных
    ST_OVERWRITEDATA,

    /// Пусто
    ST_EMPTY,

    /// Проблема с данными
    ST_WRONGDATA,

    /// Дублирование данных
    ST_DUBLICATE
};

class TradingCompany
{
    friend class Data;
    friend class Director;
    
private:
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
        std::string stringValue;
    };
    
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
    
    /// Карта параметров
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
    virtual void functional() = 0;
    std::string getPosition() const;
    std::string getSurname() const;
    std::string getName() const;
    std::string getPatronymic() const;
    
    const TradingCompany& operator = (const TradingCompany &object);
    friend void operator >> (const std::string &line, TradingCompany &tradingCompany);
    friend std::ostream& operator << (std::ostream &out, const TradingCompany &tradingCompany);
    friend bool operator == (const TradingCompany &first, const TradingCompany &second);
    
protected:
    uint        getId() const;
    std::string getSex() const;
    std::string getDateOfBirth() const;
    uint64_t    getPassport() const;
    uint64_t    getPhone() const;
    std::string getEmail() const;
    std::string getDateOfHiring() const;
    std::string getWorkingHours() const;
    uint        getSalary() const;
    std::string getPassword() const;
    uint        getPremium() const;
    uint        getFine() const;

private:
    uint        id_ = 0;
    std::string position_;
    std::string surname_;
    std::string name_;
    std::string patronymic_;
    std::string sex_;
    std::string dateOfBirth_;
    uint64_t    passport_ = 0;
    uint64_t    phone_ = 0;
    std::string email_;
    std::string dateOfHiring_;
    std::string workingHours_;
    uint        salary_ = 0;
    std::string password_;
    
    void setId(const std::string &id);
    void setPosition(const std::string &position);
    void setSurname(const std::string &surname);
    void setName(const std::string &name);
    void setPatronymic(const std::string &patronymic);
    void setSex(const std::string &sex);
    void setDateOfBirth(const std::string &dateOfBirth);
    void setPhone(const std::string &phone);
    void setEmail(const std::string &phone);
    void setDateOfHiring(const std::string &dateOfHiring);
    void setWorkingHours(const std::string &workingHours);
    void setPassport(const std::string &passport);
    void setSalary(const std::string &salary);
    void setPassword(const std::string &password);
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
    void changePersonalData();
    void changeStatusPosition();
    void changeStatusSurname();
    void changeStatusName();
    void changeStatusPatronymic();
    void changeStatusSex();
    void changeStatusDateOfBirth();
    void changeStatusPassport(const bool canOverwrite = false);
    void changeStatusPhone(const bool canOverwrite = false);
    void changeStatusEmail(const bool canOverwrite);
    void changeStatusDateOfHiring();
    void changeStatusWorkingHours();
    void changeStatusSalary();
    void changeStatusPassword();
    void checkId(const std::string &warning = {});
    void recursion(const Field &field,
                   std::function<void(TradingCompany&, std::string&)> setParameter,
                   const std::string &message);
    template<typename T> T get(const std::string &value, const Field field);
    /// Пустое поле для возврата в качестве отсутствия результата поиска
    const Type empty = Type();
    const Type checkField(std::string value, const Field &numberField);
};

#endif // TradingCompany_h
