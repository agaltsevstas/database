#include "Data.h"
#include "AbstractFactory.h"
#include "IEmployee.h"
#include "Logger.h"
#include "Utils.h"

#include "tinyxml2.h"

#include <boost/filesystem.hpp>
#include <boost/variant.hpp>
#include <fstream>
#include <thread>


/// Карта ID должностей
static const std::map<std::string, uint> idPositions =
{
    {"Бухгалтер", 900},
    {"Водитель", 1400},
    {"Главный_бухгалтер", 200},
    {"Главный_юрист-консультант", 300},
    {"Грузчик", 1300},
    {"Директор", 100},
    {"Логист", 1000},
    {"Менеджер_по_закупкам", 1200},
    {"Менеджер_по_персоналу", 400},
    {"Менеджер_по_продажам", 700},
    {"Кассир", 800},
    {"Начальник_отдела_закупок", 500},
    {"Начальник_склада", 600},
    {"Юрист", 1100}
};

/// Вектор предупреждений, номер элемента соответствует номеру поля класса Employee
static const std::vector<std::string> warnings
{
    "Ваш id не удовлетворяет требованиям!\n",
    "Ваша должность не удовлетворяет требованиям!\n",
    "Ваша фамилия не удовлетворяет требованиям!\n",
    "Ваше имя не удовлетворяет требованиям!\n",
    "Ваше отчество не удовлетворяет требованиям!\n",
    "Ваш пол не удовлетворяет требованиям!\n",
    "Ваша дата рождения не удовлетворяет требованиям!\n",
    "Ваш паспорт не удовлетворяет требованиям!\n",
    "Ваш телефон не удовлетворяет требованиям!\n",
    "Ваша почта не удовлетворяет требованиям!\n",
    "Ваша дата принятия на работу не удовлетворяет требованиям!\n",
    "Ваши часы работы не удовлетворяет требованиям!\n",
    "Ваша зарплата не удовлетворяет требованиям!\n",
    "Ваш пароль не удовлетворяет требованиям!\n"
};


/*!
 * @brief Класс-синглтон, предназначенный для чтения/записи/хранения объектов производных классов от Employee
 */
class Data
{
    friend class DataProxy;
    
private:
    
    /// Режимы записи данных
    enum Mode
    {
        TXT = 1,
        XML,
        Postgres,
        ALL
    };

    /*!
     * @brief Структура, предназначенная для проверки полей объекта
     * getParameter - Получение значения поля с типом (uint32_t/uint64_t/string)
     * checkParameter - Проверка полей на повреждение/перезапись данных
     * changeStatusParameter - Изменение статуса полей на перезапись/дублирование данных
     * object - Интересующий объект, который проверяется на валидность полей
     * isMatchCheck - Проверка совпадения поля объекта с другим полем другого объекта
     */
    struct Parameter
    {
        boost::variant<std::function<uint(IEmployee&)>,
                       std::function<uint64_t(IEmployee&)>,
                       std::function<std::string(IEmployee&)>> getParameter;
        std::function<void()> checkParameter = nullptr;
        std::function<void()> changeStatusParameter = nullptr;
        IEmployee *object = nullptr;
        bool isMatchCheck = false;
    };
    
public:
    /*!
     * @brief Создание единственного объекта
     */
    static Data &Instance() noexcept;

    /*!
     * @brief Загрузка базы данных.
     * Считывание данных из txt/xml файлов
     * @param iDirectoryPath - Путь к каталогу, где хранятся файлы
     */
    void LoadDatabase(const std::string &iDirectoryPath);

    /*!
     * @brief Вход в аккаунт.
     * Требуется ввести почту/логин и пароль
     */
    void AccountLogin();

    /*!
     * @brief Изменение личных/чужих данных
     * @param iObject - Объект, который в данный момент используется
     * @param ioOtherObject - Чужой объект, в котором изменяются данные
     */
    void ChangeData(const IEmployee *iObject, IEmployee *ioOtherObject = nullptr);
    
private:
    
