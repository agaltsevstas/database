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
    while (true)
    {
        cout << ("Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: ") << endl;
        try
        {
            cin >> input;
            for (const auto &tradingCompanyObject: tradingCompanyObjects_)
            {
                if (input == tradingCompanyObject->getPassword())
                {
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
        }
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
                Director director;
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

template<class C> void Data::setOtherData(C &tradingCompanyObject)
{
    string input;
    Data &data = Data::instance();
    cout << ("Введите должность сотрудника") << endl;
    cin >> input;
    tradingCompanyObject.setPosition(input);
    cout << ("Введите фамилию сотрудника") << endl;
    cin >> input;
    tradingCompanyObject.setSurname(input);
    cout << ("Введите имя сотрудника") << endl;
    cin >> input;
    tradingCompanyObject.setName(input);
    cout << ("Введите отчество сотрудника") << endl;
    cin >> input;
    tradingCompanyObject.setPatronymic(input);
    cout << ("Введите пол сотрудника (например, Муж)") << endl;
    cin >> input;
    tradingCompanyObject.setSex(input);
    cout << ("Введите дату рождения сотрудника (например, 16.12.1995)") << endl;
    cin >> input;
    tradingCompanyObject.setDateOfBirth(input);
    cout << ("Введите номер паспорта сотрудника (например, 4516561974)") << endl;
    cin >> input;
    tradingCompanyObject.setPassport(input);
    cout << ("Введите номер телефона сотрудника (например, 9032697963)") << endl;
    cin >> input;
    tradingCompanyObject.setPhone(input);
    cout << ("Введите дату принятия сотрудника (например, 16.04.2018)") << endl;
    cin >> input;
    tradingCompanyObject.setDateOfHiring(input);
    cout << ("Введите время работы сотрудника (например, Понедельник-Пятница=09:00-18:00)") << endl;
    cin >> input;
    tradingCompanyObject.setWorkingHours(input);
    cout << ("Введите зарплату сотрудника (в рублях)") << endl;
    cin >> input;
    tradingCompanyObject.setSalary(input);
    cout << ("Введите пароль к доступу сотрудника") << endl;
    cin >> input;
    tradingCompanyObject.setPassword(input);

    data.pushBack(tradingCompanyObject);
}
