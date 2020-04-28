#include <boost/filesystem.hpp>

#include "Data.h"

void Data::loadDatabase(const std::string &directoryPath)
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
    objectFactory_.add<HRManager>("HRManager.h");
    objectFactory_.add<Lawyer>("Юрист");
    
    Logger::info << " ---------- Считывание данных всех сотрудников ---------- " << std::endl;
    for (boost::filesystem::directory_entry &filePath: boost::filesystem::directory_iterator(directoryPath))
    {
        try
        {
            std::string fileName = utils::getNameWithoutExtension(filePath.path().string());
            auto result = find(positions.begin(), positions.end(), fileName);
            if (result != positions.end())
            {
                std::string line;
                std::ifstream file(filePath.path().string());
                if (file.is_open())
                {
                    while (getline(file, line))
                    {
                        auto object = objectFactory_.get(fileName)();
                        Logger::info << " ********** Считывание данных сотрудника ********** " << std::endl;
                        line >> *object;
                        auto result = find_if(tradingCompanyObjects_.begin(), tradingCompanyObjects_.end(),
                                              [&object](std::shared_ptr<TradingCompany> &tradingCompanyObject)
                                              {
                                                  return *object == *tradingCompanyObject;
                                              });
                        if (result != tradingCompanyObjects_.end())
                        {
                            Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                            delete object;
                            continue;
                        }
                        checkData(object);
                        tradingCompanyObjects_.push_back(std::shared_ptr<TradingCompany>(object));
                        if (file.eof())
                        {
                            break;
                        }
                    }
                }
                else
                {
                    Logger::error << "Невозможно открыть файл >> " << fileName << std::endl;
                }
            }
            else
            {
                throw fileName;
            }
        }
        catch(const std::string &exception)
        {
            Logger::error << "Неверное название файла >> " << exception << std::endl;
        }
        
        catch(const std::exception &ex)
        {
            Logger::error << "Ошибка >> " << ex.what() << std::endl;
        }
        catch(...)
        {
            Logger::error << "Неизвестная ошибка!" << std::endl;
        }
    }
    Logger::info << " ---------- Конец считывания всех данных сотрудников ---------- " << std::endl;
}

void Data::inputPassword()
{
    std::cout << "Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: " << std::endl;
    std::string input;
    try
    {
        std::cin >> input;
        Logger::info << std::setfill('.') << std::setw(80) << "" << std::left << std::endl;
        for (const auto &object: tradingCompanyObjects_)
        {
            if (input == object->getPassword())
            {
                if (object->hasDublicatePassword())
                {
                    std::cout << "Введите номер паспорта (например, 4516561974)" << std::endl;
                    std::cin >> input;
                    if (strtoul(input.c_str(), NULL, 0) != object->getPassport())
                    {
                        std::cerr << "Введенный паспорт не совпадает с вашим паспортом!" << std::endl;
                        inputPassword();
                    }
                }
                checkPassword(object);
                checkParameters(&(*object));
                object->functional();
                inputPassword();
            }
        }
        if(utils::toLower(input) == "esc")
        {
            Logger::info << "Выход из программы" << std::endl;
            std::cout << "Вы вышли из программы" << std::endl;
            exit(0);
        }
        else
        {
            throw input;
        }
    }
    catch (const std::string &exception)
    {
        Logger::info << " ---------- Попытка войти в аккаунт ---------- " << std::endl;
        Logger::error << "Введен >> " << exception << " - неверный пароль!" << std::endl;
        std::cerr << "Вы ввели >> " << exception
                  << " - неверный пароль! Попробуйте ввести заново: " << std::endl;
        inputPassword();
    }
    catch(const std::exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << std::endl;
        std::cerr << "Ошибка >> " << ex.what() << std::endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!" << std::endl;
        std::cerr << "Неизвестная ошибка!" << std::endl;
        exit(0);
    }
}

