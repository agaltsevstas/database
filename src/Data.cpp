#include "Data.h"
#include "Utils.h"

using namespace  utils;

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

void Data::setPassword()
{
    string input;
    cout << ("Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: ") << endl;
    try
    {
        cin >> input;
        for (const auto &tradingCompanyObject: tradingCompanyObjects_)
        {
            if (input == tradingCompanyObject->getPassword())
            {
                if (tradingCompanyObject->hasDublicatePassword())
                {
                    cout << "Введите номер паспорта (например, 4516561974)" << endl;
                    cin >> input;
                    if (strtoul(input.c_str(), NULL, 0) != tradingCompanyObject->getPassport())
                    {
                        cout << "Введенный паспорт не совпадает с вашим паспортом!" << endl;
                        setPassword();
                    }
                }
                checkPassword(tradingCompanyObject);
                tradingCompanyObject->functional();
            }
        }
        toLower(input);
        if(input == "esc")
        {
            cout << "Вы вышли из программы!" << endl;
            exit(0);
        }
        else
        {
            throw input;
        }
    }
    catch (const string &exception)
    {
        cout << "Вы ввели: " << exception << " - неверный пароль! Попробуйте ввести заново или закончите выполнение программы, введя ESC: "<< endl;
        setPassword();
    }
    catch(...)
    {
        cout << "Неизвестная ошибка!";
        exit(0);
    }
}

template<class C> void Data::checkPassword(C &object)
{
    object->checkEmail();
}

void Data::getAllOtherData() const
{
    for (const auto &tradingCompany: tradingCompanyObjects_)
    {
        cout << *tradingCompany << endl;
    }
}

template<class C> void Data::pushBack(C &object)
{
    uint maxId = 0;
    shared_ptr<C> pointer;
    vector<shared_ptr<TradingCompany>>::iterator it;
    
    for (it = tradingCompanyObjects_.begin(); it != tradingCompanyObjects_.end(); ++it)
    {
        if ((pointer = dynamic_pointer_cast<C>(*it)) && (*it)->getId() > maxId)
        {
            maxId = (*it)->getId();
        }
        else
        {
            break;
        }
    }
    
    // object.setId(to_string(++maxId));
    tradingCompanyObjects_.insert(it, make_shared<C>(object));
}

void Data::addNewEmployeeData()
{
    Data &data = Data::instance();
//    vector<string> positions;
//
//    cout << "Выберите одну из предложенных должности: " << endl;
//
//    for (const auto &tradingCompany: data.tradingCompanytradingCompanyObjects_)
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
    for (const auto &tradingCompanyObject: data.tradingCompanyObjects_)
    {
        if (input == tradingCompanyObject->getPosition())
        {
            if ((directorPtr_ = dynamic_pointer_cast<Director>(tradingCompanyObject)))
            {
                shared_ptr<Director> director;
                setOtherData(director);
            }
//            if ((chiefAccountantPtr__ = dynamic_pointer_cast<ChiefAccountant>(tradingCompanyObject)))
//            {
//                ChiefAccountant *chiefAccountant;
//                setOtherData(&chiefAccountant);
//            }
//            if ((chiefLegalCounselPtr__ = dynamic_pointer_cast<ChiefLegalCounsel>(tradingCompanyObject)))
//            {
//                ChiefLegalCounsel *chiefLegalCounsel;
//                setOtherData(&chiefLegalCounsel);
//            }
//            if ((headOfProcurementPtr__ = dynamic_pointer_cast<HeadOfProcurement>(tradingCompanyObject)))
//            {
//                HeadOfProcurement *headOfProcurement;
//                setOtherData(&headOfProcurement);
//            }
//            if ((headOfWarehousePtr__ = dynamic_pointer_cast<HeadOfWarehouse>(tradingCompanyObject)))
//            {
//                HeadOfWarehouse *headOfWarehouse;
//                setOtherData(&headOfWarehouse);
//            }
//            if ((salesManagerPtr__ = dynamic_pointer_cast<SalesManager>(tradingCompanyObject)))
//            {
//                SalesManager *salesManager;
//                setOtherData(&salesManager);
//            }
//            if ((cashierPtr__ = dynamic_pointer_cast<Cashier>(tradingCompanyObject)))
//            {
//                Cashier *cashier;
//                setOtherData(&cashier);
//            }
//            if ((accountantPtr__ = dynamic_pointer_cast<Accountant>(tradingCompanyObject)))
//            {
//                Accountant *accountant;
//                setOtherData(&accountant);
//            }
//            if ((logisticianPtr__ = dynamic_pointer_cast<Logistician>(tradingCompanyObject)))
//            {
//                Logistician *logistician;
//                setOtherData(&logistician);
//            }
//            if ((lawyerPtr__ = dynamic_pointer_cast<Lawyer>(tradingCompanyObject)))
//            {
//                Lawyer *lawyer;
//                setOtherData(&lawyer);
//            }
//            if ((purchasingManagerPtr__ = dynamic_pointer_cast<PurchasingManager>(tradingCompanyObject)))
//            {
//                PurchasingManager *purchasingManager;
//                setOtherData(&purchasingManager);
//            }
//            if ((stevedorePtr__ = dynamic_pointer_cast<Stevedore>(tradingCompanyObject)))
//            {
//                Stevedore *stevedore;
//                setOtherData(&stevedore);
//            }
//            if ((driverPtr__ = dynamic_pointer_cast<Driver>(tradingCompanyObject)))
//            {
//                Driver *driver;
//                setOtherData(&driver);
//            }
        }
    }
}

