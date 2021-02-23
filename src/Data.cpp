#include "ChiefAccountant.h"
#include "ChiefLegalCounsel.h"
#include "Loader.h"
#include "HeadOfProcurement.h"
#include "HeadOfWarehouse.h"
#include "SalesManager.h"
#include "Cashier.h"
#include "Accountant.h"
#include "Logistician.h"
#include "Lawyer.h"
#include "PurchasingManager.h"
#include "Driver.h"
#include "Data.h"
#include "Utils.h"
#include "tinyxml2.h"

Data &Data::instance()
{
    static Data data; // Объект-одиночка
    return data;
}

void Data::readingTxtFile(const boost::filesystem::path &filePath, uint id)
{
    std::string line;
    const std::string fileName = filePath.filename().c_str(); // Получение имени с расширением
    const std::string name = filePath.stem().c_str(); // Получение имени без расширения
    try
    {
        std::ifstream file(filePath.c_str());
        if (file.is_open())
        {
            if (file.peek() == EOF)
            {
                throw "Пустой файл >> " + fileName;
            }
            while (getline(file, line))
            {
                Logger::info << "************* Считывание данных сотрудника *************" << std::endl;
                auto object = objectFactory_.get(name)(); // Получение определенного объекта из фабрики объектов
                object->setId(std::to_string(id));
                line >> *object; // Запись данных в поля объекта
                auto result = find_if(vectorObjects_.begin(), vectorObjects_.end(),
                                      [&object](std::shared_ptr<TradingCompany> &tradingCompanyObject)
                                      {
                                          return *object == *tradingCompanyObject;
                                      });
                if (result != vectorObjects_.end())
                {
                    Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                    delete object;
                    continue;
                }
                vectorObjects_.push_back(std::shared_ptr<TradingCompany>(object));
                ++id;
            }
        }
        else
        {
            throw "Невозможно открыть файл >> " + fileName;
        }
    }
    catch (const std::string &exception)
    {
        Logger::info << std::setfill('*') << std::setw(56) << "" << std::left << std::endl; // Ограничительная линия
        Logger::error << exception << std::endl;
    }
}

void Data::readingXmlFile(const boost::filesystem::path &filePath, uint id)
{
    const char *tag = "tradingCompany";
    const std::string fileName = filePath.filename().c_str(); // Получение имени с расширением
    const std::string name = filePath.stem().c_str(); // Получение имени без расширения
    const char *className = utils::getClassName(*objectFactory_.get(name)()).c_str();
    tinyxml2::XMLDocument doc; // Инициализация документа
    try
    {
        tinyxml2::XMLError eResult = doc.LoadFile(filePath.c_str()); // Проверка на успешность загрузки файла в документ

        if (eResult == tinyxml2::XML_SUCCESS)
        {
            // Корневой узел с меткой, хранящий список дочерних элементов.
            // Необходим для обхода элементов в документе
            tinyxml2::XMLNode *node = doc.FirstChildElement(tag);
            if (node == nullptr)
            {
                throw std::string("Неверный тег файла!");
            }

            // Прохождение по списку элементов корневого узла
            for (const auto *element = node->FirstChildElement(className); element != nullptr; element = element->NextSiblingElement())
            {
                Logger::info << "************* Считывание данных сотрудника *************" << std::endl;
                auto object = objectFactory_.get(name)(); // Получение определенного объекта из фабрики объектов
                object->setId(std::to_string(id));
                for (const auto &[parameter, setParameter]: object->setParameters_)
                {
                    if (setParameter != nullptr)
                    {
                        std::string input;
                        input = element->Attribute(parameter.c_str()); // Получение значения поля по параметру
                        setParameter(*object, input); // Инициализация поля
                    }
                }
                auto result = find_if(vectorObjects_.begin(), vectorObjects_.end(),
                                      [&object](std::shared_ptr<TradingCompany> &tradingCompanyObject)
                                      {
                                          return *object == *tradingCompanyObject;
                                      });
                if (result != vectorObjects_.end())
                {
                    Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                    delete object;
                    continue;
                }
                vectorObjects_.push_back(std::shared_ptr<TradingCompany>(object));
                ++id;
            }
        }
        else
        {            
            throw "Невозможно открыть файл >> " + fileName;
        }
    }
    catch (const std::string &exception)
    {
        Logger::info << std::setfill('*') << std::setw(56) << "" << std::left << std::endl; // Ограничительная линия
        Logger::error << exception << std::endl;
    }
}