template<class C> void Data::checkParameter(Parameter<C> &parameter)
{
    auto getUintParameter = parameter.getUintParameter;
    auto getUint64Parameter = parameter.getUint64Parameter;
    auto getStringParameter = parameter.getStringParameter;
    auto checkParameter = parameter.checkParameter;
    auto changeStatusParameter = parameter.changeStatusParameter;
    auto object = parameter.object;
    bool isMatchCheck = parameter.isMatchCheck;
    
    checkParameter();
    
    if (isMatchCheck)
    {
        for (auto it = std::begin(tradingCompanyObjects_); it != std::end(tradingCompanyObjects_);)
        {
            if (getUintParameter != nullptr && (&(*(*it)) != object) &&
                getUintParameter(*(*it)) == getUintParameter(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = tradingCompanyObjects_.begin();
            }
            else if (getUint64Parameter != nullptr && (&(*(*it)) != object) &&
                     getUint64Parameter(*(*it)) == getUint64Parameter(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = tradingCompanyObjects_.begin();
            }
            else if (getStringParameter != nullptr && (&(*(*it)) != object) &&
                     getStringParameter(*(*it)) == getStringParameter(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = tradingCompanyObjects_.begin();
            }
            else
            {
                ++it;
            }
        }
    }
}

template<class C> Data::Parameter<C> Data::selectParameter(const Field &field, C *object, const std::string &message)
{
    switch (field)
    {
        case FIELD_ID :
        {
            return {FIELD_ID, std::function<uint(TradingCompany&)>{&TradingCompany::getId},
                    nullptr, nullptr, std::bind(&TradingCompany::checkId, object, message),
                    std::bind(&TradingCompany::changeStatusId, object, true), object, true};
        }

        case FIELD_POSITION :
        {
            return {FIELD_POSITION, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getPosition},
                    std::bind(&TradingCompany::checkPosition, object, message),
                    std::bind(&TradingCompany::changeStatusPosition, object), object};
        }

        case FIELD_SURNAME :
        {
            return {FIELD_SURNAME, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getSurname},
                    std::bind(&TradingCompany::checkSurname, object, message),
                    std::bind(&TradingCompany::changeStatusSurname, object), object};
        }

        case FIELD_NAME :
        {
            return {FIELD_NAME, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getName},
                    std::bind(&TradingCompany::checkName, object, message),
                    std::bind(&TradingCompany::changeStatusName, object), object};
        }

        case FIELD_PATRONYMIC :
        {
            return {FIELD_PATRONYMIC, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getPatronymic},
                    std::bind(&TradingCompany::checkPatronymic, object, message),
                    std::bind(&TradingCompany::changeStatusPatronymic, object), object};
        }

        case FIELD_SEX :
        {
            return {FIELD_SEX, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getSex},
                    std::bind(&TradingCompany::checkSex, object, message),
                    std::bind(&TradingCompany::changeStatusSex, object), object};
        }

        case FIELD_DATE_OF_BIRTH :
        {
            return {FIELD_DATE_OF_BIRTH, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                    std::bind(&TradingCompany::checkDateOfBirth, object, message),
                    std::bind(&TradingCompany::changeStatusDateOfBirth, object), object};
        }

        case FIELD_PASSPORT :
        {
            return {FIELD_PASSPORT, nullptr, std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport}, nullptr,
                    std::bind(&TradingCompany::checkPassport, object, message),
                    std::bind(&TradingCompany::changeStatusPassport, object, true), object, true};
        }

        case FIELD_PHONE :
        {
            return {FIELD_PHONE, nullptr, std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone}, nullptr,
                    std::bind(&TradingCompany::checkPhone, object, message),
                    std::bind(&TradingCompany::changeStatusPhone, object, true), object, true};
        }

        case FIELD_EMAIL :
        {
            return {FIELD_EMAIL, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getEmail},
                    std::bind(&TradingCompany::checkEmail, object, message),
                    std::bind(&TradingCompany::changeStatusEmail, object, true), object, true};
        }

        case FIELD_DATE_OF_HIRING :
        {
            return {FIELD_DATE_OF_HIRING, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                    std::bind(&TradingCompany::checkDateOfHiring, object, message),
                    std::bind(&TradingCompany::changeStatusDateOfHiring, object), object};
        }

        case FIELD_WORKING_HOURS :
        {
            return {FIELD_WORKING_HOURS, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                    std::bind(&TradingCompany::checkWorkingHours, object, message),
                    std::bind(&TradingCompany::changeStatusWorkingHours, object), object};
        }

        case FIELD_SALARY :
        {
            return {FIELD_SALARY, std::function<uint(TradingCompany&)>{&TradingCompany::getSalary}, nullptr, nullptr,
                    std::bind(&TradingCompany::checkSalary, object, message),
                    std::bind(&TradingCompany::changeStatusSalary, object), object};
        }

        case FIELD_PASSWORD :
        {
            return {FIELD_PASSWORD, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getPassword},
                    std::bind(&TradingCompany::checkPassword, object, message),
                    std::bind(&TradingCompany::changeStatusPassword, object, true, true), object, true};
        }
    }
}

void Data::checkParameters(TradingCompany *object)
{
    for (const auto &[key, value]: (*object).fieldStatus_)
    {
        auto parameter = selectParameter(key, object, "");
        checkParameter(parameter);
    }
}

void Data::checkData(TradingCompany *object)
{
    for (const auto &tradingCompanyObject: tradingCompanyObjects_)
    {
        if (object->getId() == tradingCompanyObject->getId())
        {
            object->changeStatusId();
        }
        if (object->getPassport() == tradingCompanyObject->getPassport())
        {
            object->changeStatusPassport();
        }
        if (object->getPhone() == tradingCompanyObject->getPhone())
        {
            object->changeStatusPhone();
        }
        if (object->getEmail() == tradingCompanyObject->getEmail())
        {
            object->changeStatusEmail();
        }
        if (object->getPassword() == tradingCompanyObject->getPassword())
        {
            tradingCompanyObject->changeStatusPassword(false, false);
            object->changeStatusPassword(false, true);
        }
        break;
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
        std::cout << *tradingCompany << std::endl;
    }
}

