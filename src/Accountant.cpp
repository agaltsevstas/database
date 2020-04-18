#include "Accountant.h"
#include "Data.h"

Accountant::Accountant() : data_(&Data::instance()) {}

Accountant::~Accountant()
{
//    delete data_;
}

void Accountant::checkData()
{
    data_->checkParameter(getId(),
                          std::function<uint(TradingCompany&)>{&TradingCompany::getId},
                          bind(checkParameters_.at("id"), this, "Ваш id не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getPosition(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getPosition},
                          bind(&TradingCompany::checkPosition, this, "Ваша должность не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getSurname(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getSurname},
                          bind(&TradingCompany::checkSurname, this, "Ваша фамилия не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getName(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getName},
                          bind(&TradingCompany::checkName, this, "Ваше имя не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getPatronymic(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getPatronymic},
                          bind(&TradingCompany::checkPatronymic, this, "Ваше отчество не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getSex(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getSex},
                          bind(&TradingCompany::checkSex, this, "Ваш пол не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getDateOfBirth(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                          bind(&TradingCompany::checkDateOfBirth, this, "Ваша дата рождения не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getPassport(),
                          std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                          bind(&TradingCompany::checkPassport, this, "Ваш паспорт не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getPhone(),
                          std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
                          bind(&TradingCompany::checkPhone, this, "Ваш телефон не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getEmail(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getEmail},
                          bind(&TradingCompany::checkEmail, this, "Ваша почта не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(getDateOfHiring(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                          bind(&TradingCompany::checkDateOfHiring, this, "Ваша дата принятия на работу не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getWorkingHours(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                          bind(&TradingCompany::checkWorkingHours, this, "Ваши часы работы не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getSalary(),
                          std::function<uint(TradingCompany&)>{&TradingCompany::getSalary},
                          bind(&TradingCompany::checkSalary, this, "Ваша зарплата не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(getPassword(),
                          std::function<std::string(TradingCompany&)>{&TradingCompany::getPassword},
                          bind(&TradingCompany::checkPassword, this, "Ваш пароль не удовлетворяет требованиям!\n"), this, true);
}

void Accountant::functional()
{

}

