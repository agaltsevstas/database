#include <boost/filesystem.hpp>

#include "Data.h"

void Data::checkData(TradingCompany *object)
{
    for (const auto &tradingCompanyObject: tradingCompanyObjects_)
    {
        if (object->id_ == tradingCompanyObject->id_)
        {
            object->changeStatusId();
        }
        if (object->passport_ == tradingCompanyObject->passport_)
        {
            object->changeStatusPassport();
        }
        if (object->phone_ == tradingCompanyObject->phone_)
        {
            object->changeStatusPhone();
        }
        if (object->email_ == tradingCompanyObject->email_)
        {
            object->changeStatusEmail();
        }
        if (object->password_ == tradingCompanyObject->password_)
        {
            tradingCompanyObject->changeStatusPassword(false, false);
            object->changeStatusPassword(false, true);
        }
    }
}

void Data::loadDatabase(const std::string &directoryPath)
{
    objectFactory_.add<Accountant>("Бухгалтер");
    objectFactory_.add<Driver>("Водитель");
    objectFactory_.add<ChiefAccountant>("Главный_бухгалтер");
    objectFactory_.add<ChiefLegalCounsel>("Главный_юрист-консультант");
    objectFactory_.add<Loader>("Грузчик");
    objectFactory_.add<Director>("Директор");
    objectFactory_.add<Logistician>("Логист");
    objectFactory_.add<PurchasingManager>("Менеджер_по_закупкам");
    objectFactory_.add<SalesManager>("Менеджер_по_продажам");
    objectFactory_.add<Cashier>("Кассир");
    objectFactory_.add<HeadOfProcurement>("Начальник_отдела_закупок");
    objectFactory_.add<HeadOfWarehouse>("Начальник_склада");
    objectFactory_.add<HRManager>("Менеджер_по_персоналу");
    objectFactory_.add<Lawyer>("Юрист");
    
    Logger::info << " ---------- Считывание данных всех сотрудников ---------- " << std::endl;
    for (boost::filesystem::directory_entry &filePath: boost::filesystem::directory_iterator(directoryPath))
    {
        try
        {
            std::string fileName = utils::getNameWithoutExtension(filePath.path().string());
            auto result = std::find(positions.begin(), positions.end(), fileName);
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
            Logger::info << " ************************************************** " << std::endl;
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
            if (input == object->password_)
            {
                if (object->hasDublicatePassword())
                {
                    std::cout << "Введите номер паспорта (например, 4516561974)" << std::endl;
                    std::cin >> input;
                    if (strtoul(input.c_str(), NULL, 0) != object->passport_)
                    {
                        std::cerr << "Введенный паспорт не совпадает с вашим паспортом!" << std::endl;
                        inputPassword();
                    }
                }
                object->displayUser();
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

template<class Class> void Data::checkParameter(Parameter<Class> &parameter)
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

template<class Class> Data::Parameter<Class> Data::selectParameter(const Field &field, Class *object, const std::string &message)
{
    try
    {
        switch (field)
        {
            case FIELD_POSITION :
                return {FIELD_POSITION, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getPosition},
                        std::bind(&TradingCompany::checkPosition, object, message),
                        std::bind(&TradingCompany::changeStatusPosition, object), object};

            case FIELD_SURNAME :
                return {FIELD_SURNAME, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getSurname},
                        std::bind(&TradingCompany::checkSurname, object, message),
                        std::bind(&TradingCompany::changeStatusSurname, object), object};

            case FIELD_NAME :
                return {FIELD_NAME, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getName},
                        std::bind(&TradingCompany::checkName, object, message),
                        std::bind(&TradingCompany::changeStatusName, object), object};

            case FIELD_PATRONYMIC :
                return {FIELD_PATRONYMIC, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getPatronymic},
                        std::bind(&TradingCompany::checkPatronymic, object, message),
                        std::bind(&TradingCompany::changeStatusPatronymic, object), object};

            case FIELD_SEX :
                return {FIELD_SEX, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getSex},
                        std::bind(&TradingCompany::checkSex, object, message),
                        std::bind(&TradingCompany::changeStatusSex, object), object};

            case FIELD_DATE_OF_BIRTH :
                return {FIELD_DATE_OF_BIRTH, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                        std::bind(&TradingCompany::checkDateOfBirth, object, message),
                        std::bind(&TradingCompany::changeStatusDateOfBirth, object), object};

            case FIELD_PASSPORT :
                return {FIELD_PASSPORT, nullptr, std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport}, nullptr,
                        std::bind(&TradingCompany::checkPassport, object, message),
                        std::bind(&TradingCompany::changeStatusPassport, object, true), object, true};

            case FIELD_PHONE :
                return {FIELD_PHONE, nullptr, std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone}, nullptr,
                        std::bind(&TradingCompany::checkPhone, object, message),
                        std::bind(&TradingCompany::changeStatusPhone, object, true), object, true};

            case FIELD_EMAIL :
                return {FIELD_EMAIL, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getEmail},
                        std::bind(&TradingCompany::checkEmail, object, message),
                        std::bind(&TradingCompany::changeStatusEmail, object, true), object, true};

            case FIELD_DATE_OF_HIRING :
                return {FIELD_DATE_OF_HIRING, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                        std::bind(&TradingCompany::checkDateOfHiring, object, message),
                        std::bind(&TradingCompany::changeStatusDateOfHiring, object), object};

            case FIELD_WORKING_HOURS :
                return {FIELD_WORKING_HOURS, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                        std::bind(&TradingCompany::checkWorkingHours, object, message),
                        std::bind(&TradingCompany::changeStatusWorkingHours, object), object};

            case FIELD_SALARY :
                return {FIELD_SALARY, std::function<uint(TradingCompany&)>{&TradingCompany::getSalary}, nullptr, nullptr,
                        std::bind(&TradingCompany::checkSalary, object, message),
                        std::bind(&TradingCompany::changeStatusSalary, object), object};

            case FIELD_PASSWORD :
                return {FIELD_PASSWORD, nullptr, nullptr, std::function<std::string(TradingCompany&)>{&TradingCompany::getPassword},
                        std::bind(&TradingCompany::checkPassword, object, message),
                        std::bind(&TradingCompany::changeStatusPassword, object, true, true), object, true};
            default:
                throw field;
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Невернное значение >> " << exception << std::endl;
    }
    catch(const Field &field)
    {
        Logger::error << "Неверный параметр поля >> " + std::to_string(field) << std::endl;
    }
    catch(const std::exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << std::endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!";
    }
    return Parameter<Class>();
}