    Mode _mode = TXT; // Режим записи данных
    std::string _directoryPath; // Путь к каталогу с файлами
    std::list<std::string> _filePaths; // Список путей к файлам
    std::vector<std::shared_ptr<IEmployee>> _vectorObjects; // Вектор объектов производных классов от Employee
    
    Data() = default;

    /*!
     * @brief Деструктор вызывает методы записи данных в файлы
     */
    ~Data();

    /*!
     * @brief Запрет копирования
     */
    Data(const Data&) = delete;

    /*!
     * @brief Запрет оператора присваивания
     */
    Data& operator=(Data&) = delete;

    /*!
     * @brief Чтение txt файла. Происходит построковое считывание файла.
     * Поля объекта заполняются данными, после объект добавляется в вектор объектов.
     * В случае дубликата, объект удалется.
     * @param iFilePath - Путь к txt файлу
     * @param iID - ID должности в соответствии с названием файла
     */
    void ReadingTxtFile(const boost::filesystem::path &iFilePath, uint iID);
    
    /*!
     * @brief Чтение xml файла. Происходит считывание файла.
     * Поля объекта заполняются данными, после объект добавляется в вектор объектов.
     * В случае дубликата, объект удалется.
     * @param iFilePath - Путь к txt файлу
     * @param iID - ID должности в соответствии с названием файла
     */
    void ReadingXmlFile(const boost::filesystem::path &iFilePath, uint iID);
    
    /*!
     * @brief Сортировка вектора объектов по ID в порядке возрастания
     */
    void Sort();
    
    /*!
     * @brief Проверка полей на повреждение/перезапись/дублирование данных.
     * Каждое поле проверяется отдельно.
     * @param iParameter - Структура, предназначенная для проверки полей объекта
     */
    void CheckParameter(Parameter &iParameter);
    
    /*!
     * @brief Проверка поля на повреждение/перезапись/дублирование данных.
     * Каждое поле проверяется отдельно.
     * @param iField - Номер поля
     * @param iObject - Проверяемый объект
     * @param iMessage - Передаваемое сообщение
     * @return Структура, предназначенная для проверки полей объекта
     */
    Parameter SelectParameter(const IEmployee::Field iField,
                              IEmployee *iObject,
                              const std::string &iMessage = {});
    
    /*!
     * @brief Обертка для проверки всех полей на повреждение/перезапись/дублирование данных
     * @param iObject - Объект, который в данный момент используется
     * @param iWarning - Передаваемое предупреждение о невалидности данных поля
     */
    void CheckParameters(const std::shared_ptr<IEmployee> &iObject, const bool iWarning = false);
    
    /*!
     * @brief Поиск объекта по одному из полей
     * @param iObject - Объект, который в данный момент используется
     * @return Найденный объект
     */
    std::shared_ptr<IEmployee> Find(const IEmployee *iObject);
    
    /*!
     * @brief Обертка для изменения чужих данных
     * @param iObject - Объект, который в данный момент используется
     */
    void ChangeOtherData(const IEmployee *iObject);
    
    /*!
     * @brief Обертка для удаления данных сотрудника
     * @param iObject - Объект, который в данный момент используется
     */
    void DeleteEmployeeData(const std::shared_ptr<IEmployee> &iObject);
    
    /*!
     * @brief Вывод всех данных из вектора объектов на экран
     */
    void GetAllOtherData() const;
    
    /*!
     * @brief Добавление объекта в вектор объектов
     * @param iObject - Добавляемый объект
     */
    void PushBack(const std::shared_ptr<IEmployee> &iObject);
    
    /*!
     * @brief Удаление объекта из вектора объектов
     * @param iObject - Удаляемый объект
     */
    void DeleteObject(const IEmployee *iObject);
    
    /*!
     * @brief Добавление нового сотрудника. Заполнение полей нового объекта
     * @param iObject - Объект, который в данный момент используется
     */
    void NewEmployeeData(const IEmployee *iObject);
    
    /*!
     * @brief Установление режима записи данных
     * @param iObject - Объект, который в данный момент используется
     */
    void SetModeOutputData(const IEmployee *iObject);
    
    /*!
     * @brief Запись всех данных в txt файлы
     */
    void WriteToTxtFile();
    
    /*!
     * @brief Запись всех данных в xml файлы
     */
    void WriteToXmlFile();
};