void Data::newEmployeeData(const TradingCompany *object)
{
    std::cout << "Выберите одну из предложенных должности: " << std::endl;
    copy(positions.begin(), positions.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
    std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
    std::cout << "Введите должность сотрудника: " << std::endl;
    std::string input;
    try
    {
        std::cin >> input;
        utils::toUpperAndToLower(input);
        auto found = find(positions.begin(), positions.end(), input);
        if (found != positions.end())
        {
            auto object = objectFactory_.get(input)();
            Logger::info << "Добавление нового сотрудника с должностью >> " << input << std::endl; 
            std::cout << "Добавление нового сотрудника с должностью >> " << input << std::endl;
            checkParameters(object);
            pushBack(*object);
            Logger::info << "Сотрудник " + object->getSurname() + " " +
                                           object->getName() + " " +
                                           object->getPatronymic() + " успешно добавлен"<< std::endl;
            std::cout << "Сотрудник " + object->getSurname() + " " +
                                        object->getName() + " " +
                                        object->getPatronymic() + " успешно добавлен"<< std::endl;
        }
        else if(utils::toLower(input) == "b")
        {
            return;
        }
        else if(utils::toLower(input) == "esc")
        {
            EXIT(object);
        }
        else
        {
            throw input;
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
        std::cerr << "Вы ввели >> " << exception
                  << " - неверная команда! Попробуйте ввести заново: " << std::endl;
        newEmployeeData(object);
    }
    catch(const std::exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << std::endl;
        std::cerr << "Ошибка >> " << ex.what() << std::endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!" << std::endl;
        std::cerr << "Неизвестная ошибка!" << std::endl;
        exit(0);
    }
}

template<class C> void Data::pushBack(C &object)
{
    uint maxId = 0;
    std::shared_ptr<C> pointer;
    std::vector<std::shared_ptr<TradingCompany>>::iterator it;
    
    for (it = tradingCompanyObjects_.begin(); it != tradingCompanyObjects_.end(); ++it)
    {
        if ((pointer = std::dynamic_pointer_cast<C>(*it)) && (*it)->getId() > maxId)
        {
            maxId = (*it)->getId();
        }
        else
        {
            break;
        }
    }
    std::string maxIdString = std::to_string(++maxId);
    object.setId(maxIdString);
    tradingCompanyObjects_.insert(it, std::shared_ptr<TradingCompany>(&object));
}

template<class C> void Data::setOtherData(C &object)
{
//    checkParameter(object->getId(),
//                   std::function<uint(TradingCompany&)>{&TradingCompany::getId},
//                   std::bind(&TradingCompany::checkId, object, ""), object, true);
//    checkParameter(object->getPosition(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getPosition},
//                   std::bind(&TradingCompany::checkPosition, object, ""), object);
//    checkParameter(object->getSurname(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getSurname},
//                   std::bind(&TradingCompany::checkSurname, object, ""), object);
//    checkParameter(object->getName(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getName},
//                   std::bind(&TradingCompany::checkName, object, ""), object);
//    checkParameter(object->getPatronymic(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getPatronymic},
//                   std::bind(&TradingCompany::checkPatronymic, object, ""), object);
//    checkParameter(object->getSex()),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getSex},
//                   std::bind(&TradingCompany::checkSex, object, ""), object);
//    checkParameter(object->getDateOfBirth(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
//                   std::bind(&TradingCompany::checkDateOfBirth, object, ""), object);
//    checkParameter(object->getPassport(),
//                   std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
//                   std::bind(&TradingCompany::checkPassport, object, ""), object, true);
//    checkParameter(object->getPhone(),
//                   std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
//                   std::bind(&TradingCompany::checkPhone, object, ""), object, true);
//    checkParameter(object->getEmail(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getEmail},
//                   std::bind(&TradingCompany::checkEmail, object, ""), object, true);
//    checkParameter(object->getDateOfHiring(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
//                    std::bind(&TradingCompany::checkDateOfHiring, object, ""), object);
//    checkParameter(object->getWorkingHours(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getWorkingHours},
//                   std::bind(&TradingCompany::checkWorkingHours, object, ""), object);
//    checkParameter(object->getSalary(),
//                   std::function<uint(TradingCompany&)>{&TradingCompany::getSalary},
//                   std::bind(&TradingCompany::checkSalary, object, ""), object);
//    checkParameter(object->getPassword(),
//                   std::function<std::string(TradingCompany&)>{&TradingCompany::getPassword},
//                   std::bind(&TradingCompany::checkPassword, object, "Ваш пароль неудовлетворяет требованиям!"), object, true);
}
