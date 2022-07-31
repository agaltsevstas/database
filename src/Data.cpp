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

Data &Data::Instance()
{
    static Data data; // Объект-одиночка
    return data;
}

void Data::ReadingTxtFile(const boost::filesystem::path &iFilePath, uint iID)
{
    std::string line;
    const std::string fileName = iFilePath.filename().c_str(); // Получение имени с расширением
    const std::string name = iFilePath.stem().c_str(); // Получение имени без расширения
    try
    {
        std::ifstream file(iFilePath.c_str());
        if (file.is_open())
        {
            if (file.peek() == EOF)
            {
                throw "Пустой файл >> " + fileName;
            }
            while (getline(file, line))
            {
                Logger::info << "************* Считывание данных сотрудника *************" << std::endl;
                auto object = _objectFactory.Get(name)(); // Получение определенного объекта из фабрики объектов
                object->SetId(std::to_string(iID));
                line >> *object; // Запись данных в поля объекта
                auto result = find_if(_vectorObjects.begin(), _vectorObjects.end(),
                                      [&object](std::shared_ptr<Employee> &EmployeeObject)
                                      {
                                          return *object == *EmployeeObject;
                                      });
                if (result != _vectorObjects.end())
                {
                    Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                    delete object;
                    continue;
                }
                _vectorObjects.push_back(std::shared_ptr<Employee>(object));
                ++iID;
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

void Data::ReadingXmlFile(const boost::filesystem::path &iFilePath, uint iID)
{
    const char *tag = "Employee";
    const std::string fileName = iFilePath.filename().c_str(); // Получение имени с расширением
    const std::string name = iFilePath.stem().c_str(); // Получение имени без расширения
    const char *className = Utils::GetClassName(*_objectFactory.Get(name)()).c_str();
    tinyxml2::XMLDocument doc; // Инициализация документа
    try
    {
        tinyxml2::XMLError eResult = doc.LoadFile(iFilePath.c_str()); // Проверка на успешность загрузки файла в документ

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
                auto object = _objectFactory.Get(name)(); // Получение определенного объекта из фабрики объектов
                object->SetId(std::to_string(iID));
                for (const auto &[parameter, setParameter]: object->_setParameters)
                {
                    if (setParameter != nullptr)
                    {
                        std::string input;
                        input = element->Attribute(parameter.c_str()); // Получение значения поля по параметру
                        setParameter(*object, input); // Инициализация поля
                    }
                }
                auto result = find_if(_vectorObjects.begin(), _vectorObjects.end(),
                                      [&object](std::shared_ptr<Employee> &EmployeeObject)
                                      {
                                          return *object == *EmployeeObject;
                                      });
                if (result != _vectorObjects.end())
                {
                    Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                    delete object;
                    continue;
                }
                _vectorObjects.push_back(std::shared_ptr<Employee>(object));
                ++iID;
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

void Data::Sort()
{
    stable_sort(std::begin(_vectorObjects), std::end(_vectorObjects), []
                (const auto &first, const auto &second)
    {
        return first->_id < second->_id;
    });
}

void Data::LoadDatabase(const std::string &iDirectoryPath)
{
    namespace bs = boost::filesystem;
    
    _directoryPath = iDirectoryPath;
    // Добавление классов в фабрику объектов
    _objectFactory.Add<Accountant>("Бухгалтер");
    _objectFactory.Add<Driver>("Водитель");
    _objectFactory.Add<ChiefAccountant>("Главный_бухгалтер");
    _objectFactory.Add<ChiefLegalCounsel>("Главный_юрист-консультант");
    _objectFactory.Add<Loader>("Грузчик");
    _objectFactory.Add<Director>("Директор");
    _objectFactory.Add<Logistician>("Логист");
    _objectFactory.Add<PurchasingManager>("Менеджер_по_закупкам");
    _objectFactory.Add<SalesManager>("Менеджер_по_продажам");
    _objectFactory.Add<Cashier>("Кассир");
    _objectFactory.Add<HeadOfProcurement>("Начальник_отдела_закупок");
    _objectFactory.Add<HeadOfWarehouse>("Начальник_склада");
    _objectFactory.Add<HRManager>("Менеджер_по_персоналу");
    _objectFactory.Add<Lawyer>("Юрист");
    
    Logger::info << "---------- Считывание данных всех сотрудников ----------" << std::endl;
    for (const bs::path &filePath: bs::directory_iterator(_directoryPath))
    {
        try
        {
            const std::string fileName = Utils::ToUpperAndToLower(filePath.filename().c_str()); // Получение имени с расширением
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
                        ReadingTxtFile(filePath, id);
                        _filePaths.push_back(filePath.c_str());
                    }
                    else if (extension == ".xml")
                    {
                        ReadingXmlFile(filePath, id);
                        _filePaths.push_back(filePath.c_str());
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
    
    if (_vectorObjects.empty())
    {
        Logger::warning << "$$$$$$$$$$$$$ Пустая база данных $$$$$$$$$$$$$" << std::endl;
        Logger::info << "Выход из программы" << std::endl;
        std::cout << "Вы вышли из программы" << std::endl;
        exit(0);
    }
    Sort();
}

void Data::AccountLogin()
{
    std::cout << "Введите почту или логин и пароль от почты или закончите выполнение программы, введя ESC или ВЫХОД: " << std::endl;
    bool isLoginFound = false;
    try
    {
        std::cout << "Логин или почта: ";
        std::string login;
        std::cin >> login;
        for (const auto &object: _vectorObjects)
        {
            std::string emailCheck, loginCheck;
            emailCheck = loginCheck = object->_email;
            loginCheck.erase(loginCheck.find('@'), loginCheck.size()); // Получение логина от почты
            if (login == emailCheck || login == loginCheck)
            {
                isLoginFound = true;
                break;
            }
        }
        if (Utils::toLower(login) == "esc" || Utils::toLower(login) == "выход")
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
        for (auto object: _vectorObjects)
        {
            if (isLoginFound && password == object->_password)
            {
                LOGIN(object);
                CheckParameters(object.get(), true);
                object->Functional();
                LOGOUT(object);
                
                AccountLogin(); // Рекурсия
            }
        }
        if (Utils::toLower(password) == "esc" || Utils::toLower(password) == "выход")
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
        AccountLogin();
    }
}

template<class Class> void Data::CheckParameter(Parameter<Class> &iParameter)
{
    auto getUint32Parameter = boost::get<std::function<uint32_t(Employee&)>>(&iParameter.getParameter);
    auto getUint64Parameter = boost::get<std::function<uint64_t(Employee&)>>(&iParameter.getParameter);
    auto getStringParameter = boost::get<std::function<std::string(Employee&)>>(&iParameter.getParameter);
    auto checkParameter = iParameter.checkParameter;
    auto changeStatusParameter = iParameter.changeStatusParameter;
    auto object = iParameter.object;
    bool isMatchCheck = iParameter.isMatchCheck;
    
    checkParameter();
    
    // Проверка полей, которые имеют высший приоритет, на дублирование данных
    if (isMatchCheck)
    {
        for (auto it = std::begin(_vectorObjects); it != std::end(_vectorObjects);)
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
                it = _vectorObjects.begin();
            }
            else if (getUint64Parameter != nullptr && it->get() != object &&
                     (*getUint64Parameter)(*(*it)) == (*getUint64Parameter)(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = _vectorObjects.begin();
            }
            else if (getStringParameter != nullptr && it->get() != object &&
                     (*getStringParameter)(*(*it)) == (*getStringParameter)(*object))
            {
                changeStatusParameter();
                checkParameter();
                it = _vectorObjects.begin();
            }
            else
            {
                ++it;
            }
        }
    }
}

template<class Class> Data::Parameter<Class> Data::SelectParameter(const Field iField,
                                                                   Class *iObject,
                                                                   const std::string &iMessage)
{
    try
    {
        switch (iField)
        {
            case FIELD_POSITION :
                return {std::function<std::string(Employee&)>{&Employee::GetPosition},
                        std::bind(&Employee::CheckPosition, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusPosition, iObject), iObject};

            case FIELD_SURNAME :
                return {std::function<std::string(Employee&)>{&Employee::GetSurname},
                        std::bind(&Employee::CheckSurname, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusSurname, iObject), iObject};

            case FIELD_NAME :
                return {std::function<std::string(Employee&)>{&Employee::GetName},
                        std::bind(&Employee::CheckName, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusName, iObject), iObject};

            case FIELD_PATRONYMIC :
                return {std::function<std::string(Employee&)>{&Employee::GetPatronymic},
                        std::bind(&Employee::CheckPatronymic, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusPatronymic, iObject), iObject};

            case FIELD_SEX :
                return {std::function<std::string(Employee&)>{&Employee::GetSex},
                        std::bind(&Employee::CheckSex, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusSex, iObject), iObject};

            case FIELD_DATE_OF_BIRTH :
                return {std::function<std::string(Employee&)>{&Employee::GetDateOfBirth},
                        std::bind(&Employee::CheckDateOfBirth, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusDateOfBirth, iObject), iObject};

            case FIELD_PASSPORT :
                return {std::function<uint64_t(Employee&)>{&Employee::GetPassport},
                        std::bind(&Employee::CheckPassport, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusPassport, iObject, false), iObject, true};

            case FIELD_PHONE :
                return {std::function<uint64_t(Employee&)>{&Employee::GetPhone},
                        std::bind(&Employee::CheckPhone, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusPhone, iObject, false), iObject, true};

            case FIELD_EMAIL :
                return {std::function<std::string(Employee&)>{&Employee::GetEmail},
                        std::bind(&Employee::CheckEmail, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusEmail, iObject, false), iObject, true};

            case FIELD_DATE_OF_HIRING :
                return {std::function<std::string(Employee&)>{&Employee::GetDateOfHiring},
                        std::bind(&Employee::CheckDateOfHiring, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusDateOfHiring, iObject), iObject};

            case FIELD_WORKING_HOURS :
                return {std::function<std::string(Employee&)>{&Employee::GetWorkingHours},
                        std::bind(&Employee::CheckWorkingHours, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusWorkingHours, iObject), iObject};

            case FIELD_SALARY :
                return {std::function<uint32_t(Employee&)>{&Employee::GetSalary},
                        std::bind(&Employee::CheckSalary, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusSalary, iObject), iObject};

            case FIELD_PASSWORD :
                return {std::function<std::string(Employee&)>{&Employee::GetPassword},
                        std::bind(&Employee::CheckPassword, iObject, iMessage),
                        std::bind(&Employee::ChangeStatusPassword, iObject), iObject};
            default:
                throw iField;
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

template<class C> void Data::CheckParameters(C *iObject, const bool iWarning)
{
    std::string message;
    for (size_t field = FIELD_POSITION; field != FIELD_PASSWORD + 1; ++field)
    {
        if (iWarning)
        {
            message = warnings[field];
        }
        auto parameter = SelectParameter(static_cast<Field>(field), iObject, message);
        CheckParameter(parameter);
    }
}

void Data::PrintPersonalData(Employee *iObject)
{
    Logger::info << "***************** Вывод личных данных ******************" << std::endl;
    std::cout << std::endl;
    std::cout << "***************** Вывод личных данных ******************" << std::endl;
    std::cout << *iObject << std::endl;
}

void Data::ChangeData(Employee *iObject, Employee *ioOtherObject)
{
    bool isDirector = false;
    std::string message;
    if (typeid(*iObject) == typeid(Director)) // Изменять чужие данные имеет полномочия Director
    {
        isDirector = true;
    }
    
    if (ioOtherObject != nullptr && ioOtherObject != iObject)
    {
        message = "************** Измение данных сотрудника ***************\n>> " +
        ioOtherObject->_position + " " +
        ioOtherObject->_surname  + " " +
        ioOtherObject->_name     + " " +
        ioOtherObject->_patronymic + " <<";
    }
    else
    {
        ioOtherObject = iObject;
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
            Utils::tolower(input);
            if (isDirector && input == "1")
            {
                std::cout << "При изменении должности теряются полномочия" << std::endl;
                std::cout << "Введите yes или да - для продолжения, no или нет - для отмены" << std::endl;
                std::cout << "Ввод: ";
                std::cin >> input;
                Utils::tolower(input);
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
                    Utils::ToUpperandtolower(position);
                    auto found = idPositions.find(position); // Поиск класса с определенной должностью
                    if (found != idPositions.end())
                    {
                        auto newObject = _objectFactory.Get(position)(); // Получение определенного объекта из фабрики объектов
                        newObject->SetPosition(position);
                        *newObject = *ioOtherObject; // Запись данных из одного объекта одного класса в другой объект другого класса
                        DeleteObject(ioOtherObject);
                        PushBack(*newObject);
                        if (iObject == ioOtherObject) // После удаления личных данных происходит выход из аккаунта
                        {
                            LOGOUT(iObject);
                            AccountLogin();
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
                std::cout << "Текущая фамилия: " << ioOtherObject->_surname << std::endl;
                ioOtherObject->ChangeStatusSurname();
                auto parameter = SelectParameter(FIELD_SURNAME, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "3")
            {
                std::cout << "Текущее имя: " << ioOtherObject->_name << std::endl;
                ioOtherObject->ChangeStatusName();
                auto parameter = SelectParameter(FIELD_NAME, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "4")
            {
                std::cout << "Текущее отчество: " << ioOtherObject->_patronymic << std::endl;
                ioOtherObject->ChangeStatusPatronymic();
                auto parameter = SelectParameter(FIELD_PATRONYMIC, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "5")
            {
                std::cout << "Текущий пол: " << ioOtherObject->_sex << std::endl;
                ioOtherObject->ChangeStatusSex();
                auto parameter = SelectParameter(FIELD_SEX, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "6")
            {
                std::cout << "Текущая дата рождения: " << ioOtherObject->_dateOfBirth << std::endl;
                ioOtherObject->ChangeStatusDateOfBirth();
                auto parameter = SelectParameter(FIELD_DATE_OF_BIRTH, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "7")
            {
                std::cout << "Текущий паспорт: " << ioOtherObject->_passport << std::endl;
                ioOtherObject->ChangeStatusPassport(true);
                auto parameter = SelectParameter(FIELD_PASSPORT, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (input == "8")
            {
                std::cout << "Текущий телефон: " << ioOtherObject->_phone << std::endl;
                ioOtherObject->ChangeStatusPhone(true);
                auto parameter = SelectParameter(FIELD_PHONE, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "9")
            {
                std::cout << "Текущая почта: " << ioOtherObject->_email << std::endl;
                ioOtherObject->ChangeStatusEmail(true);
                auto parameter = SelectParameter(FIELD_EMAIL, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "10")
            {
                std::cout << "Текущее дата принятия на работу: " << ioOtherObject->_dateOfHiring << std::endl;
                ioOtherObject->ChangeStatusDateOfHiring();
                auto parameter = SelectParameter(FIELD_DATE_OF_HIRING, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "11")
            {
                std::cout << "Текущие часы работы: " << ioOtherObject->_workingHours << std::endl;
                ioOtherObject->ChangeStatusWorkingHours();
                auto parameter = SelectParameter(FIELD_WORKING_HOURS, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "12")
            {
                std::cout << "Текущая зарплата: " << ioOtherObject->_salary << std::endl;
                ioOtherObject->ChangeStatusSalary();
                auto parameter = SelectParameter(FIELD_SALARY, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (input == "13")
            {
                std::cout << "Текущий пароль: " << ioOtherObject->_password << std::endl;
                ioOtherObject->ChangeStatusPassword();
                auto parameter = SelectParameter(FIELD_PASSWORD, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (input == "b" || input == "н")
            {
                return;
            }
            else if (input == "esc" || input == "выход")
            {
                EXIT(iObject);
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

Employee *Data::Find(Employee *iObject)
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
                  << "телефон (например, 9032697963), почта (например, surname.name.patronymic@Employee.ru) "
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
            Utils::tolower(input);
            if (input == "b" || input == "н")
            {
                return nullptr;
            }
            else if (input == "esc" || input == "выход")
            {
                EXIT(iObject);
            }
            else
            {
                // Вектор объектов, в котором хранятся найденные объекты по определенным полям
                std::vector<std::shared_ptr<Employee>> foundObjects;
                for (const auto &object: _vectorObjects)
                {
                    // Вектор значений полей объекта с учетом верхнего и нижнего регистра букв
                    std::vector<std::pair<std::string, bool>> parameters = {
                        { std::to_string(object->_id), false },
                        { object->_position, true },
                        { object->_surname, true },
                        { object->_name, true },
                        { object->_patronymic, true },
                        { object->_sex, true },
                        { object->_dateOfBirth, false },
                        { std::to_string(object->_passport), false },
                        { std::to_string(object->_phone), false },
                        { object->_email, false },
                        { object->_dateOfHiring, false },
                        { object->_workingHours, false },
                        { std::to_string(object->_salary), false },
                        { object->_password, false }
                    };
                    for (const auto &[param, isUpperAndToLower]: parameters)
                    {
                        parameter = isUpperAndToLower ? Utils::ToUpperAndToLower(parameter) : parameter;
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
                        if (input == std::to_string(object->_id)) // Поиск по ID
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

void Data::ChangeOtherData(Employee *object)
{
    auto foundObject = Find(object);
    if (foundObject == nullptr)
        return;
    
    ChangeData(object, foundObject);
}

void Data::DeleteEmployeeData(Employee *iObject)
{
    while (true)
    {
        try
        {
            auto foundObject = Find(iObject);
            if (foundObject == nullptr) // Объект не найден, тогда возврат
            {
                return;
            }
            iObject == foundObject ? std::cout << "Вы действительно хотите удалить свой аккаунт?" << std::endl :
            std::cout << "Вы действительно хотите удалить сотрудника << " + foundObject->_position +   " " +
                                                                            foundObject->_surname +    " " +
                                                                            foundObject->_name +       " " +
                                                                            foundObject->_patronymic + " >> ?" << std::endl;
            std::cout << "Введите yes или да - для продолжения, no или нет - для отмены" << std::endl;
            std::cout << "Ввод: ";
            std::string input;
            std::cin >> input;
            Utils::tolower(input);
            if (input == "yes" || input == "да")
            {
                DeleteObject(foundObject);
                if (iObject == foundObject) // После удаления личных данных происходит выход из аккаунта
                {
                    LOGOUT(iObject);
                    AccountLogin();
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

void Data::GetAllOtherData() const
{
    Logger::info << "************ Вывод данных всех сотрудников *************" << std::endl;
    std::cout << std::endl;
    std::cout << "************ Вывод данных всех сотрудников *************" << std::endl;
    for (const auto &object: _vectorObjects)
        std::cout << *object << std::endl;
}

template<class C> void Data::PushBack(C &iObject)
{
    Logger::info << "************* Добавление нового сотрудника *************" << std::endl;
    std::cout << std::endl;
    std::cout << "************* Добавление нового сотрудника *************" << std::endl;
    std::string position = iObject._position;
    uint maxId = idPositions.find(position)->second - 1;
    std::vector<std::shared_ptr<Employee>>::iterator it;
    for (it = begin(_vectorObjects); it != end(_vectorObjects); ++it)
    {
        // Проверка двух объектов на то, что они от одного класса
        // Поиск макс ID среди объектов одного класса
        if ((typeid(*it->get()) == typeid(iObject)) && (*it)->_id > maxId)
        {
            maxId = (*it)->_id;
        }
    }
    std::string maxIdString = std::to_string(++maxId);
    iObject.SetId(maxIdString);
    _vectorObjects.insert(it, std::shared_ptr<Employee>(&iObject));
    Logger::info << "Сотрудник << " + iObject._position +   " " +
                                      iObject._surname +    " " +
                                      iObject._name +       " " +
                                      iObject._patronymic + " >> успешно добавлен!" << std::endl;
    std::cout << "Сотрудник << " + iObject._position +   " " +
                                   iObject._surname +    " " +
                                   iObject._name +       " " +
                                   iObject._patronymic + " >> успешно добавлен!" << std::endl;
}

template<class C> void Data::DeleteObject(C *iObject)
{
    Logger::info << "*********************** Удаление ***********************" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************** Удаление ***********************" << std::endl;
    uint deletedId = iObject->_id;
    std::string typeObject = typeid(*iObject).name(); // Получение типа объекта
    for (size_t i = 0; i < _vectorObjects.size(); ++i)
    {
        if (_vectorObjects[i].get() == iObject)
        {
            _vectorObjects.erase(_vectorObjects.begin() + i);
            Logger::info << "Cотрудник << " + iObject->_position +   " " +
                                              iObject->_surname +    " " +
                                              iObject->_name +       " " +
                                              iObject->_patronymic + " >> успешно удален!" << std::endl;
            std::cout << "Cотрудник << " + iObject->_position +   " " +
                                           iObject->_surname +    " " +
                                           iObject->_name +       " " +
                                           iObject->_patronymic + " >> успешно удален!" << std::endl;
            
            for (const auto &element: _vectorObjects)
            {
                // Изменение ID всех объектов определенного класса, которые стояли после удаляемого объекта
                if (typeid(*element.get()).name() == typeObject && element->_id > deletedId)
                {
                    element->_id = deletedId;
                    ++deletedId;
                }
            }
            Sort();
            return;
        }
    }
}

void Data::NewEmployeeData(const Employee *iObject)
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
            Utils::tolower(input);
            if (input == "b" || input == "н")
            {
                return;
            }
            else if (input == "esc" || input == "выход")
            {
                EXIT(iObject);
            }
            else
            {
                auto found = idPositions.find(Utils::ToUpperAndToLower(input)); // Поиск класса с определенной должностью
                if (found != idPositions.end())
                {
                    std::string position = found->first;
                    auto object = _objectFactory.Get(position)(); // Получение определенного объекта из фабрики объектов
                    object->_position = position;
                    object->_fieldStatus[FIELD_POSITION] = ST_OK;
                    CheckParameters(object);
                    PushBack(*object);
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

void Data::SetModeOutputData(const Employee *iObject)
{
    Logger::info << "************ Изменение режима данных вывода ************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "************ Изменение режима данных вывода ************" << std::endl;
        _mode == TXT ? std::cout << "По умолчанию режим - TXT" :
        _mode == XML ? std::cout << "По умолчанию режим - XML" :
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
            Utils::tolower(input);
            switch (Utils::Hash(input.c_str()))
            {
                case Utils::Hash("1") :
                    _mode = TXT;
                    Logger::info << "Установлен режим вывода данных >> TXT" << std::endl;
                    std::cout << "Установлен режим вывода данных >> TXT" << std::endl;
                    return;

                case Utils::Hash("2") :
                    _mode = XML;
                    Logger::info << "Установлен режим вывода данных >> XML" << std::endl;
                    std::cout << "Установлен режим вывода данных >> XML" << std::endl;
                    return;
                    
                case Utils::Hash("3") :
                    _mode = ALL;
                    Logger::info << "Установлен режим вывода данных >> ALL" << std::endl;
                    std::cout << "Установлен режим вывода данных >> ALL" << std::endl;
                    return;

                case Utils::Hash("b") :
                case Utils::Hash("н") :
                    return;

                case Utils::Hash("esc") :
                case Utils::Hash("выход") :
                    EXIT(iObject);

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

void Data::WriteToTxtFile()
{
    for (const auto &object: _vectorObjects)
    {
        std::ofstream out(_directoryPath + object->_position + ".txt", std::ios_base::app);
        out << "id: "           << "\"" << object->_id           << "\" ";
        out << "position: "     << "\"" << object->_position     << "\" ";
        out << "surname: "      << "\"" << object->_surname      << "\" ";
        out << "name: "         << "\"" << object->_name         << "\" ";
        out << "patronymic: "   << "\"" << object->_patronymic   << "\" ";
        out << "sex: "          << "\"" << object->_sex          << "\" ";
        out << "dateOfBirth: "  << "\"" << object->_dateOfBirth  << "\" ";
        out << "passport: "     << "\"" << object->_passport     << "\" ";
        out << "phone: "        << "\"" << object->_phone        << "\" ";
        out << "email: "        << "\"" << object->_email        << "\" ";
        out << "dateOfHiring: " << "\"" << object->_dateOfHiring << "\" ";
        out << "workingHours: " << "\"" << object->_workingHours << "\" ";
        out << "salary: "       << "\"" << object->_salary       << "\" ";
        out << "password: "     << "\"" << object->_password     << "\"";
        out << std::endl;
    }
}

void Data::WriteToXmlFile()
{
    const char *tag = "Employee";
    std::string previosPosition;
    auto lastObject = std::end(_vectorObjects) - 1;
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument(); // Инициализация документа
    tinyxml2::XMLNode *node = doc->NewElement(tag); // Корневой узел с меткой
    doc->InsertFirstChild(node); // Прикрепление корневого узла к документу

    for (const auto &object: _vectorObjects)
    {
        // Проверка на изменение должности и на конец вектора
        if ((previosPosition != object->_position && !previosPosition.empty()) || *object == *lastObject->get())
        {
            doc->SaveFile((_directoryPath + previosPosition + ".xml").c_str());
            doc->Clear();
            // После очищения идет новое создание корневого узла и приклепление к документу
            node = doc->NewElement(tag);
            doc->InsertFirstChild(node);
        }
        const char *className = Utils::GetClassName(*object).c_str();
        // Список элементов с меткой, которая должна совпадать с названием определенного класса
        tinyxml2::XMLElement *element = doc->NewElement(className);
        element->SetAttribute("id", object->_id);
        element->SetAttribute("position", object->_position.c_str());
        element->SetAttribute("surname", object->_surname.c_str());
        element->SetAttribute("name", object->_name.c_str());
        element->SetAttribute("patronymic", object->_patronymic.c_str());
        element->SetAttribute("sex", object->_sex.c_str());
        element->SetAttribute("dateOfBirth", object->_dateOfBirth.c_str());
        element->SetAttribute("passport", std::to_string(object->_passport).c_str());
        element->SetAttribute("phone", std::to_string(object->_phone).c_str());
        element->SetAttribute("email", object->_email.c_str());
        element->SetAttribute("dateOfHiring", object->_dateOfHiring.c_str());
        element->SetAttribute("workingHours", object->_workingHours.c_str());
        element->SetAttribute("salary", object->_salary);
        element->SetAttribute("password", object->_password.c_str());
        node->InsertEndChild(element); // Прикрепление списка элементов к корневому узлу
        previosPosition = object->_position;
    }
    delete doc;
}

Data::~Data()
{
    // Удаление ранних файлов с данными
    for (const auto &filePath: _filePaths)
    {
        std::remove(filePath.c_str());
    }
    
    try
    {
        switch (_mode)
        {
            case TXT :
                WriteToTxtFile();
                break;
                
            case XML :
                WriteToXmlFile();
                break;
                
            case ALL :
            {
                // Запись txt и xml в разных потоках
                std::thread thread = std::thread([this]()
                {
                    this->WriteToTxtFile();
                });
                this->WriteToXmlFile();
                thread.join();
                break;
            }
            default:
                throw _mode;
        }
    }
    catch (const Mode mode)
    {
        Logger::error << "Неверный режим вывода >> " + std::to_string(mode) << std::endl;
        std::cerr << "Неверный режим вывода >> " + std::to_string(mode) << std::endl;
    }
}