void Data::sort()
{
    stable_sort(std::begin(vectorObjects_), std::end(vectorObjects_), []
                (const auto &first, const auto &second)
    {
        return first->id_ < second->id_;
    });
}

void Data::loadDatabase(const std::string &directoryPath)
{
    namespace bs = boost::filesystem;
    
    directoryPath_ = directoryPath;
    // Добавление классов в фабрику объектов
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
    
    Logger::info << "---------- Считывание данных всех сотрудников ----------" << std::endl;
    for (const bs::path &filePath: bs::directory_iterator(directoryPath_))
    {
        try
        {
            const std::string fileName = utils::toUpperAndToLower(filePath.filename().c_str()); // Получение имени с расширением
            const std::string name = filePath.stem().c_str(); // Получение имени без расширения
            const std::string extension = filePath.extension().c_str(); // Получение расширения
            auto found = idPositions.find(name);
            if (found != idPositions.end())
            {
                uint id = found->second;
                if (extension == ".txt" || extension == ".xml")
                {
                    Logger::info << std::setfill('*') << std::setw(56) << "" << std::left << std::endl; // Ограничительная линия
                    Logger::info << "Считывание данных из файла >> " << fileName << std::endl;
                    if (extension == ".txt")
                    {
                        readingTxtFile(filePath, id);
                        filePaths_.push_back(filePath.c_str());
                    }
                    else if (extension == ".xml")
                    {
                        readingXmlFile(filePath, id);
                        filePaths_.push_back(filePath.c_str());
                    }
                }
                else
                {
                    Logger::error << "Неверное расширение файла >> " << fileName << std::endl;
                }
            }
            else
            {
                throw fileName;
            }
        }
        catch (const std::string &exception)
        {
            Logger::info << std::setfill('*') << std::setw(56) << "" << std::left << std::endl; // Ограничительная линия
            Logger::error << "Неверное название файла >> " << exception << std::endl;
        }
    }
    Logger::info << "------- Конец считывания всех данных сотрудников -------" << std::endl;
    Logger::info << std::endl;
    
    if (vectorObjects_.empty())
    {
        Logger::warning << "$$$$$$$$$$$$$ Пустая база данных $$$$$$$$$$$$$" << std::endl;
        Logger::info << "Выход из программы" << std::endl;
        std::cout << "Вы вышли из программы" << std::endl;
        exit(0);
    }
    sort();
}

void Data::accountLogin()
{
    std::cout << "Введите почту или логин и пароль от почты или закончите выполнение программы, введя ESC или ВЫХОД: " << std::endl;
    bool isLoginFound = false;
    try
    {
        std::cout << "Логин или почта: ";
        std::string login;
        std::cin >> login;
        for (const auto &object: vectorObjects_)
        {
            std::string emailCheck, loginCheck;
            emailCheck = loginCheck = object->email_;
            loginCheck.erase(loginCheck.find('@'), loginCheck.size()); // Получение логина от почты
            if (login == emailCheck || login == loginCheck)
            {
                isLoginFound = true;
                break;
            }
        }
        if (utils::toLower(login) == "esc" || utils::toLower(login) == "выход")
        {
            Logger::info << "Выход из программы" << std::endl;
            std::cout << "Вы вышли из программы" << std::endl;
            exit(0);
        }
        
        std::cout << "Пароль: ";
        std::string password;
        std::cin >> password;
        std::cout << std::endl;
        Logger::info << std::setfill('.') << std::setw(56) << "" << std::left << std::endl;
        for (auto object: vectorObjects_)
        {
            if (isLoginFound && password == object->password_)
            {
                LOGIN(object);
                checkParameters(object.get(), true);
                object->functional();
                LOGOUT(object);
                
                accountLogin(); // Рекурсия
            }
        }
        if (utils::toLower(password) == "esc" || utils::toLower(password) == "выход")
        {
            Logger::info << "Выход из программы" << std::endl;
            std::cout << "Вы вышли из программы" << std::endl;
            exit(0);
        }
        else
        {
            throw login + " " + password;
        }
    }
    catch (const std::string &exception)
    {
        Logger::info << "---------- Попытка войти в аккаунт ----------" << std::endl;
        Logger::error << "Введен >> " << exception << " - неверный логин или пароль!" << std::endl;
        std::cerr << "Вы ввели >> " << exception << " - неверный логин или пароль!" << std::endl;
        accountLogin();
    }
}

