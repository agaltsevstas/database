#include "Accountant.h"
#include "Data.h"
#include "Logger.h"

Accountant::Accountant() : data_(&Data::instance()) {}

Accountant::~Accountant()
{
//    delete data_;
}

void Accountant::checkData()
{
    data_->checkParameter(getId(),
                          function<uint(TradingCompany&)>{&TradingCompany::getId},
                          bind(checkParameters_.at("id"), this, "Ваш id не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getPosition(),
                          function<string(TradingCompany&)>{&TradingCompany::getPosition},
                          bind(&TradingCompany::checkPosition, this, "Ваша должность не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getSurname(),
                          function<string(TradingCompany&)>{&TradingCompany::getSurname},
                          bind(&TradingCompany::checkSurname, this, "Ваша фамилия не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getName(),
                          function<string(TradingCompany&)>{&TradingCompany::getName},
                          bind(&TradingCompany::checkName, this, "Ваше имя не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getPatronymic(),
                          function<string(TradingCompany&)>{&TradingCompany::getPatronymic},
                          bind(&TradingCompany::checkPatronymic, this, "Ваше отчество не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getSex(),
                          function<string(TradingCompany&)>{&TradingCompany::getSex},
                          bind(&TradingCompany::checkSex, this, "Ваш пол не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getDateOfBirth(),
                          function<string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                          bind(&TradingCompany::checkDateOfBirth, this, "Ваша дата рождения не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getPassport(),
                          function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                          bind(&TradingCompany::checkPassport, this, "Ваш паспорт не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getPhone(),
                          function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
                          bind(&TradingCompany::checkPhone, this, "Ваш телефон не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getEmail(),
                          function<string(TradingCompany&)>{&TradingCompany::getEmail},
                          bind(&TradingCompany::checkEmail, this, "Ваша почта не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getDateOfHiring(),
                          function<string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                          bind(&TradingCompany::checkDateOfHiring, this, "Ваша дата принятия на работу не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getWorkingHours(),
                          function<string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                          bind(&TradingCompany::checkWorkingHours, this, "Ваши часы работы не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getSalary(),
                          function<uint(TradingCompany&)>{&TradingCompany::getSalary},
                          bind(&TradingCompany::checkSalary, this, "Ваша зарплата не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getPassword(),
                          function<string(TradingCompany&)>{&TradingCompany::getPassword},
                          bind(&TradingCompany::checkPassword, this, "Ваш пароль не удовлетворяет требованиям!\n"), this, true);
}

void Accountant::functional()
{

}

