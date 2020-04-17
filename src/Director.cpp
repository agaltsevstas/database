#include "Director.h"
#include "Data.h"
#include "Logger.h"
#include "Utils.h"

using namespace utils;

Director::Director() : data_(&Data::instance()) {}

Director::~Director()
{
//    delete data_;
}

void Director::checkData()
{
    data_->checkParameter(id_,
                          function<uint(TradingCompany&)>{&TradingCompany::getId},
                          bind(checkParameters_.at("id"), this, "Ваш id не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(position_,
                          function<string(TradingCompany&)>{&TradingCompany::getPosition},
                          bind(&TradingCompany::checkPosition, this, "Ваша должность не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(surname_,
                          function<string(TradingCompany&)>{&TradingCompany::getSurname},
                          bind(&TradingCompany::checkSurname, this, "Ваша фамилия не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(name_,
                          function<string(TradingCompany&)>{&TradingCompany::getName},
                          bind(&TradingCompany::checkName, this, "Ваше имя не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(patronymic_,
                          function<string(TradingCompany&)>{&TradingCompany::getPatronymic},
                          bind(&TradingCompany::checkPatronymic, this, "Ваше отчество не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(sex_,
                          function<string(TradingCompany&)>{&TradingCompany::getSex},
                          bind(&TradingCompany::checkSex, this, "Ваш пол не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(dateOfBirth_,
                          function<string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                          bind(&TradingCompany::checkDateOfBirth, this, "Ваша дата рождения не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(passport_,
                          function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                          bind(&TradingCompany::checkPassport, this, "Ваш паспорт не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(phone_,
                          function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
                          bind(&TradingCompany::checkPhone, this, "Ваш телефон не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(email_,
                          function<string(TradingCompany&)>{&TradingCompany::getEmail},
                          bind(&TradingCompany::checkEmail, this, "Ваша почта не удовлетворяет требованиям!\n"), this, true);
    data_->checkParameter(dateOfHiring_,
                          function<string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                          bind(&TradingCompany::checkDateOfHiring, this, "Ваша дата принятия на работу не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(workingHours_,
                          function<string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                          bind(&TradingCompany::checkWorkingHours, this, "Ваши часы работы не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(salary_,
                          function<uint(TradingCompany&)>{&TradingCompany::getSalary},
                          bind(&TradingCompany::checkSalary, this, "Ваша зарплата не удовлетворяет требованиям!\n"), this);
    data_->checkParameter(password_,
                          function<string(TradingCompany&)>{&TradingCompany::getPassword},
                          bind(&TradingCompany::checkPassword, this, "Ваш пароль не удовлетворяет требованиям!\n"), this, true);
}

void Director::changePersonalData()
{
    string input;
    while (true)
    {
        cout << "Изменить свой ID - нажмите 1" << endl;
        cout << "Изменить свою должность - нажмите 2" << endl;
        cout << "Изменить свою фамилию - нажмите 3" << endl;
        cout << "Изменить своё имя - нажмите 4" << endl;
        cout << "Изменить своё отчество - нажмите 5" << endl;
        cout << "Изменить свой пол - нажите 6" << endl;
        cout << "Изменить свою дату рождения - нажмите 7" << endl;
        cout << "Изменить свой номер паспорта - нажмите 8" << endl;
        cout << "Изменить свой номер телефона - нажмите 9" << endl;
        cout << "Изменить свою почту - нажмите 10" << endl;
        cout << "Изменить свою дату принятия на работу - нажмите 11" << endl;
        cout << "Изменить свои часы работы - нажмите 12" << endl;
        cout << "Изменить свою зарплату - нажмите 13" << endl;
        cout << "Изменить свой пароль к доступу - нажмите 14" << endl;
        cout << "Хотите вернуться назад? - введите B: " << endl;
        cout << "Хотите выйти из программы? - введите ESC: " << endl;
        try
        {
            cin >> input;
            toLower(input);
            switch (str(input.c_str()))
            {
                case str("1") :
                    changeStatusId(true);
                    data_->checkParameter(id_,
                                          function<uint(TradingCompany&)>{&TradingCompany::getId},
                                          bind(checkParameters_.at("id"), this, ""), this, true);
                    break;
                    
                case str("2") :
                {
                    cout << "При изменении своей должности вы теряете свои полномочия." << endl;
                    cout << "Введите yes - для продолжения, no - для отмены." << endl;
                    cout << "Ввод: " << endl;
                    string input;
                    cin >> input;
                    toLower(input);
                    if (input == "yes")
                    {
                        cout << "Выберите одну из предложенных должности: " << endl;
                        copy(positions.begin(), positions.end(), ostream_iterator<string>(cout, " "));
                        changeStatusPosition();
                        data_->checkParameter(position_,
                                              function<string(TradingCompany&)>{&TradingCompany::getPosition},
                                              bind(&TradingCompany::checkPosition, this, ""), this);
                    }
                    else if (input == "no")
                    {
                        changePersonalData();
                    }
                    break;
                }
                    
                case str("3") :
                    changeStatusSurname();
                    data_->checkParameter(surname_,
                                          function<string(TradingCompany&)>{&TradingCompany::getSurname},
                                          bind(&TradingCompany::checkSurname, this, ""), this);
                    break;
                    
                case str("4") :
                    changeStatusName();
                    data_->checkParameter(name_,
                                          function<string(TradingCompany&)>{&TradingCompany::getName},
                                          bind(&TradingCompany::checkName, this, ""), this);
                    break;
                    
                case str("5") :
                    changeStatusPatronymic();
                    data_->checkParameter(patronymic_,
                                          function<string(TradingCompany&)>{&TradingCompany::getPatronymic},
                                          bind(&TradingCompany::checkPatronymic, this, "!\n"), this);
                    break;
                    
                case str("6") :
                    changeStatusSex();
                    data_->checkParameter(sex_,
                                          function<string(TradingCompany&)>{&TradingCompany::getSex},
                                          bind(&TradingCompany::checkSex, this, ""), this);
                    break;
                    
                case str("7") :
                    changeStatusDateOfBirth();
                    data_->checkParameter(dateOfBirth_,
                                          function<string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                                          bind(&TradingCompany::checkDateOfBirth, this, ""), this);
                    break;
                    
                case str("8") :
                    changeStatusPassport(true);
                    data_->checkParameter(passport_,
                                          function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                                          bind(&TradingCompany::checkPassport, this, ""), this, true);
                    break;
                    
                case str("9") :
                    changeStatusPhone(true);
                    data_->checkParameter(passport_,
                                          function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                                          bind(&TradingCompany::checkPassport, this, ""), this, true);
                    break;
                    
                case str("10") :
                    changeStatusEmail(true);
                    data_->checkParameter(email_,
                                          function<string(TradingCompany&)>{&TradingCompany::getEmail},
                                          bind(&TradingCompany::checkEmail, this, ""), this, true);
                    break;
                    
                case str("11") :
                    changeStatusDateOfHiring();
                    data_->checkParameter(dateOfHiring_,
                                          function<string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                                          bind(&TradingCompany::checkDateOfHiring, this, ""), this);
                    break;
                    
                case str("12") :
                    changeStatusWorkingHours();
                    break;
                    
                case str("13") :
                    changeStatusSalary();
                    data_->checkParameter(workingHours_,
                                          function<string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                                          bind(&TradingCompany::checkWorkingHours, this, "Ваши часы работы не удовлетворяет требованиям!\n"), this);
                    break;
                    
                case str("14") :
                    changeStatusPassword(true);
                    data_->checkParameter(password_,
                                          function<string(TradingCompany&)>{&TradingCompany::getPassword},
                                          bind(&TradingCompany::checkPassword, this, ""), this, true);
                    break;
                    
                case str("b") :
                    return;
                case str("esc") :
                    Logger::info << "Выход из аккаунта << " << position_   << " "
                                                            << surname_    << " "
                                                            << name_       << " "
                                                            << patronymic_ << endl;
                    cout << "Вы вышли из аккаунта." << endl;
                    exit(0);
                default:
                    throw input;
            }
        }
        catch (const string &exception)
        {
            Logger::error << "Введена >> " << exception
                          << " - неверная команда!" << endl;
            cerr << "Вы ввели >> " << exception
                 << " - неверная команда! Попробуйте ввести заново: "
                 << endl;
            changePersonalData();
        }
        catch(const exception &ex)
        {
            Logger::error << "Ошибка >> " << ex.what() << endl;
            cerr << "Ошибка >> " << ex.what() << endl;
        }
        catch(...)
        {
            Logger::error << "Неизвестная ошибка!" << endl;
            cerr << "Неизвестная ошибка!" << endl;
            exit(0);
        }
    }
}

void Director::addNewEmployeeData()
{
    data_->newEmployeeData();
}

void Director::functional()
{
    displayUser();
    checkData();
    
    string input;
    while (true)
    {
        cout << "Хотите изменить личные данные? - нажмите 1" << endl;
        cout << "Хотите вывести данные данные всех сотрудников? - нажмите 2" << endl;
        cout << "Хотите изменить чужие данные? - нажмите 3" << endl;
        cout << "Хотите добавить нового сотрудника? - нажмите 4" << endl;
        cout << "Хотите вывести лог файла? - нажмите 5" << endl;
        cout << "Хотите вернуться назад? - введите B: " << endl;
        cout << "Хотите выйти из программы? - введите ESC: " << endl;
        try
        {
            cin >> input;
            toLower(input);
            switch (str(input.c_str()))
            {
                case str("1") :
                    changePersonalData();
                    break;
                    
                case str("2") :
                    data_->getAllOtherData();
                    break;
                    
                case str("3") :
                    addNewEmployeeData();
                    break;
                    
                case str("4") :
                    addNewEmployeeData();
                    break;
                    
                case str("5") :
                    Logger::printLog();
                    break;
                    
                case str("b") :
                    return;

                case str("esc") :

                    Logger::info << "Выход из аккаунта << " << position_   << " "
                                                            << surname_    << " "
                                                            << name_       << " "
                                                            << patronymic_ << endl;
                    cout << "Вы вышли из аккаунта." << endl;
                    exit(0);

                default:
                    throw input;
            }
        }
        catch (const string &exception)
        {
            Logger::error << "Введена >> " << exception
                          << " - неверная команда!" << endl;
            cerr << "Вы ввели >> " << exception
                 << " - неверная команда! Попробуйте ввести заново: "
                 << endl;
            changePersonalData();
        }
        catch(const exception &ex)
        {
            Logger::error << "Ошибка >> " << ex.what() << endl;
            cerr << "Ошибка >> " << ex.what() << endl;
        }
        catch(...)
        {
            Logger::error << "Неизвестная ошибка!" << endl;
            cerr << "Неизвестная ошибка!" << endl;
            exit(0);
        }
    }
}

void Director::setPremium(int premium)
{
    salary_ += premium;
}
void Director::setFine(int fine)
{
    salary_ -= fine;
}