template<class C> void Data::checkParameters(C *object, const bool isWarning)
{
    std::string message;
    for (size_t field = FIELD_POSITION; field != FIELD_PASSWORD + 1; ++field)
    {
        if (isWarning)
        {
            message = warnings[field];
        }
        auto parameter = selectParameter(static_cast<Field>(field), object, message);
        checkParameter(parameter);
    }
}

template<class C> void Data::checkPassword(C &object)
{
    object->checkPassword();
}

void Data::printPersonalData(TradingCompany *object)
{
    std::cout << *object << std::endl;
}

void Data::changeData(TradingCompany *object, TradingCompany *otherObject)
{
    bool isDirector = false;
    std::string input;
    std::string message;
    std::shared_ptr<Director> pointer = nullptr;
    auto tradingCompanyPtr = std::shared_ptr<TradingCompany>(object);
    if (pointer = std::dynamic_pointer_cast<Director>(tradingCompanyPtr))
    {
        isDirector = true;
    }
    
    if (otherObject && otherObject != object)
    {
        message = "Измение данных сотрудника >> " + otherObject->position_ + " "
        + otherObject->surname_  + " "
        + otherObject->name_     + " "
        + otherObject->patronymic_;
    }
    else
    {
        otherObject = object;
        message = "Изменение личных данных";
    }
    while (true)
    {
        std::cout << message << std::endl;
        if (isDirector)
        {
            std::cout << "Изменить должность - нажмите 1" << std::endl;
            std::cout << "Изменить фамилию - нажмите 2" << std::endl;
            std::cout << "Изменить имя - нажмите 3" << std::endl;
            std::cout << "Изменить отчество - нажмите 4" << std::endl;
            std::cout << "Изменить пол - нажите 5" << std::endl;
            std::cout << "Изменить дату рождения - нажмите 6" << std::endl;
            std::cout << "Изменить номер паспорта - нажмите 7" << std::endl;
        }
        std::cout << "Изменить свой номер телефона - нажмите 8" << std::endl;
        if (isDirector)
        {
            std::cout << "Изменить почту - нажмите 9" << std::endl;
            std::cout << "Изменить дату принятия на работу - нажмите 10" << std::endl;
            std::cout << "Изменить часы работы - нажмите 11" << std::endl;
            std::cout << "Изменить зарплату - нажмите 12" << std::endl;
        }
        std::cout << "Изменить пароль к доступу - нажмите 13" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
        try
        {
            std::cin >> input;
            utils::toLower(input);
            if (isDirector && input == "1")
            {
                std::cout << "При изменении должности теряются полномочия" << std::endl;
                std::cout << "Введите yes - для продолжения, no - для отмены" << std::endl;
                std::cout << "Ввод: " << std::endl;
                std::string input;
                std::cin >> input;
                utils::toLower(input);
                if (input == "yes")
                {
                    std::cout << "Выберите одну из предложенных должностей: " << std::endl;
                    copy(positions.begin(), positions.end(), std::ostream_iterator<std::string>(std::cout, " "));
                    otherObject->changeStatusPosition();
                    selectParameter(FIELD_POSITION, otherObject, "");
                }
                else if (input == "no")
                {
                    changeData(otherObject);
                }
            }
            else if (isDirector && input == "2")
            {
                otherObject->changeStatusSurname();
                selectParameter(FIELD_SURNAME, otherObject, "");
            }
            else if (isDirector && input == "3")
            {
                otherObject->changeStatusName();
                selectParameter(FIELD_NAME, otherObject, "");
            }
            else if (isDirector && input == "4")
            {
                otherObject->changeStatusPatronymic();
                selectParameter(FIELD_PATRONYMIC, otherObject, "");
            }
            else if (isDirector && input == "5")
            {
                otherObject->changeStatusSex();
                selectParameter(FIELD_SEX, otherObject, "");
            }
            else if (isDirector && input == "6")
            {
                otherObject->changeStatusDateOfBirth();
                selectParameter(FIELD_DATE_OF_BIRTH, otherObject, "");
            }
            else if (isDirector && input == "7")
            {
                otherObject->changeStatusPassport(true);
                selectParameter(FIELD_PASSPORT, otherObject, "");
            }
            else if (input == "8")
            {
                otherObject->changeStatusPhone(true);
                selectParameter(FIELD_PHONE, otherObject, "");
            }
            else if (isDirector && input == "9")
            {
                otherObject->changeStatusEmail(true);
                selectParameter(FIELD_EMAIL, otherObject, "");
            }
            else if (isDirector && input == "10")
            {
                otherObject->changeStatusDateOfHiring();
                selectParameter(FIELD_DATE_OF_HIRING, otherObject, "");
            }
            else if (isDirector && input == "11")
            {
                otherObject->changeStatusWorkingHours();
                selectParameter(FIELD_WORKING_HOURS, otherObject, "");
            }
            else if (isDirector && input == "12")
            {
                otherObject->changeStatusSalary();
                selectParameter(FIELD_SALARY, otherObject, "");
            }
            else if (input == "13")
            {
                otherObject->changeStatusPassword(true);
                selectParameter(FIELD_PASSWORD, otherObject, "");
            }
            else if (input == "b")
            {
                return;
            }
            else if (input == "esc")
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
            changeData(object, otherObject);
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
}

bool Data::find(const std::string &str, const std::string &parameter) const
{
    std::size_t found = str.find(parameter);
    return found != std::string::npos ? true : false;
}

TradingCompany *Data::findParameter(const std::string &parameter)
{
    std::vector<std::shared_ptr<TradingCompany>> foundObjects;
    for (const auto &object: tradingCompanyObjects_)
    {
        bool found = false;
        std::string stringParameter;
        stringParameter = std::to_string(object->id_);
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->surname_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->name_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->patronymic_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->sex_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->dateOfBirth_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = std::to_string(object->passport_);
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = std::to_string(object->phone_);
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->email_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->dateOfHiring_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->workingHours_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = std::to_string(object->salary_);
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
        stringParameter = object->password_;
        found = find(stringParameter, parameter);
        if (found)
        {
            foundObjects.push_back(object);
            continue;
        }
    }
    if (foundObjects.size() == 1)
    {
        auto object = foundObjects.at(0);
        return &(*foundObjects.at(0));
    }
    else if (foundObjects.size() > 1)
    {
        std::cout << "Найденные объекты: " << std::endl;
        for (const auto &object: foundObjects)
        {
            std::cout << *object << std::endl;
        }
        std::cout << "Введите id конкретного сотрудника" << std::endl;
    }
    return nullptr;
}

void Data::changeOtherData(TradingCompany *object)
{
    std::cout << "Найдите сотрудника по одному из предложенных параметров (или его части): " << std::endl;
    std::cout << "ID (например, 100), позиция (например, Директор), фамилия (например, Агальцев), "
              << "имя (например, Стас), отчество (например, Сергеевич), пол (например, Муж), "
              << "дата рождения (например, 16.12.1995), паспорт (например, 4516561974), "
              << "телефон (например, 9032697963), почта (например, surname.name.patronymic@tradingcompany.ru) "
              << "дата принятия на работу (например, 16.04.2018), время работы (например, Понедельник-Пятница=09:00-18:00) "
              << "зарплата (в рублях), пароль" << std::endl;
    std::string input;
    std::cin >> input;
    auto foundObject = findParameter(input);
    foundObject ? changeData(object, foundObject) :changeOtherData(object);
}

void Data::getAllOtherData() const
{
    for (const auto &object: tradingCompanyObjects_)
    {
        std::cout << *object << std::endl;
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
        auto found = std::find(positions.begin(), positions.end(), input);
        if (found != positions.end())
        {
            auto object = objectFactory_.get(input)();
            Logger::info << "Добавление нового сотрудника с должностью >> " << input << std::endl; 
            std::cout << "Добавление нового сотрудника с должностью >> " << input << std::endl;
            checkParameters(object, true);
            pushBack(*object);
            Logger::info << "Сотрудник " + object->surname_ + " " +
                                           object->name_ + " " +
                                           object->patronymic_ + " успешно добавлен"<< std::endl;
            std::cout << "Сотрудник " + object->surname_ + " " +
                                        object->name_ + " " +
                                        object->patronymic_ + " успешно добавлен"<< std::endl;
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
