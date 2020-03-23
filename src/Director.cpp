#include "Director.h"
#include "Data.h"
#include "Utils.h"

using namespace utils;

Director::Director() : data_(&Data::instance()) {}

Director::~Director()
{
    delete data_;
}

void Director::checkData()
{
    data_->checkParameter(id_,
                        function<uint(TradingCompany&)>{&TradingCompany::getId},
                        bind(&TradingCompany::checkId, this, ""), this, true);
    data_->checkParameter(position_,
                        function<string(TradingCompany&)>{&TradingCompany::getPosition},
                        bind(&TradingCompany::checkPosition, this, ""), this);
    data_->checkParameter(surname_,
                        function<string(TradingCompany&)>{&TradingCompany::getSurname},
                        bind(&TradingCompany::checkSurname, this, ""), this);
    data_->checkParameter(name_,
                        function<string(TradingCompany&)>{&TradingCompany::getName},
                        bind(&TradingCompany::checkName, this, ""), this);
    data_->checkParameter(patronymic_,
                        function<string(TradingCompany&)>{&TradingCompany::getPatronymic},
                        bind(&TradingCompany::checkPatronymic, this, ""), this);
    data_->checkParameter(sex_,
                        function<string(TradingCompany&)>{&TradingCompany::getSex},
                        bind(&TradingCompany::checkSex, this, ""), this);
    data_->checkParameter(dateOfBirth_,
                        function<string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                        bind(&TradingCompany::checkDateOfBirth, this, ""), this);
    data_->checkParameter(passport_,
                        function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                        bind(&TradingCompany::checkPassport, this, ""), this, true);
    data_->checkParameter(phone_,
                        function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
                        bind(&TradingCompany::checkPhone, this, ""), this, true);
    data_->checkParameter(email_,
                        function<string(TradingCompany&)>{&TradingCompany::getEmail},
                        bind(&TradingCompany::checkEmail, this, ""), this, true);
    data_->checkParameter(dateOfHiring_,
                        function<string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                        bind(&TradingCompany::checkDateOfHiring, this, ""), this);
    data_->checkParameter(workingHours_,
                        function<string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                        bind(&TradingCompany::checkWorkingHours, this, ""), this);
    data_->checkParameter(salary_,
                        function<uint(TradingCompany&)>{&TradingCompany::getSalary},
                        bind(&TradingCompany::checkSalary, this, ""), this);
    data_->checkParameter(password_,
                        function<string(TradingCompany&)>{&TradingCompany::getPassword},
                        bind(&TradingCompany::checkPassword, this, "Ваш пароль неудовлетворяет требованиям!"), this, true);
}

void Director::changePersonalData()
{
    string input;
    while (true)
    {
        cout << "Изменить свой ID - нажмите 0" << endl;
        cout << "Изменить свою должность - нажмите 1" << endl;
        cout << "Изменить свою фамилию - нажмите 2" << endl;
        cout << "Изменить своё имя - нажмите 3" << endl;
        cout << "Изменить своё отчество - нажмите 4" << endl;
        cout << "Изменить свой пол - нажите 5" << endl;
        cout << "Изменить свою дату рождения - нажмите 6" << endl;
        cout << "Изменить свой номер паспорта - нажмите 7" << endl;
        cout << "Изменить свой номер телефона - нажмите 8" << endl;
        cout << "Изменить свою почту - нажмите 9" << endl;
        cout << "Изменить свою дату принятия на работу - нажмите 10" << endl;
        cout << "Изменить свои часы работы - нажмите 11" << endl;
        cout << "Изменить свою зарплату - нажмите 12" << endl;
        cout << "Изменить свой пароль к доступу - нажмите 13" << endl;
        cout << "Хотите вернуться назад? - введите B: " << endl;
        cout << "Хотите выйти из программы? - введите ESC: " << endl;
        try
        {
            cin >> input;
            toLower(input);
            switch (str(input.c_str()))
            {
                case str("1") :
                    checkId();
                    break;
                case str("2") :
                    checkPosition();
                    break;
                case str("3") :
                    checkSurname();
                    break;
                case str("4") :
                    checkName();
                    break;
                case str("5") :
                    checkPatronymic();
                    break;
                case str("6") :
                    cout << "Текущее значение: " <<  getDateOfBirth() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setDateOfHiring(input);
                    break;
                case str("7") :
                    cout << "Текущее значение: " <<  getPassport() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPassport(input);
                    break;
                case str("8") :
                    cout << "Текущее значение: " <<  getPhone() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPhone(input);
                    break;
                case str("9") :
                    cout << "Текущее значение: " <<  getPassword() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPassword(input);
                    break;
                case str("b") :
                    return;
                case str("esc") :
                    cout << "Вы вышли из программы!" << endl;
                    exit(0);
                default:
                    throw input;
            }
        }
        catch (const string &exception)
        {
            cout << "Вы ввели: " << exception << " - неверная команда! Попробуйте ввести заново: "<< endl;
        }
        catch(...)
        {
            cout << "Неизвестная ошибка!";
            exit(0);
        }
    }
}

void Director::functional()
{
    checkData();
    
    string input;
    while (true)
    {
        displayUser();
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
                    data_->changePersonalData(this);
                    break;
                    
                case str("2") :
                    data_->getAllOtherData();
                    break;
                    
                case str("3") :
                    data_->addNewEmployeeData();
                    break;
                    
                case str("4") :
                    data_->addNewEmployeeData();
                    break;
                    
                case str("5") :
//                    Logger::printLogger();
                    break;
                    
//                case str("b") :
//                    return;
//
//                case str("esc") :
//
//                    cout << "Вы вышли из программы!" << endl;
//                    exit(0);
//
//                default:
//                    throw input;
            }
        }
        catch (const string &exception)
        {
            cout << "Вы ввели: " << exception << " - неверная команда! Попробуйте ввести заново: "<< endl;
        }
        catch(...)
        {
            cout << "Неизвестная ошибка!";
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



