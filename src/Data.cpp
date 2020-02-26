#include "Data.h"
#include "Director.h"
#include "ChiefAccountant.h"
#include "ChiefLegalCounsel.h"
#include "HeadOfProcurement.h"
#include "HeadOfWarehouse.h"
#include "SalesManager.h"
#include "Cashier.h"
#include "Accountant.h"
#include "Logistician.h"
#include "Lawyer.h"
#include "PurchasingManager.h"
#include "Stevedore.h"
#include "Driver.h"

void Data::getAllOtherData() const
{
    for (const auto &tradingCompany: tradingCompanyVector_)
    {
        cout << *tradingCompany << endl;
    }
}

template <class T> void Data::pushBack(T &object)
{
    uint maxId = 0;
    shared_ptr<T> pointer;
    vector<shared_ptr<TradingCompany>>::iterator it;
    
    for (it = tradingCompanyVector_.begin(); it != tradingCompanyVector_.end(); ++it)
    {
        if ((pointer = dynamic_pointer_cast<T>(*it)) && (*it)->getId() > maxId)
        {
            maxId = (*it)->getId();
        }
        else
        {
            break;
        }
    }
    
    // object.setId(to_string(++maxId));
    tradingCompanyVector_.insert(it, make_shared<T>(object));
}

void Data::addNewEmployeeData()
{
    Data &data = Data::getInstance();
//    vector<string> positions;
//
//    cout << "Выберите одну из предложенных должности: " << endl;
//
//    for (const auto &tradingCompany: data.tradingCompanyVector_)
//    {
//        positions.push_back(tradingCompany->getPosition());
//    }
//
//    auto last = unique(positions.begin(), positions.end());
//    positions.erase(last, positions.end());
    copy(positions.begin(), positions.end(), ostream_iterator<string>(cout, "\n"));

    cout << "Введите должность сотрудника: " << endl;
    string input;
    cin >> input;
    for (const auto &object: data.tradingCompanyVector_)
    {
        if (input == object->getPosition())
        {
            if ((directorPtr_ = dynamic_pointer_cast<Director>(object)))
            {
                Director director;
                setOtherData(director);
            }
//            if ((chiefAccountantPtr_ = dynamic_pointer_cast<ChiefAccountant>(object)))
//            {
//                ChiefAccountant *chiefAccountant;
//                setOtherData(&chiefAccountant);
//            }
//            if ((chiefLegalCounselPtr_ = dynamic_pointer_cast<ChiefLegalCounsel>(object)))
//            {
//                ChiefLegalCounsel *chiefLegalCounsel;
//                setOtherData(&chiefLegalCounsel);
//            }
//            if ((headOfProcurementPtr_ = dynamic_pointer_cast<HeadOfProcurement>(object)))
//            {
//                HeadOfProcurement *headOfProcurement;
//                setOtherData(&headOfProcurement);
//            }
//            if ((headOfWarehousePtr_ = dynamic_pointer_cast<HeadOfWarehouse>(object)))
//            {
//                HeadOfWarehouse *headOfWarehouse;
//                setOtherData(&headOfWarehouse);
//            }
//            if ((salesManagerPtr_ = dynamic_pointer_cast<SalesManager>(object)))
//            {
//                SalesManager *salesManager;
//                setOtherData(&salesManager);
//            }
//            if ((cashierPtr_ = dynamic_pointer_cast<Cashier>(object)))
//            {
//                Cashier *cashier;
//                setOtherData(&cashier);
//            }
//            if ((accountantPtr_ = dynamic_pointer_cast<Accountant>(object)))
//            {
//                Accountant *accountant;
//                setOtherData(&accountant);
//            }
//            if ((logisticianPtr_ = dynamic_pointer_cast<Logistician>(object)))
//            {
//                Logistician *logistician;
//                setOtherData(&logistician);
//            }
//            if ((lawyerPtr_ = dynamic_pointer_cast<Lawyer>(object)))
//            {
//                Lawyer *lawyer;
//                setOtherData(&lawyer);
//            }
//            if ((purchasingManagerPtr_ = dynamic_pointer_cast<PurchasingManager>(object)))
//            {
//                PurchasingManager *purchasingManager;
//                setOtherData(&purchasingManager);
//            }
//            if ((stevedorePtr_ = dynamic_pointer_cast<Stevedore>(object)))
//            {
//                Stevedore *stevedore;
//                setOtherData(&stevedore);
//            }
//            if ((driverPtr_ = dynamic_pointer_cast<Driver>(object)))
//            {
//                Driver *driver;
//                setOtherData(&driver);
//            }
        }
    }
}

template <class T> void Data::setOtherData(T &object)
{
    string input;
    Data &data = Data::getInstance();
    cout << ("Введите должность сотрудника") << endl;
    cin >> input;
    object.setPosition(input);
    cout << ("Введите фамилию сотрудника") << endl;
    cin >> input;
    object.setSurname(input);
    cout << ("Введите имя сотрудника") << endl;
    cin >> input;
    object.setName(input);
    cout << ("Введите отчество сотрудника") << endl;
    cin >> input;
    object.setPatronymic(input);
    cout << ("Введите пол сотрудника (например, Муж)") << endl;
    cin >> input;
    object.setSex(input);
    cout << ("Введите дату рождения сотрудника (например, 16.12.1995)") << endl;
    cin >> input;
    object.setDateOfBirth(input);
    cout << ("Введите номер паспорта сотрудника (например, 4516561974)") << endl;
    cin >> input;
    object.setPassport(input);
    cout << ("Введите номер телефона сотрудника (например, 9032697963)") << endl;
    cin >> input;
    object.setPhone(input);
    cout << ("Введите дату принятия сотрудника (например, 16.04.2018)") << endl;
    cin >> input;
    object.setDateOfHiring(input);
    cout << ("Введите время работы сотрудника (например, Понедельник-Пятница=09:00-18:00)") << endl;
    cin >> input;
    object.setWorkingHours(input);
    cout << ("Введите зарплату сотрудника (в рублях)") << endl;
    cin >> input;
    object.setSalary(input);
    cout << ("Введите пароль к доступу сотрудника") << endl;
    cin >> input;
    object.setPassword(input);

    data.pushBack(object);
}