template<class Class> void Data::checkParameter(Parameter<Class> &parameter)
{
    auto getUint32Parameter = boost::get<std::function<uint32_t(TradingCompany&)>>(&parameter.getParameter);
    auto getUint64Parameter = boost::get<std::function<uint64_t(TradingCompany&)>>(&parameter.getParameter);
    auto getStringParameter = boost::get<std::function<std::string(TradingCompany&)>>(&parameter.getParameter);
    auto checkParameter = parameter.checkParameter;
    auto changeStatusParameter = parameter.changeStatusParameter;
    auto object = parameter.object;
    bool isMatchCheck = parameter.isMatchCheck;
    
    checkParameter();
    
    // Проверка полей, которые имеют высший приоритет, на дублирование данных
    if (isMatchCheck)
    {
        for (auto it = std::begin(vectorObjects_); it != std::end(vectorObjects_);)
        {
            // 1. Используется только один указатель, который != nullptr.
            // 2. Объект не должен совпадать ни с один из объектов вектора.
            // 3. Возвращаемое значение поля объекта должно совпадать со значением поля одного из объектов вектора
            // 4. После изменения значения поля объекта, цикл начинается заново
            if (getUint32Parameter != nullptr && it->get() != object &&
                (*getUint32Parameter)(*(*it)) == (*getUint32Parameter)(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = vectorObjects_.begin();
            }
            else if (getUint64Parameter != nullptr && it->get() != object &&
                     (*getUint64Parameter)(*(*it)) == (*getUint64Parameter)(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = vectorObjects_.begin();
            }
            else if (getStringParameter != nullptr && it->get() != object &&
                     (*getStringParameter)(*(*it)) == (*getStringParameter)(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = vectorObjects_.begin();
            }
            else
            {
                ++it;
            }
        }
    }
}

template<class Class> Data::Parameter<Class> Data::selectParameter(const Field field,
                                                                   Class *object,
                                                                   const std::string &message)
{
    try
    {
        switch (field)
        {
            case FIELD_POSITION :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getPosition},
                        std::bind(&TradingCompany::checkPosition, object, message),
                        std::bind(&TradingCompany::changeStatusPosition, object), object};

            case FIELD_SURNAME :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getSurname},
                        std::bind(&TradingCompany::checkSurname, object, message),
                        std::bind(&TradingCompany::changeStatusSurname, object), object};

            case FIELD_NAME :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getName},
                        std::bind(&TradingCompany::checkName, object, message),
                        std::bind(&TradingCompany::changeStatusName, object), object};

            case FIELD_PATRONYMIC :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getPatronymic},
                        std::bind(&TradingCompany::checkPatronymic, object, message),
                        std::bind(&TradingCompany::changeStatusPatronymic, object), object};

            case FIELD_SEX :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getSex},
                        std::bind(&TradingCompany::checkSex, object, message),
                        std::bind(&TradingCompany::changeStatusSex, object), object};

            case FIELD_DATE_OF_BIRTH :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                        std::bind(&TradingCompany::checkDateOfBirth, object, message),
                        std::bind(&TradingCompany::changeStatusDateOfBirth, object), object};

            case FIELD_PASSPORT :
                return {std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                        std::bind(&TradingCompany::checkPassport, object, message),
                        std::bind(&TradingCompany::changeStatusPassport, object, false), object, true};

            case FIELD_PHONE :
                return {std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPhone},
                        std::bind(&TradingCompany::checkPhone, object, message),
                        std::bind(&TradingCompany::changeStatusPhone, object, false), object, true};

            case FIELD_EMAIL :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getEmail},
                        std::bind(&TradingCompany::checkEmail, object, message),
                        std::bind(&TradingCompany::changeStatusEmail, object, false), object, true};

            case FIELD_DATE_OF_HIRING :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                        std::bind(&TradingCompany::checkDateOfHiring, object, message),
                        std::bind(&TradingCompany::changeStatusDateOfHiring, object), object};

            case FIELD_WORKING_HOURS :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                        std::bind(&TradingCompany::checkWorkingHours, object, message),
                        std::bind(&TradingCompany::changeStatusWorkingHours, object), object};

            case FIELD_SALARY :
                return {std::function<uint32_t(TradingCompany&)>{&TradingCompany::getSalary},
                        std::bind(&TradingCompany::checkSalary, object, message),
                        std::bind(&TradingCompany::changeStatusSalary, object), object};

            case FIELD_PASSWORD :
                return {std::function<std::string(TradingCompany&)>{&TradingCompany::getPassword},
                        std::bind(&TradingCompany::checkPassword, object, message),
                        std::bind(&TradingCompany::changeStatusPassword, object), object};
            default:
                throw field;
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Невернное значение >> " << exception << std::endl;
        std::cerr << "Невернное значение >> " << exception << std::endl;
    }
    catch (const Field field)
    {
        Logger::error << "Неверный параметр поля >> " + std::to_string(field) << std::endl;
        std::cerr << "Неверный параметр поля >> " + std::to_string(field) << std::endl;
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

void Data::printPersonalData(TradingCompany *object)
{
    Logger::info << "***************** Вывод личных данных ******************" << std::endl;
    std::cout << std::endl;
    std::cout << "***************** Вывод личных данных ******************" << std::endl;
    std::cout << *object << std::endl;
}

void Data::changeData(TradingCompany *object, TradingCompany *otherObject)
{
    bool isDirector = false;
    std::string message;
    if (typeid(*object) == typeid(Director)) // Изменять чужие данные имеет полномочия Director
    {
        isDirector = true;
    }
    
    if (otherObject != nullptr && otherObject != object)
    {
        message = "************** Измение данных сотрудника ***************\n>> " +
                  otherObject->position_ + " " +
                  otherObject->surname_  + " " +
                  otherObject->name_     + " " +
                  otherObject->patronymic_ + " <<";
    }
    else
    {
        otherObject = object;
        message = "*************** Изменение личных данных ****************";
    }
    Logger::info << message << std::endl;
    while (true)
    {
        std::cout << std::endl << message << std::endl;
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
        std::cout << "Изменить номер телефона - нажмите 8" << std::endl;
        if (isDirector)
        {
            std::cout << "Изменить почту - нажмите 9" << std::endl;
            std::cout << "Изменить дату принятия на работу - нажмите 10" << std::endl;
            std::cout << "Изменить часы работы - нажмите 11" << std::endl;
            std::cout << "Изменить зарплату - нажмите 12" << std::endl;
        }
        std::cout << "Изменить пароль - нажмите 13" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            if (isDirector && input == "1")
            {
                std::cout << "При изменении должности теряются полномочия" << std::endl;
                std::cout << "Введите yes или да - для продолжения, no или нет - для отмены" << std::endl;
                std::cout << "Ввод: ";
                std::cin >> input;
                utils::tolower(input);
                if (input == "yes" || input == "да")
                {
                    std::cout << "Выберите одну из предложенных должностей: " << std::endl;
                    for (const auto &[key, value]: idPositions)
                    {
                        std::cout << key << " ";
                    }
                    std::cout << std::endl;
                    std::cout << "Ввод: ";
                    std::string position;
                    std::cin >> position;
                    utils::toupperandtolower(position);
                    auto found = idPositions.find(position); // Поиск класса с определенной должностью
                    if (found != idPositions.end())
                    {
                        auto newObject = objectFactory_.get(position)(); // Получение определенного объекта из фабрики объектов
                        newObject->setPosition(position);
                        *newObject = *otherObject; // Запись данных из одного объекта одного класса в другой объект другого класса
                        deleteObject(otherObject);
                        pushBack(*newObject);
                        if (object == otherObject) // После удаления личных данных происходит выход из аккаунта
                        {
                            LOGOUT(object);
                            accountLogin();
                        }
                        Logger::info << message << std::endl;
                    }
                    else
                    {
                        throw position;
                    }
                }
                else if (input == "no" || input == "нет")
                {
                    continue;
                }
                else
                {
                    throw input;
                }
            }
            else if (isDirector && input == "2")
            {
                std::cout << "Текущая фамилия: " << otherObject->surname_ << std::endl;
                otherObject->changeStatusSurname();
                auto parameter = selectParameter(FIELD_SURNAME, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "3")
            {
                std::cout << "Текущее имя: " << otherObject->name_ << std::endl;
                otherObject->changeStatusName();
                auto parameter = selectParameter(FIELD_NAME, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "4")
            {
                std::cout << "Текущее отчество: " << otherObject->patronymic_ << std::endl;
                otherObject->changeStatusPatronymic();
                auto parameter = selectParameter(FIELD_PATRONYMIC, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "5")
            {
                std::cout << "Текущий пол: " << otherObject->sex_ << std::endl;
                otherObject->changeStatusSex();
                auto parameter = selectParameter(FIELD_SEX, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "6")
            {
                std::cout << "Текущая дата рождения: " << otherObject->dateOfBirth_ << std::endl;
                otherObject->changeStatusDateOfBirth();
                auto parameter = selectParameter(FIELD_DATE_OF_BIRTH, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "7")
            {
                std::cout << "Текущий паспорт: " << otherObject->passport_ << std::endl;
                otherObject->changeStatusPassport(true);
                auto parameter = selectParameter(FIELD_PASSPORT, otherObject, "");
                checkParameter(parameter);
            }
            else if (input == "8")
            {
                std::cout << "Текущий телефон: " << otherObject->phone_ << std::endl;
                otherObject->changeStatusPhone(true);
                auto parameter = selectParameter(FIELD_PHONE, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "9")
            {
                std::cout << "Текущая почта: " << otherObject->email_ << std::endl;
                otherObject->changeStatusEmail(true);
                auto parameter = selectParameter(FIELD_EMAIL, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "10")
            {
                std::cout << "Текущее дата принятия на работу: " << otherObject->dateOfHiring_ << std::endl;
                otherObject->changeStatusDateOfHiring();
                auto parameter = selectParameter(FIELD_DATE_OF_HIRING, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "11")
            {
                std::cout << "Текущие часы работы: " << otherObject->workingHours_ << std::endl;
                otherObject->changeStatusWorkingHours();
                auto parameter = selectParameter(FIELD_WORKING_HOURS, otherObject, "");
                checkParameter(parameter);
            }
            else if (isDirector && input == "12")
            {
                std::cout << "Текущая зарплата: " << otherObject->salary_ << std::endl;
                otherObject->changeStatusSalary();
                auto parameter = selectParameter(FIELD_SALARY, otherObject, "");
                checkParameter(parameter);
            }
            else if (input == "13")
            {
                std::cout << "Текущий пароль: " << otherObject->password_ << std::endl;
                otherObject->changeStatusPassword();
                auto parameter = selectParameter(FIELD_PASSWORD, otherObject, "");
                checkParameter(parameter);
            }
            else if (input == "b" || input == "н")
            {
                return;
            }
            else if (input == "esc" || input == "выход")
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
            std::cerr << "Вы ввели >> " << exception << " - неверная команда!" << std::endl;
        }
    }
}

TradingCompany *Data::find(TradingCompany *object)
{
    Logger::info << "************************ Поиск *************************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "************************ Поиск *************************" << std::endl;
        std::cout << "Найдите сотрудника по одному из предложенных параметров (или его части): " << std::endl;
        std::cout << "ID (например, 100), позиция (например, Директор), фамилия (например, Агальцев), "
                  << "имя (например, Стас), отчество (например, Сергеевич), пол (например, Муж), "
                  << "дата рождения (например, 16.12.1995), паспорт (например, 4516561974), "
                  << "телефон (например, 9032697963), почта (например, surname.name.patronymic@tradingcompany.ru) "
                  << "дата принятия на работу (например, 16.04.2018), время работы (например, Понедельник-Пятница=09:00-18:00) "
                  << "зарплата (в рублях), пароль" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            std::string parameter = input;
            utils::tolower(input);
            if (input == "b" || input == "н")
            {
                return nullptr;
            }
            else if (input == "esc" || input == "выход")
            {
                EXIT(object);
            }
            else
            {
                // Вектор объектов, в котором хранятся найденные объекты по определенным полям
                std::vector<std::shared_ptr<TradingCompany>> foundObjects;
                for (const auto &object: vectorObjects_)
                {
                    // Вектор значений полей объекта с учетом верхнего и нижнего регистра букв
                    std::vector<std::pair<std::string, bool>> parameters = {
                        { std::to_string(object->id_), false },
                        { object->position_, true },
                        { object->surname_, true },
                        { object->name_, true },
                        { object->patronymic_, true },
                        { object->sex_, true },
                        { object->dateOfBirth_, false },
                        { std::to_string(object->passport_), false },
                        { std::to_string(object->phone_), false },
                        { object->email_, false },
                        { object->dateOfHiring_, false },
                        { object->workingHours_, false },
                        { std::to_string(object->salary_), false },
                        { object->password_, false }
                    };
                    for (const auto &[param, isUpperAndToLower]: parameters)
                    {
                        parameter = isUpperAndToLower ? utils::toUpperAndToLower(parameter) : parameter;
                        std::size_t found = param.find(parameter);
                        if (found != std::string::npos)
                        {
                            foundObjects.push_back(object);
                            break;
                        }
                    }
                }
                // Один найденный объект
                if (foundObjects.size() == 1)
                {
                    std::cout << "Найденный сотрудник: " << std::endl;
                    std::cout << *foundObjects.at(0) << std::endl;
                    return foundObjects.at(0).get();
                }
                // Больше одного найденного объекта
                else if (foundObjects.size() > 1)
                {
                    std::cout << "Найденные сотрудники: " << std::endl;
                    for (const auto &object: foundObjects)
                    {
                        std::cout << *object << std::endl;
                    }
                    std::cout << "Введите id конкретного сотрудника из предложенных" << std::endl;
                    std::cout << "Ввод: ";
                    std::string input;
                    std::cin >> input;
                    for (const auto &object: foundObjects)
                    {
                        if (input == std::to_string(object->id_)) // Поиск по ID
                        {
                            std::cout << "Найденный сотрудник: " << std::endl;
                            std::cout << *object << std::endl;
                            return object.get();
                        }
                    }
                    throw ("Вы ввели неверный id сотрудника!");
                }
                else
                {
                    throw parameter;
                }
            }
        }
        catch (const char *exception)
        {
            Logger::info << exception << std::endl;
            std::cerr << exception << std::endl;
        }
        catch (const std::string &exception)
        {
            Logger::error << "По запросу << " << exception << " >> ничего не найдено!" << std::endl;
            std::cerr << "По запросу << " << exception << " >> ничего не найдено!" << std::endl;
        }
    }
    return nullptr;
}

void Data::changeOtherData(TradingCompany *object)
{
    auto foundObject = find(object);
    if (foundObject == nullptr)
    {
        return;
    }
    changeData(object, foundObject);
}

void Data::deleteEmployeeData(TradingCompany *object)
{
    while (true)
    {
        try
        {
            auto foundObject = find(object);
            if (foundObject == nullptr) // Объект не найден, тогда возврат
            {
                return;
            }
            object == foundObject ? std::cout << "Вы действительно хотите удалить свой аккаунт?" << std::endl :
            std::cout << "Вы действительно хотите удалить сотрудника << " + foundObject->position_ +   " " +
                                                                            foundObject->surname_ +    " " +
                                                                            foundObject->name_ +       " " +
                                                                            foundObject->patronymic_ + " >> ?" << std::endl;
            std::cout << "Введите yes или да - для продолжения, no или нет - для отмены" << std::endl;
            std::cout << "Ввод: ";
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            if (input == "yes" || input == "да")
            {
                deleteObject(foundObject);
                if (object == foundObject) // После удаления личных данных происходит выход из аккаунта
                {
                    LOGOUT(object);
                    accountLogin();
                }
                else
                {
                    return;
                }
            }
            else if (input == "no" || input == "нет")
            {
                continue;
            }
            else
            {
                throw input;
            }
        }
        catch (const std::string &exception)
        {
            Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
            std::cerr << "Вы ввели >> " << exception << " - неверная команда!" << std::endl;
        }
    }
}

void Data::getAllOtherData() const
{
    Logger::info << "************ Вывод данных всех сотрудников *************" << std::endl;
    std::cout << std::endl;
    std::cout << "************ Вывод данных всех сотрудников *************" << std::endl;
    for (const auto &object: vectorObjects_)
    {
        std::cout << *object << std::endl;
    }
}

template<class C> void Data::pushBack(C &object)
{
    Logger::info << "************* Добавление нового сотрудника *************" << std::endl;
    std::cout << std::endl;
    std::cout << "************* Добавление нового сотрудника *************" << std::endl;
    std::string position = object.position_;
    uint maxId = idPositions.find(position)->second - 1;
    std::vector<std::shared_ptr<TradingCompany>>::iterator it;
    for (it = begin(vectorObjects_); it != end(vectorObjects_); ++it)
    {
        // Проверка двух объектов на то, что они от одного класса
        // Поиск макс ID среди объектов одного класса
        if ((typeid(*it->get()) == typeid(object)) && (*it)->id_ > maxId)
        {
            maxId = (*it)->id_;
        }
    }
    std::string maxIdString = std::to_string(++maxId);
    object.setId(maxIdString);
    vectorObjects_.insert(it, std::shared_ptr<TradingCompany>(&object));
    Logger::info << "Сотрудник << " + object.position_ +   " " +
                                      object.surname_ +    " " +
                                      object.name_ +       " " +
                                      object.patronymic_ + " >> успешно добавлен!" << std::endl;
    std::cout << "Сотрудник << " + object.position_ +   " " +
                                   object.surname_ +    " " +
                                   object.name_ +       " " +
                                   object.patronymic_ + " >> успешно добавлен!" << std::endl;
}

template<class C> void Data::deleteObject(C *object)
{
    Logger::info << "*********************** Удаление ***********************" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************** Удаление ***********************" << std::endl;
    uint deletedId = object->id_;
    std::string typeObject = typeid(*object).name(); // Получение типа объекта
    for (size_t i = 0; i < vectorObjects_.size(); ++i)
    {
        if (vectorObjects_[i].get() == object)
        {
            vectorObjects_.erase(vectorObjects_.begin() + i);
            Logger::info << "Cотрудник << " + object->position_ +   " " +
                                              object->surname_ +    " " +
                                              object->name_ +       " " +
                                              object->patronymic_ + " >> успешно удален!" << std::endl;
            std::cout << "Cотрудник << " + object->position_ +   " " +
                                           object->surname_ +    " " +
                                           object->name_ +       " " +
                                           object->patronymic_ + " >> успешно удален!" << std::endl;
            
            for (const auto &element: vectorObjects_)
            {
                // Изменение ID всех объектов определенного класса, которые стояли после удаляемого объекта
                if (typeid(*element.get()).name() == typeObject && element->id_ > deletedId)
                {
                    element->id_ = deletedId;
                    ++deletedId;
                }
            }
            sort();
            return;
        }
    }
}

void Data::newEmployeeData(const TradingCompany *object)
{
    Logger::info << "************* Добавление данных сотрудника *************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "************* Добавление данных сотрудника *************" << std::endl;
        std::cout << "Выберите одну из предложенных должности: " << std::endl;
        for (const auto &[key, value]: idPositions)
        {
            std::cout << key << " ";
        }
        std::cout << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            if (input == "b" || input == "н")
            {
                return;
            }
            else if (input == "esc" || input == "выход")
            {
                EXIT(object);
            }
            else
            {
                auto found = idPositions.find(utils::toUpperAndToLower(input)); // Поиск класса с определенной должностью
                if (found != idPositions.end())
                {
                    std::string position = found->first;
                    auto object = objectFactory_.get(position)(); // Получение определенного объекта из фабрики объектов
                    object->position_ = position;
                    object->fieldStatus_[FIELD_POSITION] = ST_OK;
                    checkParameters(object);
                    pushBack(*object);
                }
                else
                {
                    throw input;
                }
            }
        }
        catch (const std::string &exception)
        {
            Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
            std::cerr << "Вы ввели >> " << exception << " - неверная команда!" << std::endl;
        }
    }
}

void Data::setModeOutputData(const TradingCompany *object)
{
    Logger::info << "************ Изменение режима данных вывода ************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "************ Изменение режима данных вывода ************" << std::endl;
        mode_ == TXT ? std::cout << "По умолчанию режим - TXT" :
        mode_ == XML ? std::cout << "По умолчанию режим - XML" :
                       std::cout << "По умолчанию режим - ALL";
        std::cout << std::endl;
        std::cout << "Изменить на TXT - нажмите 1" << std::endl;
        std::cout << "Изменить на XML - нажмите 2" << std::endl;
        std::cout << "Изменить на ALL (использование всех режимов: TXT, XML) - нажмите 3" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            switch (utils::hash(input.c_str()))
            {
                case utils::hash("1") :
                    mode_ = TXT;
                    Logger::info << "Установлен режим вывода данных >> TXT" << std::endl;
                    std::cout << "Установлен режим вывода данных >> TXT" << std::endl;
                    return;

                case utils::hash("2") :
                    mode_ = XML;
                    Logger::info << "Установлен режим вывода данных >> XML" << std::endl;
                    std::cout << "Установлен режим вывода данных >> XML" << std::endl;
                    return;
                    
                case utils::hash("3") :
                    mode_ = ALL;
                    Logger::info << "Установлен режим вывода данных >> ALL" << std::endl;
                    std::cout << "Установлен режим вывода данных >> ALL" << std::endl;
                    return;

                case utils::hash("b") :
                case utils::hash("н") :
                    return;

                case utils::hash("esc") :
                case utils::hash("выход") :
                    EXIT(object);

                default:
                    throw input;
            }
        }
        catch (const std::string &exception)
        {
            Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
            std::cerr << "Вы ввели >> " << exception << " - неверная команда!" << std::endl;
        }
    }
}

void Data::writeToTxtFile()
{
    for (const auto &object: vectorObjects_)
    {
        std::ofstream out(directoryPath_ + object->position_ + ".txt", std::ios_base::app);
        out << "id: "           << "\"" << object->id_           << "\" ";
        out << "position: "     << "\"" << object->position_     << "\" ";
        out << "surname: "      << "\"" << object->surname_      << "\" ";
        out << "name: "         << "\"" << object->name_         << "\" ";
        out << "patronymic: "   << "\"" << object->patronymic_   << "\" ";
        out << "sex: "          << "\"" << object->sex_          << "\" ";
        out << "dateOfBirth: "  << "\"" << object->dateOfBirth_  << "\" ";
        out << "passport: "     << "\"" << object->passport_     << "\" ";
        out << "phone: "        << "\"" << object->phone_        << "\" ";
        out << "email: "        << "\"" << object->email_        << "\" ";
        out << "dateOfHiring: " << "\"" << object->dateOfHiring_ << "\" ";
        out << "workingHours: " << "\"" << object->workingHours_ << "\" ";
        out << "salary: "       << "\"" << object->salary_       << "\" ";
        out << "password: "     << "\"" << object->password_     << "\"";
        out << std::endl;
    }
}

void Data::writeToXmlFile()
{
    const char *tag = "tradingCompany";
    std::string previosPosition;
    auto lastObject = std::end(vectorObjects_) - 1;
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument(); // Инициализация документа
    tinyxml2::XMLNode *node = doc->NewElement(tag); // Корневой узел с меткой
    doc->InsertFirstChild(node); // Прикрепление корневого узла к документу

    for (const auto &object: vectorObjects_)
    {
        // Проверка на изменение должности и на конец вектора
        if ((previosPosition != object->position_ && !previosPosition.empty()) || *object == *lastObject->get())
        {
            doc->SaveFile((directoryPath_ + previosPosition + ".xml").c_str());
            doc->Clear();
            // После очищения идет новое создание корневого узла и приклепление к документу
            node = doc->NewElement(tag);
            doc->InsertFirstChild(node);
        }
        const char *className = utils::getClassName(*object).c_str();
        // Список элементов с меткой, которая должна совпадать с названием определенного класса
        tinyxml2::XMLElement *element = doc->NewElement(className);
        element->SetAttribute("id", object->id_);
        element->SetAttribute("position", object->position_.c_str());
        element->SetAttribute("surname", object->surname_.c_str());
        element->SetAttribute("name", object->name_.c_str());
        element->SetAttribute("patronymic", object->patronymic_.c_str());
        element->SetAttribute("sex", object->sex_.c_str());
        element->SetAttribute("dateOfBirth", object->dateOfBirth_.c_str());
        element->SetAttribute("passport", std::to_string(object->passport_).c_str());
        element->SetAttribute("phone", std::to_string(object->phone_).c_str());
        element->SetAttribute("email", object->email_.c_str());
        element->SetAttribute("dateOfHiring", object->dateOfHiring_.c_str());
        element->SetAttribute("workingHours", object->workingHours_.c_str());
        element->SetAttribute("salary", object->salary_);
        element->SetAttribute("password", object->password_.c_str());
        node->InsertEndChild(element); // Прикрепление списка элементов к корневому узлу
        previosPosition = object->position_;
    }
    delete doc;
}

Data::~Data()
{
    // Удаление ранних файлов с данными
    for (const auto &filePath: filePaths_)
    {
        std::remove(filePath.c_str());
    }
    
    try
    {
        switch (mode_)
        {
            case TXT :
                writeToTxtFile();
                break;
                
            case XML :
                writeToXmlFile();
                break;
                
            case ALL :
            {
                // Запись txt и xml в разных потоках
                std::thread thread = std::thread([this]()
                {
                    this->writeToTxtFile();
                });
                this->writeToXmlFile();
                thread.join();
                break;
            }
            default:
                throw mode_;
        }
    }
    catch (const Mode mode)
    {
        Logger::error << "Неверный режим вывода >> " + std::to_string(mode) << std::endl;
        std::cerr << "Неверный режим вывода >> " + std::to_string(mode) << std::endl;
    }
}
