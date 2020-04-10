#include <boost/filesystem.hpp>

#include "Data.h"
#include "Logger.h"
#include "Utils.h"

using namespace boost::filesystem;
using namespace utils;

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

void Data::loadData(const string &position)
{
    
}

void Data::loadDatabase(const string &directoryPath)
{
    objectFactory_.add<Accountant>("Бухгалтер");
    objectFactory_.add<Driver>("Водитель");
    objectFactory_.add<ChiefAccountant>("Главный_бухгалтер");
    objectFactory_.add<ChiefLegalCounsel>("Главный_юрист-консультант");
    objectFactory_.add<Loader>("Грузчик");
    objectFactory_.add<Director>("Директор");
    objectFactory_.add<Logistician>("Логист");
    objectFactory_.add<PurchasingManager>("Менеджер_по_закупкам");
    objectFactory_.add<SalesManager>("Менеджер_по_продажам");
    objectFactory_.add<Cashier>("Кассир");
    objectFactory_.add<HeadOfProcurement>("Начальник_отдела_закупок");
    objectFactory_.add<HeadOfWarehouse>("Начальник_склада");
    objectFactory_.add<Lawyer>("Юрист");
    
    try
    {
        for (directory_entry &filePath: directory_iterator(directoryPath))
        {
            string fileName = getNameWithoutExtension(filePath.path().string());
            auto result = find(positions.begin(), positions.end(), fileName);
            if (result != positions.end())
            {
                string line;
                std::ifstream file(filePath.path().string());
                if (file.is_open())
                {
                    while (getline(file, line))
                    {
                        auto object = objectFactory_.get(fileName)();
                        Logger::info << " ---------- Считывание данных сотрудника ---------- " << endl;
                        line >> *object;
                        auto result = find_if(tradingCompanyObjects_.begin(), tradingCompanyObjects_.end(),
                                              [&object](shared_ptr<TradingCompany> &tradingCompanyObject)
                                              {
                                                  return *object == *tradingCompanyObject;
                                              });
                        if (result != tradingCompanyObjects_.end())
                        {
                            Logger::warning << "[DELETION] Запись-дубликат" << endl;
                            delete object;
                            continue;
                        }
                        checkData(object);
                        tradingCompanyObjects_.push_back(shared_ptr<TradingCompany>(object));
                        if (file.eof())
                        {
                            break;
                        }
                    }
                }
                else
                {
                    Logger::error << "Невозможно открыть файл >> " << fileName << endl;
                }
            }
            else
            {
                throw fileName;
            }
        }
    }
    catch(const string &exception)
    {
        Logger::error << "Неверное название файла >> " << exception << endl;
    }

    catch(const exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!" << endl;
    }
}

void Data::inputPassword()
{
    string input;
    cerr << "Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: " << endl;
    try
    {
        cin >> input;
        for (const auto &tradingCompanyObject: tradingCompanyObjects_)
        {
            if (input == tradingCompanyObject->getPassword())
            {
                if (tradingCompanyObject->hasDublicatePassword())
                {
                    cerr << "Введите номер паспорта (например, 4516561974)" << endl;
                    cin >> input;
                    if (strtoul(input.c_str(), NULL, 0) != tradingCompanyObject->getPassport())
                    {
                        cerr << "Введенный паспорт не совпадает с вашим паспортом!" << endl;
                        inputPassword();
                    }
                }
                checkPassword(tradingCompanyObject);
                tradingCompanyObject->functional();
            }
        }
        toLower(input);
        if(input == "esc")
        {
            Logger::info << "Выход из программы." << endl;
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
        Logger::error << "Введена >> " << exception
                      << " - неверная команда!" << endl;
        cerr << "Вы ввели >> " << exception
             << " - неверная команда! Попробуйте ввести заново: "
             << endl;
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

void Data::newEmployeeData()
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
    auto object = data.objectFactory_.get(input)();
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
//                   bind(&TradingCompany::checkDateOfHiring, object, ""), object);
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
