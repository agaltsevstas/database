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
            for (const auto tradingCompanyObject: tradingCompanyObjects_)
            {
                if (input == tradingCompanyObject->getPassword())
                {
                    if ((directorPtr_ = dynamic_pointer_cast<Director>(tradingCompanyObject)))
                    {
                        directorPtr_->functional();
                    }
                    if ((chiefAccountantPtr_ = dynamic_pointer_cast<ChiefAccountant>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*chief_accountant_pointer);
                    }
                    if ((chiefLegalCounselPtr_ = dynamic_pointer_cast<ChiefLegalCounsel>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*chief_legal_counsel_pointer);
                    }
                    if ((headOfProcurementPtr_ = dynamic_pointer_cast<HeadOfProcurement>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*head_of_procurement_pointer);
                    }
                    if ((headOfWarehousePtr_ = dynamic_pointer_cast<HeadOfWarehouse>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*head_of_warehouses_pointer);
                    }
                    if ((salesManagerPtr_ = dynamic_pointer_cast<SalesManager>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*sales_managers_pointer);
                    }
                    if ((cashierPtr_ = dynamic_pointer_cast<Cashier>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*cashier_pointer);
                    }
                    if ((accountantPtr_ = dynamic_pointer_cast<Accountant>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*accountants_pointer);
                    }
                    if ((logisticianPtr_ = dynamic_pointer_cast<Logistician>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*logisticians_pointer);
                    }
                    if ((lawyerPtr_ = dynamic_pointer_cast<Lawyer>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*lawyer_pointer);
                    }
                    if ((purchasingManagerPtr_ = dynamic_pointer_cast<PurchasingManager>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*purchasing_managers_pointer);
                    }
                    if ((stevedorePtr_ = dynamic_pointer_cast<Stevedore>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*stevedores_pointer);
                    }
                    if ((driverPtr_ = dynamic_pointer_cast<Driver>(tradingCompanyObject)))
                    {
    //                    trading_company::change_personal_data(*drivers_pointer);
                    }
                }
            }
            toLower(input);
            if(input == "esc")
            {
                cout << "Вы вышли из программы!" << endl;
                exit(0);
            }
            else
                throw input;
        }
        catch (const string &exception)
        {
            cout << "Вы ввели: " << exception << " - неверный пароль! Попробуйте ввести заново или закончите выполнение программы, введя ESC: "<< endl;
        }
    }
}

void Data::getAllOtherData() const
{
    for (const auto &tradingCompany: tradingCompanyObjects_)
    {
        cout << *tradingCompany << endl;
    }
}

template<class T> void Data::pushBack(T &tradingCompanyObject)
{
    uint maxId = 0;
    shared_ptr<T> pointer;
    vector<shared_ptr<TradingCompany>>::iterator it;
    
    for (it = tradingCompanyObjects_.begin(); it != tradingCompanyObjects_.end(); ++it)
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
    
    // tradingCompanyObject.setId(to_string(++maxId));
    tradingCompanyObjects_.insert(it, make_shared<T>(tradingCompanyObject));
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

template<class T> void Data::setOtherData(T &tradingCompanyObject)
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
