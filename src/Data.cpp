#include <boost/filesystem.hpp>

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
    static Data data;
    return data;
}

template<typename T> void Data::readingTxtFile(const T &filePath, uint id)
{
    std::string line;
    const std::string fileName = filePath.filename().c_str();
    const std::string name = filePath.stem().c_str();
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
                Logger::info << " ************* Считывание данных сотрудника ************* " << std::endl;
                auto object = objectFactory_.get(name)();
                object->setId(std::to_string(id));
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
        Logger::info << ' ' << std::setfill('*') << std::setw(56) << "" << std::left << ' ' << std::endl;
        Logger::error << exception << std::endl;
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
template<typename T> void Data::readingXmlFile(const T &filePath, uint id)
{
    const char *tag = "tradingCompany";
    const std::string fileName = filePath.filename().c_str();
    const std::string name = filePath.stem().c_str();
    const char *className = utils::getClassName(*objectFactory_.get(name)()).c_str();
    tinyxml2::XMLDocument doc;
    try
    {
        tinyxml2::XMLError eResult = doc.LoadFile(filePath.c_str());

        if(eResult == tinyxml2::XML_SUCCESS)
        {
            tinyxml2::XMLNode *node = doc.FirstChildElement(tag); // корневой элемент xml документа
            if (node == nullptr)
            {
                throw std::string("Неверный тег файла!" );
            }
            doc.InsertFirstChild(node);            

            for (const auto *element = node->FirstChildElement(className); element != nullptr; element = element->NextSiblingElement()) // элемент найденного объекта
            {
                Logger::info << " ************* Считывание данных сотрудника ************* " << std::endl;
                auto object = objectFactory_.get(name)();
                object->setId(std::to_string(id));
                for (const auto &[key, value]: object->setParameters_)
                {
                    if (value != nullptr)
                    {
                        std::string input;
                        input = element->Attribute(key.c_str());
                        value(*object, input);
                    }
                }
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
        Logger::info << ' ' << std::setfill('*') << std::setw(56) << "" << std::left << ' ' << std::endl;
        Logger::error << exception << std::endl;
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

void Data::checkData(TradingCompany *object)
{
    for (const auto &element: tradingCompanyObjects_)
    {
        if (object->id_ == element->id_)
        {
            object->changeStatusId();
        }
        if (object->passport_ == element->passport_)
        {
            object->changeStatusPassport();
        }
        if (object->phone_ == element->phone_)
        {
            object->changeStatusPhone();
        }
        if (object->email_ == element->email_)
        {
            element->changeStatusEmail(false, false);
            object->changeStatusEmail(false, true);
        }
    }
}

void Data::sort()
{
    stable_sort(std::begin(tradingCompanyObjects_), std::end(tradingCompanyObjects_), []
                (const auto &first, const auto &second)
    {
        return first->id_ < second->id_;
    });
}

void Data::loadDatabase(const std::string &directoryPath)
{
    namespace bs = boost::filesystem;
    
    directoryPath_ = directoryPath;
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
    for (const bs::path &filePath: bs::directory_iterator(directoryPath_))
    {
        try
        {
            const std::string fileName = filePath.filename().c_str();
            const std::string name = filePath.stem().c_str();
            const std::string extension = filePath.extension().c_str();
            auto found = idPositions.find(name);
            if (found != idPositions.end())
            {
                uint id = found->second;
                if (extension == ".txt" || extension == ".xml")
                {
                    Logger::info << ' ' << std::setfill('*') << std::setw(56) << "" << std::left << ' ' << std::endl;
                    Logger::info << " Считывание данных из файла >> " << fileName << std::endl;
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
                    Logger::info << " Конец считывания данных из файла << " << fileName << std::endl;
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
        catch(const std::string &exception)
        {
            Logger::info << ' ' << std::setfill('*') << std::setw(56) << "" << std::left << ' ' << std::endl;
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
    Logger::info << " ------- Конец считывания всех данных сотрудников ------- " << std::endl;
    
    if (tradingCompanyObjects_.empty())
    {
        Logger::warning << "!!!!!!!!!! Пустая база данных !!!!!!!!!!" << std::endl;
        Logger::info << "Выход из программы" << std::endl;
        std::cout << "Вы вышли из программы" << std::endl;
        exit(0);
    }

    sort();
}

void Data::inputPassword()
{
    std::cout << "Введите почту или логин и пароль от почты или закончите выполнение программы, введя ESC или ВЫХОД: " << std::endl;
    bool isLoginFound = false;
    std::string login;
    try
    {
        std::cout << "Логин или почта: ";
        std::cin >> login;
        for (const auto &object: tradingCompanyObjects_)
        {
            std::string emailCheck, loginCheck;
            emailCheck = loginCheck = object->email_;
            loginCheck.erase(loginCheck.find('@'), loginCheck.size());
            if (login == emailCheck || login == loginCheck)
            {
                isLoginFound = true;
                break;
            }
        }
        if(utils::toLower(login) == "esc" || utils::toLower(login) == "выход")
        {
            Logger::info << "Выход из программы" << std::endl;
            std::cout << "Вы вышли из программы" << std::endl;
            exit(0);
        }
        
        std::cout << "Пароль: ";
        std::string password;
        std::cin >> password;
        Logger::info << std::setfill('.') << std::setw(57) << "" << std::left << std::endl;
        for (auto object: tradingCompanyObjects_)
        {
            if (isLoginFound && password == object->password_)
            {
                LOGIN(object);
                checkParameters(object.get());
                object->functional();
                LOGOUT(object);
                
                inputPassword();
            }
        }
        if(utils::toLower(password) == "esc" || utils::toLower(password) == "выход")
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
        Logger::info << " ---------- Попытка войти в аккаунт ---------- " << std::endl;
        Logger::error << "Введен >> " << exception << " - неверный логин или пароль!" << std::endl;
        std::cerr << "Вы ввели >> " << exception
                  << " - неверный логин или пароль! Попробуйте ввести заново: " << std::endl;
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
            if (getUintParameter != nullptr && (it->get() != object) &&
                getUintParameter(*(*it)) == getUintParameter(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = tradingCompanyObjects_.begin();
            }
            else if (getUint64Parameter != nullptr && (it->get() != object) &&
                     getUint64Parameter(*(*it)) == getUint64Parameter(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = tradingCompanyObjects_.begin();
            }
            else if (getStringParameter != nullptr && (it->get() != object) &&
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
                        std::bind(&TradingCompany::changeStatusEmail, object, true, false), object, true};

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
                        std::bind(&TradingCompany::changeStatusPassword, object), object, true};
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

void Data::printPersonalData(TradingCompany *object)
{
    std::cout << *object << std::endl;
}

void Data::changeData(TradingCompany *object, TradingCompany *otherObject)
{
    bool isDirector = false;
    std::string input;
    std::string message;
    if (typeid(*object) == typeid(Director))
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
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.): " << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД: " << std::endl;
        std::cout << "Ввод: ";
        try
        {
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
                    std::cout << "Ввод: ";
                    for (const auto &[key, value]: idPositions)
                    {
                        std::cout << key << " ";
                    }
                    std::cout << std::endl;
                    std::string position;
                    std::cin >> position;
                    utils::toupperandtolower(position);
                    auto found = idPositions.find(position);
                    if (found != idPositions.end())
                    {
                        auto newObject = objectFactory_.get(position)();
                        *newObject = *otherObject;
                        newObject->setPosition(position);
                        std::for_each(newObject->fieldStatus_.begin(), newObject->fieldStatus_.end(),
                                      [&newObject](auto &field){ newObject->fieldStatus_[field.first] = ST_OK; });
                        pushBack(*newObject);
                        deleteObject(otherObject);
                        otherObject = newObject;
                        Logger::info << "Должность сотрудника " + otherObject->surname_ + " " +
                                                                  otherObject->name_ + " " +
                                                                  otherObject->patronymic_ + " успешно изменена с " +
                                                                  otherObject->position_ + " на " +
                                                                  newObject->position_ << std::endl;
                        std::cout << "Должность сотрудника " + otherObject->surname_ + " " +
                                                               otherObject->name_ + " " +
                                                               otherObject->patronymic_ + " успешно изменена с " +
                                                               otherObject->position_ + " на " +
                                                               newObject->position_ << std::endl;
                        if (object == otherObject)
                        {
                            LOGOUT(object);
                            inputPassword();
                        }
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
            std::cerr << "Вы ввели >> " << exception
                      << " - неверная команда! Попробуйте ввести заново: " << std::endl;
            continue;
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

TradingCompany *Data::findParameter(std::string &parameter)
{
    if (parameter.empty())
    {
        std::cout << "Введена пустая строка" << std::endl;
        return nullptr;
    }
    std::vector<std::shared_ptr<TradingCompany>> foundObjects;
    for (const auto &object: tradingCompanyObjects_)
    {
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
    if (foundObjects.size() == 1)
    {
        return foundObjects.at(0).get();
    }
    else if (foundObjects.size() > 1)
    {
        std::cout << "Найденные объекты: " << std::endl;
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
            if (input == std::to_string(object->id_))
            {
                return object.get();
            }
        }
        std::cout << "Вы ввелите неверный id сотрудника!" << std::endl;
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
    std::cout << "Ввод: ";
    std::string input;
    std::cin >> input;
    auto foundObject = findParameter(input);
    foundObject ? changeData(object, foundObject) : changeOtherData(object);
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
    std::string position = object.position_;
    uint maxId = idPositions.find(position)->second - 1;
    std::vector<std::shared_ptr<TradingCompany>>::iterator it;
    
    for (it = begin(tradingCompanyObjects_); it != end(tradingCompanyObjects_); ++it)
    {
        if ((typeid(*it->get()) == typeid(object)) && (*it)->id_ > maxId)
        {
            maxId = (*it)->id_;
        }
    }
    std::string maxIdString = std::to_string(++maxId);
    object.setId(maxIdString);
    tradingCompanyObjects_.insert(it, std::shared_ptr<TradingCompany>(&object));
    sort();
}

template<class C> void Data::deleteObject(C *object)
{
    uint deletedId = object->id_;
    std::string typeObject = typeid(*object).name();
    for (size_t i = 0; i < tradingCompanyObjects_.size(); ++i)
    {
        if (tradingCompanyObjects_[i].get() == object)
        {
            tradingCompanyObjects_.erase(tradingCompanyObjects_.begin() + i);
            Logger::info << "Cотрудник " + object->position_ + " " +
                                           object->surname_ + " " +
                                           object->name_ + " " +
                                           object->patronymic_ + " успешно удален!" << std::endl;
            std::cout << "Cотрудник " + object->position_ + " " +
                                        object->surname_ + " " +
                                        object->name_ + " " +
                                        object->patronymic_ + " успешно удален!" << std::endl;
            
            for (const auto &element: tradingCompanyObjects_)
            {
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
    std::cout << "Выберите одну из предложенных должности: " << std::endl;
    for (const auto &[key, value]: idPositions)
    {
        std::cout << key << " ";
    }
    std::cout << std::endl;
    std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.): " << std::endl;
    std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД: " << std::endl;
    std::cout << "Введите должность сотрудника: " << std::endl;
    std::string input;
    try
    {
        std::cin >> input;
        auto found = idPositions.find(input);
        if (found != idPositions.end())
        {
            utils::toupperandtolower(input);
            auto object = objectFactory_.get(input)();
            pushBack(*object);
            Logger::info << "Добавление нового сотрудника с должностью >> " << input << std::endl; 
            std::cout << "Добавление нового сотрудника с должностью >> " << input << std::endl;
            checkParameters(object);
            pushBack(*object);
            Logger::info << "Сотрудник " + object->surname_ + " " +
                                           object->name_ + " " +
                                           object->patronymic_ + " успешно добавлен" << std::endl;
            std::cout << "Сотрудник " + object->surname_ + " " +
                                        object->name_ + " " +
                                        object->patronymic_ + " успешно добавлен" << std::endl;
        }
        else if(utils::toLower(input) == "b" || utils::toLower(input) == "н")
        {
            return;
        }
        else if(utils::toLower(input) == "esc" || utils::toLower(input) == "выход")
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

void Data::setModeOutputData(const TradingCompany *object)
{
    std::cout << "Хотите изменить режим вывода данных?" << std::endl;
    std::cout << "Режимы: 1 - TXT, 2 - XML ";
    mode_ == TXT ? std::cout << "(по умолчанию TXT)" : std::cout << "(по умолчанию XML)";
    std::cout << std::endl;
    std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
    std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
    std::cout << "Ввод: ";
    try
    {
        std::string input;
        std::cin >> input;
        switch (utils::str(input.c_str()))
        {
            case utils::str("1") :
                mode_ = TXT;
                Logger::info << "Установлен режим вывода данных >> TXT" << std::endl;
                std::cout << "Установлен режим вывода данных >> TXT" << std::endl;
                break;

            case utils::str("2") :
                mode_ = XML;
                Logger::info << "Установлен режим вывода данных >> XML" << std::endl;
                std::cout << "Установлен режим вывода данных >> XML" << std::endl;
                break;

            case utils::str("b") :
                return;

            case utils::str("esc") :
                EXIT(object);

            default:
                throw input;
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
        std::cerr << "Вы ввели >> " << exception
                  << " - неверная команда! Попробуйте ввести заново: " << std::endl;
        setModeOutputData(object);
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
        std::exit(0);
    }
}

void Data::writeToTxtFile()
{
    for (const auto &object: tradingCompanyObjects_)
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
    auto it = std::end(tradingCompanyObjects_) - 1;
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument(); // документ xml
    tinyxml2::XMLNode *node = doc->NewElement(tag); // корневой элемент xml документа
    doc->InsertFirstChild(node);

    for (const auto &object: tradingCompanyObjects_)
    {
        if ((previosPosition != object->position_ && !previosPosition.empty()) || *object == *it->get())
        {
            doc->SaveFile((directoryPath_ + previosPosition + ".xml").c_str());
            doc->Clear();
            node = doc->NewElement(tag); // корневой элемент xml документа
            doc->InsertFirstChild(node);
        }
        const char *classname = utils::getClassName(*object).c_str();
        tinyxml2::XMLElement *element = doc->NewElement(classname); // элемент найденного объекта
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
        node->InsertEndChild(element);
        previosPosition = object->position_;
    }
    delete doc;
}

Data::~Data()
{
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
                
            case XML:
                writeToXmlFile();
                break;
            
            default:
                throw mode_;
        }
    }
    catch(const Mode &mode)
    {
        Logger::error << "Неверный режим вывода >> " + std::to_string(mode) << std::endl;
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