Data &Data::Instance() noexcept
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
                auto object = IAbstractFactory<std::string, IEmployee>::Create(name); // Получение определенного объекта из фабрики объектов
                if (!object)
                    throw "Пустой объект >> " + name;
                
                object->SetId(std::to_string(iID));
                *object >> line; // Запись данных в поля объекта
                auto result = find_if(_vectorObjects.begin(), _vectorObjects.end(),
                                      [&object](std::shared_ptr<IEmployee> &EmployeeObject)
                                      {
                                          return object == EmployeeObject;
                                      });
                if (result != _vectorObjects.end())
                {
                    Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                    continue;
                }
                _vectorObjects.push_back(object);
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
    const char *className = Utils::GetClassName(*IAbstractFactory<std::string, IEmployee>::Get(name)()).c_str();
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
                auto object = IAbstractFactory<std::string, IEmployee>::Create(name); // Получение определенного объекта из фабрики объектов
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
                                      [&object](std::shared_ptr<IEmployee> &EmployeeObject)
                                      {
                                          return object == EmployeeObject;
                                      });
                if (result != _vectorObjects.end())
                {
                    Logger::warning << "[DELETION] Запись-дубликат" << std::endl;
                    continue;
                }
                _vectorObjects.push_back(object);
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
        return first->GetId() < second->GetId();
    });
}

void Data::LoadDatabase(const std::string &iDirectoryPath)
{
    namespace bs = boost::filesystem;

    _directoryPath = iDirectoryPath;
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
            emailCheck = loginCheck = object->GetEmail();
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
            if (isLoginFound && password == object->GetPassword())
            {
                LOGIN(object);
                CheckParameters(object, true);
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

void Data::CheckParameter(Parameter &iParameter)
{
    auto getUint32Parameter = boost::get<std::function<uint32_t(IEmployee&)>>(&iParameter.getParameter);
    auto getUint64Parameter = boost::get<std::function<uint64_t(IEmployee&)>>(&iParameter.getParameter);
    auto getStringParameter = boost::get<std::function<std::string(IEmployee&)>>(&iParameter.getParameter);
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

Data::Parameter Data::SelectParameter(const IEmployee::Field iField,
                                      IEmployee *iObject,
                                      const std::string &iMessage)
{
    try
    {
        switch (iField)
        {
            case IEmployee::FIELD_POSITION :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetPosition},
                        std::bind(&IEmployee::CheckPosition, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusPosition, iObject), iObject};

            case IEmployee::FIELD_SURNAME :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetSurname},
                        std::bind(&IEmployee::CheckSurname, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusSurname, iObject), iObject};

            case IEmployee::FIELD_NAME :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetName},
                        std::bind(&IEmployee::CheckName, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusName, iObject), iObject};

            case IEmployee::FIELD_PATRONYMIC :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetPatronymic},
                        std::bind(&IEmployee::CheckPatronymic, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusPatronymic, iObject), iObject};

            case IEmployee::FIELD_SEX :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetSex},
                        std::bind(&IEmployee::CheckSex, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusSex, iObject), iObject};

            case IEmployee::FIELD_DATE_OF_BIRTH :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetDateOfBirth},
                        std::bind(&IEmployee::CheckDateOfBirth, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusDateOfBirth, iObject), iObject};

            case IEmployee::FIELD_PASSPORT :
                return {std::function<uint64_t(IEmployee&)>{&IEmployee::GetPassport},
                        std::bind(&IEmployee::CheckPassport, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusPassport, iObject, false), iObject, true};

            case IEmployee::FIELD_PHONE :
                return {std::function<uint64_t(IEmployee&)>{&IEmployee::GetPhone},
                        std::bind(&IEmployee::CheckPhone, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusPhone, iObject, false), iObject, true};

            case IEmployee::FIELD_EMAIL :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetEmail},
                        std::bind(&IEmployee::CheckEmail, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusEmail, iObject, false), iObject, true};

            case IEmployee::FIELD_DATE_OF_HIRING :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetDateOfHiring},
                        std::bind(&IEmployee::CheckDateOfHiring, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusDateOfHiring, iObject), iObject};

            case IEmployee::FIELD_WORKING_HOURS :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetWorkingHours},
                        std::bind(&IEmployee::CheckWorkingHours, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusWorkingHours, iObject), iObject};

            case IEmployee::FIELD_SALARY :
                return {std::function<uint32_t(IEmployee&)>{&IEmployee::GetSalary},
                        std::bind(&IEmployee::CheckSalary, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusSalary, iObject), iObject};

            case IEmployee::FIELD_PASSWORD :
                return {std::function<std::string(IEmployee&)>{&IEmployee::GetPassword},
                        std::bind(&IEmployee::CheckPassword, iObject, iMessage),
                        std::bind(&IEmployee::ChangeStatusPassword, iObject), iObject};
            default:
                throw iField;
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Невернное значение >> " << exception << std::endl;
        std::cerr << "Невернное значение >> " << exception << std::endl;
    }
    catch (const IEmployee::Field field)
    {
        Logger::error << "Неверный параметр поля >> " + std::to_string(field) << std::endl;
        std::cerr << "Неверный параметр поля >> " + std::to_string(field) << std::endl;
    }
    
    return Parameter();
}