template<class C> void Data::setOtherData(C &object)
{
//    checkParameter(object->getId(),
//                   function<uint(TradingCompany&)>{&TradingCompany::getId},
//                   bind(&TradingCompany::checkId, object, ""), object, true);
//    checkParameter(object->getPosition(),
//                   function<string(TradingCompany&)>{&TradingCompany::getPosition},
//                   bind(&TradingCompany::checkPosition, object, ""), object);
//    checkParameter(object->getSurname(),
//                   function<string(TradingCompany&)>{&TradingCompany::getSurname},
//                   bind(&TradingCompany::checkSurname, object, ""), object);
//    checkParameter(object->getName(),
//                   function<string(TradingCompany&)>{&TradingCompany::getName},
//                   bind(&TradingCompany::checkName, object, ""), object);
//    checkParameter(object->getPatronymic(),
//                   function<string(TradingCompany&)>{&TradingCompany::getPatronymic},
//                   bind(&TradingCompany::checkPatronymic, object, ""), object);
//    checkParameter(object->getSex()),
//                   function<string(TradingCompany&)>{&TradingCompany::getSex},
//                   bind(&TradingCompany::checkSex, object, ""), object);
//    checkParameter(object->getDateOfBirth(),
//                   function<string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
//                   bind(&TradingCompany::checkDateOfBirth, object, ""), object);
//    checkParameter(object->getPassport(),
//                   function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
//                   bind(&TradingCompany::checkPassport, object, ""), object, true);
//    checkParameter(object->getPhone(),
//                   function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
//                   bind(&TradingCompany::checkPhone, object, ""), object, true);
//    checkParameter(object->getEmail(),
//                   function<string(TradingCompany&)>{&TradingCompany::getEmail},
//                   bind(&TradingCompany::checkEmail, object, ""), object, true);
//    checkParameter(object->getDateOfHiring(),
//                   function<string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
//                    bind(&TradingCompany::checkDateOfHiring, object, ""), object);
//    checkParameter(object->getWorkingHours(),
//                   function<string(TradingCompany&)>{&TradingCompany::getWorkingHours},
//                   bind(&TradingCompany::checkWorkingHours, object, ""), object);
//    checkParameter(object->getSalary(),
//                   function<uint(TradingCompany&)>{&TradingCompany::getSalary},
//                   bind(&TradingCompany::checkSalary, object, ""), object);
//    checkParameter(object->getPassword(),
//                   function<string(TradingCompany&)>{&TradingCompany::getPassword},
//                   bind(&TradingCompany::checkPassword, object, "Ваш пароль неудовлетворяет требованиям!"), object, true);
}