void Data::CheckParameters(const std::shared_ptr<IEmployee> &iObject, const bool iWarning)
{
    std::string message;
    for (size_t field = IEmployee::FIELD_POSITION; field != IEmployee::FIELD_PASSWORD + 1; ++field)
    {
        if (iWarning)
        {
            message = warnings[field];
        }
        auto parameter = SelectParameter(static_cast<IEmployee::Field>(field), iObject.get(), message);
        CheckParameter(parameter);
    }
}

void Data::ChangeData(const IEmployee *iObject, IEmployee *ioOtherObject)
{
    bool isDirector = false;
    std::string message;
    if (Utils::GetClassName(*iObject) == "Director") // Изменять чужие данные имеет полномочия Director
    {
        isDirector = true;
    }

    if (ioOtherObject != nullptr && ioOtherObject != iObject)
    {
        message = "************** Измение данных сотрудника ***************\n>> " +
        ioOtherObject->GetPosition() + " " +
        ioOtherObject->GetSurname()  + " " +
        ioOtherObject->GetName()     + " " +
        ioOtherObject->GetPatronymic() + " <<";
    }
    else
    {
        *ioOtherObject = *iObject;
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
                        auto newObject = IAbstractFactory<std::string, IEmployee>::Create(position); // Получение определенного объекта из фабрики объектов
                        newObject->SetPosition(position);
                        *newObject = *ioOtherObject; // Запись данных из одного объекта одного класса в другой объект другого класса
                        DeleteObject(ioOtherObject);
                        PushBack(newObject);
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
                std::cout << "Текущая фамилия: " << ioOtherObject->GetSurname() << std::endl;
                ioOtherObject->ChangeStatusSurname();
                auto parameter = SelectParameter(IEmployee::FIELD_SURNAME, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "3")
            {
                std::cout << "Текущее имя: " << ioOtherObject->GetName() << std::endl;
                ioOtherObject->ChangeStatusName();
                auto parameter = SelectParameter(IEmployee::FIELD_NAME, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "4")
            {
                std::cout << "Текущее отчество: " << ioOtherObject->GetPatronymic() << std::endl;
                ioOtherObject->ChangeStatusPatronymic();
                auto parameter = SelectParameter(IEmployee::FIELD_PATRONYMIC, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "5")
            {
                std::cout << "Текущий пол: " << ioOtherObject->GetSex() << std::endl;
                ioOtherObject->ChangeStatusSex();
                auto parameter = SelectParameter(IEmployee::FIELD_SEX, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "6")
            {
                std::cout << "Текущая дата рождения: " << ioOtherObject->GetDateOfBirth() << std::endl;
                ioOtherObject->ChangeStatusDateOfBirth();
                auto parameter = SelectParameter(IEmployee::FIELD_DATE_OF_BIRTH, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "7")
            {
                std::cout << "Текущий паспорт: " << ioOtherObject->GetPassport() << std::endl;
                ioOtherObject->ChangeStatusPassport(true);
                auto parameter = SelectParameter(IEmployee::FIELD_PASSPORT, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (input == "8")
            {
                std::cout << "Текущий телефон: " << ioOtherObject->GetPhone() << std::endl;
                ioOtherObject->ChangeStatusPhone(true);
                auto parameter = SelectParameter(IEmployee::FIELD_PHONE, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "9")
            {
                std::cout << "Текущая почта: " << ioOtherObject->GetEmail() << std::endl;
                ioOtherObject->ChangeStatusEmail(true);
                auto parameter = SelectParameter(IEmployee::FIELD_EMAIL, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "10")
            {
                std::cout << "Текущее дата принятия на работу: " << ioOtherObject->GetDateOfHiring() << std::endl;
                ioOtherObject->ChangeStatusDateOfHiring();
                auto parameter = SelectParameter(IEmployee::FIELD_DATE_OF_HIRING, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "11")
            {
                std::cout << "Текущие часы работы: " << ioOtherObject->GetWorkingHours() << std::endl;
                ioOtherObject->ChangeStatusWorkingHours();
                auto parameter = SelectParameter(IEmployee::FIELD_WORKING_HOURS, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (isDirector && input == "12")
            {
                std::cout << "Текущая зарплата: " << ioOtherObject->GetSalary() << std::endl;
                ioOtherObject->ChangeStatusSalary();
                auto parameter = SelectParameter(IEmployee::FIELD_SALARY, ioOtherObject, "");
                CheckParameter(parameter);
            }
            else if (input == "13")
            {
                std::cout << "Текущий пароль: " << ioOtherObject->GetPassword() << std::endl;
                ioOtherObject->ChangeStatusPassword();
                auto parameter = SelectParameter(IEmployee::FIELD_PASSWORD, ioOtherObject, "");
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

std::shared_ptr<IEmployee> Data::Find(const IEmployee *iObject)
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
                std::vector<std::shared_ptr<IEmployee>> foundObjects;
                for (const auto &object: _vectorObjects)
                {
                    // Вектор значений полей объекта с учетом верхнего и нижнего регистра букв
                    std::vector<std::pair<std::string, bool>> parameters = {
                        { std::to_string(object->GetId()), false },
                        { object->GetPosition(), true },
                        { object->GetSurname(), true },
                        { object->GetName(), true },
                        { object->GetPatronymic(), true },
                        { object->GetSex(), true },
                        { object->GetDateOfBirth(), false },
                        { std::to_string(object->GetPassport()), false },
                        { std::to_string(object->GetPhone()), false },
                        { object->GetEmail(), false },
                        { object->GetDateOfHiring(), false },
                        { object->GetWorkingHours(), false },
                        { std::to_string(object->GetSalary()), false },
                        { object->GetPassword(), false }
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
//                    std::cout << *foundObjects.at(0) << std::endl;
                    return foundObjects.at(0);
                }
                // Больше одного найденного объекта
                else if (foundObjects.size() > 1)
                {
                    std::cout << "Найденные сотрудники: " << std::endl;
                    for (const auto &object: foundObjects)
                    {
                        *object << std::cout << std::endl;
                    }
                    std::cout << "Введите id конкретного сотрудника из предложенных" << std::endl;
                    std::cout << "Ввод: ";
                    std::string input;
                    std::cin >> input;
                    for (const auto &object: foundObjects)
                    {
                        if (input == std::to_string(object->GetId())) // Поиск по ID
                        {
                            std::cout << "Найденный сотрудник: " << std::endl;
                            *object << std::cout << std::endl;
                            return object;
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

void Data::ChangeOtherData(const IEmployee *object)
{
    auto foundObject = Find(object);
    if (foundObject == nullptr)
        return;

    ChangeData(object, foundObject.get());
}

void Data::DeleteEmployeeData(const std::shared_ptr<IEmployee> &iObject)
{
    while (true)
    {
        try
        {
            auto foundObject = Find(iObject.get());
            if (foundObject == nullptr) // Объект не найден, тогда возврат
            {
                return;
            }
            iObject == foundObject ? std::cout << "Вы действительно хотите удалить свой аккаунт?" << std::endl :
            std::cout << "Вы действительно хотите удалить сотрудника << " + foundObject->GetPosition() +   " " +
                                                                            foundObject->GetSurname() +    " " +
                                                                            foundObject->GetName() +       " " +
                                                                            foundObject->GetPatronymic() + " >> ?" << std::endl;
            std::cout << "Введите yes или да - для продолжения, no или нет - для отмены" << std::endl;
            std::cout << "Ввод: ";
            std::string input;
            std::cin >> input;
            Utils::tolower(input);
            if (input == "yes" || input == "да")
            {
                DeleteObject(foundObject.get());
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
        *object << std::cout << std::endl;
}

void Data::PushBack(const std::shared_ptr<IEmployee> &iObject)
{
    Logger::info << "************* Добавление нового сотрудника *************" << std::endl;
    std::cout << std::endl;
    std::cout << "************* Добавление нового сотрудника *************" << std::endl;
    std::string position = iObject->GetPosition();
    uint maxId = idPositions.find(position)->second - 1;
    std::vector<std::shared_ptr<IEmployee>>::iterator it;
    std::string typeObject = Utils::GetClassName(*iObject); // Получение типа объекта
    for (it = begin(_vectorObjects); it != end(_vectorObjects); ++it)
    {
        // Проверка двух объектов на то, что они от одного класса
        // Поиск макс ID среди объектов одного класса
        if (Utils::GetClassName(**it) == typeObject && (*it)->GetId() > maxId)
        {
            maxId = (*it)->GetId();
        }
    }
    std::string maxIdString = std::to_string(++maxId);
    iObject->SetId(maxIdString);
    _vectorObjects.insert(it, iObject);
    Logger::info << "Сотрудник << " + iObject->GetPosition() +   " " +
                                      iObject->GetSurname() +    " " +
                                      iObject->GetName() +       " " +
                                      iObject->GetPatronymic() + " >> успешно добавлен!" << std::endl;
    std::cout << "Сотрудник << " + iObject->GetPosition() +   " " +
                                   iObject->GetSurname() +    " " +
                                   iObject->GetName() +       " " +
                                   iObject->GetPatronymic() + " >> успешно добавлен!" << std::endl;
}

void Data::DeleteObject(const IEmployee *iObject)
{
    Logger::info << "*********************** Удаление ***********************" << std::endl;
    std::cout << std::endl;
    std::cout << "*********************** Удаление ***********************" << std::endl;
    uint deletedId = iObject->GetId();
    std::string typeObject = Utils::GetClassName(*iObject); // Получение типа объекта
    for (size_t i = 0, I = _vectorObjects.size(); i < I; ++i)
    {
        if (_vectorObjects[i].get() == iObject)
        {
            _vectorObjects.erase(_vectorObjects.begin() + i);
            Logger::info << "Cотрудник << " + iObject->GetPosition() +   " " +
                                              iObject->GetSurname() +    " " +
                                              iObject->GetName() +       " " +
                                              iObject->GetPatronymic() + " >> успешно удален!" << std::endl;
            std::cout << "Cотрудник << " + iObject->GetPosition() +   " " +
                                           iObject->GetSurname() +    " " +
                                           iObject->GetName() +       " " +
                                           iObject->GetPatronymic() + " >> успешно удален!" << std::endl;

            for (const auto &element: _vectorObjects)
            {
                // Изменение ID всех объектов определенного класса, которые стояли после удаляемого объекта
                if (Utils::GetClassName(*element) == typeObject && element->GetId() > deletedId)
                {
                    element->SetId(std::to_string(deletedId));
                    ++deletedId;
                }
            }
            Sort();
            return;
        }
    }
}

void Data::NewEmployeeData(const IEmployee *iObject)
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
                    auto object = IAbstractFactory<std::string, IEmployee>::Create(position); // Получение определенного объекта из фабрики объектов
                    object->SetPosition(position);
                    object->_fieldStatus[IEmployee::FIELD_POSITION] = IEmployee::ST_OK;
                    CheckParameters(object);
                    PushBack(object);
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

void Data::SetModeOutputData(const IEmployee *iObject)
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
        std::ofstream out(_directoryPath + object->GetPosition() + ".txt", std::ios_base::app);
        out << "id: "           << "\"" << object->GetId()           << "\" ";
        out << "position: "     << "\"" << object->GetPosition()     << "\" ";
        out << "surname: "      << "\"" << object->GetSurname()      << "\" ";
        out << "name: "         << "\"" << object->GetName()         << "\" ";
        out << "patronymic: "   << "\"" << object->GetPatronymic()   << "\" ";
        out << "sex: "          << "\"" << object->GetSex()          << "\" ";
        out << "dateOfBirth: "  << "\"" << object->GetDateOfBirth()  << "\" ";
        out << "passport: "     << "\"" << object->GetPassport()     << "\" ";
        out << "phone: "        << "\"" << object->GetPhone()        << "\" ";
        out << "email: "        << "\"" << object->GetEmail()        << "\" ";
        out << "dateOfHiring: " << "\"" << object->GetDateOfHiring() << "\" ";
        out << "workingHours: " << "\"" << object->GetWorkingHours() << "\" ";
        out << "salary: "       << "\"" << object->GetSalary()       << "\" ";
        out << "password: "     << "\"" << object->GetPassword()     << "\"";
        out << std::endl;
    }
}

void Data::WriteToXmlFile()
{
    const char *tag = "Employee";
    std::string previosPosition;
    auto lastObject = std::end(_vectorObjects) - 1;
    auto doc = std::make_unique<tinyxml2::XMLDocument>(); // Инициализация документа
    tinyxml2::XMLNode *node = doc->NewElement(tag); // Корневой узел с меткой
    doc->InsertFirstChild(node); // Прикрепление корневого узла к документу

    for (const auto &object: _vectorObjects)
    {
        // Проверка на изменение должности и на конец вектора
        if ((previosPosition != object->GetPosition() && !previosPosition.empty()) || *object == *lastObject->get())
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
        element->SetAttribute("id", object->GetId());
        element->SetAttribute("position", object->GetPosition().c_str());
        element->SetAttribute("surname", object->GetSurname().c_str());
        element->SetAttribute("name", object->GetName().c_str());
        element->SetAttribute("patronymic", object->GetPatronymic().c_str());
        element->SetAttribute("sex", object->GetSex().c_str());
        element->SetAttribute("dateOfBirth", object->GetDateOfBirth().c_str());
        element->SetAttribute("passport", std::to_string(object->GetPassport()).c_str());
        element->SetAttribute("phone", std::to_string(object->GetPhone()).c_str());
        element->SetAttribute("email", object->GetEmail().c_str());
        element->SetAttribute("dateOfHiring", object->GetDateOfHiring().c_str());
        element->SetAttribute("workingHours", object->GetWorkingHours().c_str());
        element->SetAttribute("salary", object->GetSalary());
        element->SetAttribute("password", object->GetPassword().c_str());
        node->InsertEndChild(element); // Прикрепление списка элементов к корневому узлу
        previosPosition = object->GetPosition();
    }
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


static Data &data = Data::Instance();


void DataProxy::LoadDatabase(const std::string &iDirectoryPath)
{
    data.LoadDatabase(iDirectoryPath);
}

void DataProxy::AccountLogin()
{
    data.AccountLogin();
}

void DataProxy::ChangeData(const IEmployee *iObject, IEmployee *ioOtherObject)
{
    data.ChangeData(iObject, ioOtherObject);
}

std::shared_ptr<IEmployee> DataProxy::Find(const IEmployee *iObject)
{
    return data.Find(iObject);
}

void DataProxy::ChangeOtherData(const IEmployee *iObject)
{
    data.ChangeOtherData(iObject);
}

void DataProxy::DeleteEmployeeData(const IEmployee *iObject)
{
    data.DeleteObject(iObject);
}

void DataProxy::GetAllOtherData()
{
    data.GetAllOtherData();
}

void DataProxy::NewEmployeeData(const IEmployee *iObject)
{
    data.NewEmployeeData(iObject);
}

void DataProxy::SetModeOutputData(const IEmployee *iObject)
{
    data.SetModeOutputData(iObject);
}
