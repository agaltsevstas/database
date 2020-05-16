#include <boost/regex.hpp>

#include "TradingCompany.h"

template<>
uint TradingCompany::get<uint>(const std::string &value, const Field field)
{
    return checkField(value, field).uintValue;
}

template<>
uint64_t TradingCompany::get<uint64_t>(const std::string &value, const Field field)
{
    return checkField(value, field).uint64Value;
}

template<>
std::string TradingCompany::get<std::string>(const std::string &value, const Field field)
{
    return checkField(value, field).stringValue;
}

void TradingCompany::setId(const std::string &id)
{
    id_ = get<uint>(id, FIELD_ID);
}

void TradingCompany::setPosition(const std::string &position)
{
    position_ = get<std::string>(position, FIELD_POSITION);
}

void TradingCompany::setSurname(const std::string &surname)
{
    surname_ = get<std::string>(surname, FIELD_SURNAME);
}

void TradingCompany::setName(const std::string &name)
{
    name_ = get<std::string>(name, FIELD_NAME);
}

void TradingCompany::setPatronymic(const std::string &patronymic)
{
    patronymic_ = get<std::string>(patronymic, FIELD_PATRONYMIC);
}

void TradingCompany::setSex(const std::string &sex)
{
    sex_ = get<std::string>(sex, FIELD_SEX);
}

void TradingCompany::setDateOfBirth(const std::string &dateOfBirth)
{
    dateOfBirth_ = get<std::string>(dateOfBirth, FIELD_DATE_OF_BIRTH);
}

void TradingCompany::setPassport(const std::string &passport)
{
    passport_ = get<uint64_t>(passport, FIELD_PASSPORT);
}

void TradingCompany::setPhone(const std::string &phone)
{
    phone_ = get<uint64_t>(phone, FIELD_PHONE);
}

void TradingCompany::setEmail(const std::string &email)
{
    email_ = get<std::string>(email, FIELD_EMAIL);
}

void TradingCompany::setDateOfHiring(const std::string &dateOfHiring)
{
    dateOfHiring_ = get<std::string>(dateOfHiring, FIELD_DATE_OF_HIRING);
}

void TradingCompany::setWorkingHours(const std::string &workingHours)
{
    workingHours_ = get<std::string>(workingHours, FIELD_WORKING_HOURS);
}

void TradingCompany::setSalary(const std::string &salary)
{
    salary_ = get<uint>(salary, FIELD_SALARY);
}

void TradingCompany::setPassword(const std::string &password)
{
    password_ = get<std::string>(password, FIELD_PASSWORD);
}

uint TradingCompany::getId() const
{
    return id_;
}

std::string TradingCompany::getPosition() const
{
    return position_;
}

std::string TradingCompany::getSurname() const
{
    return surname_;
}

std::string TradingCompany::getName() const
{
    return name_;
}

std::string TradingCompany::getPatronymic() const
{
    return patronymic_;
}

std::string TradingCompany::getSex() const
{
    return sex_;
}

std::string TradingCompany::getDateOfBirth() const
{
    return dateOfBirth_;
}

uint64_t TradingCompany::getPassport() const
{
    return passport_;
}

uint64_t TradingCompany::getPhone() const
{
    return phone_;
}

std::string TradingCompany::getEmail() const
{
    return email_;
}

std::string TradingCompany::getDateOfHiring() const
{
    return dateOfHiring_;
}

std::string TradingCompany::getWorkingHours() const
{
    return workingHours_;
}

uint TradingCompany::getSalary() const
{
    return salary_;
}

std::string TradingCompany::getPassword() const
{
    return password_;
}

void TradingCompany::changeStatusId(const bool canOverwrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_ID] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись id >> " << id_ << std::endl;
    }
    else
    {
        uint id = id_;
        id_ = rand();
        fieldStatus_[FIELD_ID] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся id >> " << id << " изменен на >> " << id_ << std::endl;
    }
}

void TradingCompany::changeStatusPosition()
{
    fieldStatus_[FIELD_POSITION] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись должности >> " << position_ << std::endl;
}

void TradingCompany::changeStatusSurname()
{
    fieldStatus_[FIELD_SURNAME] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись фамилии >> " << surname_ << std::endl;
}

void TradingCompany::changeStatusName()
{
    fieldStatus_[FIELD_NAME] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись имени >> " << name_ << std::endl;
}

void TradingCompany::changeStatusPatronymic()
{
    fieldStatus_[FIELD_PATRONYMIC] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись отчества >> " << patronymic_ << std::endl;
}

void TradingCompany::changeStatusSex()
{
    fieldStatus_[FIELD_SEX] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись пола >> " << sex_ << std::endl;
}

void TradingCompany::changeStatusDateOfBirth()
{
    fieldStatus_[FIELD_DATE_OF_BIRTH] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись даты рождения >> " << dateOfBirth_ << std::endl;
}

void TradingCompany::changeStatusPassport(const bool canOverwrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_PASSPORT] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись паспорта >> " << passport_ << std::endl;
    }
    else
    {
        uint64_t passport = passport_;
        passport_ = rand();
        fieldStatus_[FIELD_PASSPORT] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся паспорт >> " << passport << " изменен на >> " << passport_ << std::endl;
    }
}

void TradingCompany::changeStatusPhone(const bool canOverwrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_PHONE] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись телефона >> " << phone_ << std::endl;
    }
    else
    {
        uint64_t phone = phone_;
        phone_ = rand();
        fieldStatus_[FIELD_PHONE] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся телефон >> " << phone << " изменен на >> " << phone_ << std::endl;
    }
}

void TradingCompany::changeStatusEmail(const bool canOverwrite, const bool isWrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_EMAIL] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись почты >> " << email_ << std::endl;
    }
    else
    {
        fieldStatus_[FIELD_EMAIL] = ST_DUBLICATE;
        if (isWrite)
        {
            Logger::warning << "Повторяющаяся почта >> " << email_ << std::endl;
        }
    }
}

void TradingCompany::changeStatusDateOfHiring()
{
    fieldStatus_[FIELD_DATE_OF_HIRING] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись даты принятия на работу >> " << dateOfHiring_ << std::endl;
}

void TradingCompany::changeStatusWorkingHours()
{
    fieldStatus_[FIELD_WORKING_HOURS] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись часов работы >> " << workingHours_ << std::endl;
}

void TradingCompany::changeStatusSalary()
{
    fieldStatus_[FIELD_SALARY] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись зарплаты >> " << salary_ << std::endl;
}

void TradingCompany::changeStatusPassword()
{
    fieldStatus_[FIELD_PASSWORD] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись пароля >> " << password_ << std::endl;
}

void TradingCompany::recursion(const Field &field,
                               std::function<void(TradingCompany&, std::string&)> setParameter,
                               const std::string &message)
{
    std::string input;
    if (fieldStatus_[field] != ST_OK)
    {
        std::cout << message << std::endl;
        std::string newMessage;
        auto condition = message.find("ведите");
        if (condition != std::string::npos)
        {
            newMessage = message.substr(condition);
        }
        std::cout << "Ввод: " << std::endl;
        std::cin >> input;
        setParameter(*this, input);
        recursion(field, setParameter, "Некорректно введен параметр, в" + newMessage);
    }
}

void TradingCompany::checkId(const std::string &warning)
{
    const std::string message = "Введите ID (например, 100)";
    recursion(FIELD_ID, &TradingCompany::setId, warning + message);
}

void TradingCompany::checkPosition(const std::string &warning)
{
    const std::string message = "Введите должность";
    recursion(FIELD_POSITION, &TradingCompany::setPosition, warning + message);
}

void TradingCompany::checkSurname(const std::string &warning)
{
    const std::string message = "Введите фамилию";
    recursion(FIELD_SURNAME, &TradingCompany::setSurname, warning + message);
}

void TradingCompany::checkName(const std::string &warning)
{
    const std::string message = "Введите имя";
    recursion(FIELD_NAME, &TradingCompany::setName, warning + message);
}

void TradingCompany::checkPatronymic(const std::string &warning)
{
    const std::string message = "Введите отчество";
    recursion(FIELD_PATRONYMIC, &TradingCompany::setPatronymic, warning + message);
}

void TradingCompany::checkSex(const std::string &warning)
{
    const std::string message = "Введите пол (например, Муж)";
    recursion(FIELD_SEX, &TradingCompany::setSex, warning + message);
}

void TradingCompany::checkDateOfBirth(const std::string &warning)
{
    const std::string message = "Введите дату рождения (например, 16.12.1995)";
    recursion(FIELD_DATE_OF_BIRTH, &TradingCompany::setDateOfBirth, warning + message);
}

void TradingCompany::checkPassport(const std::string &warning)
{
    const std::string message = "Введите номер паспорта (например, 4516561974)";
    recursion(FIELD_PASSPORT, &TradingCompany::setPassport, warning + message);
}

void TradingCompany::checkPhone(const std::string &warning)
{
    const std::string message = "Введите номер телефона (например, 9032697963)";
    recursion(FIELD_PHONE, &TradingCompany::setPhone, warning + message);
}

void TradingCompany::checkEmail(const std::string &warning)
{
    if (fieldStatus_[FIELD_EMAIL] != ST_OK)
    {
        const std::string email = utils::createEmail(std::vector<std::string>{surname_, name_, patronymic_});
        std::string firstPartEmail = email.substr(0, email.find("@"));
        uint secondPartEmail = 0;
        std::cout << "Ваша первая часть почты: " + firstPartEmail << std::endl;
        std::string message = "Введите вторую часть почты (это должно быть число от 1 до 99)\n";
        while (true)
        {
            std::cout << message;
            message = "Некорректно введен параметр, введите вторую часть почты (это должно быть число от 1 до 99)\n";
            std::cout << "Ввод: " << std::endl;
            std::cin >> secondPartEmail;
            if (secondPartEmail > 0 && secondPartEmail < 100)
            {
                break;
            }
            else
            {
                continue;
            }
        }
        setEmail(firstPartEmail + std::to_string(secondPartEmail) + "@tradingcompany.ru");
    }
}

void TradingCompany::checkDateOfHiring(const std::string &warning)
{
    const std::string message = "Введите дату принятия на работу (например, 16.04.2018)";
    recursion(FIELD_DATE_OF_HIRING, &TradingCompany::setDateOfHiring, warning + message);
}

void TradingCompany::checkWorkingHours(const std::string &warning)
{
    const std::string message = "Введите время работы (например, Понедельник-Пятница=09:00-18:00)";
    recursion(FIELD_WORKING_HOURS, &TradingCompany::setWorkingHours, warning + message);
}

void TradingCompany::checkSalary(const std::string &warning)
{
    const std::string message = "Введите зарплату (в рублях)";
    recursion(FIELD_SALARY, &TradingCompany::setSalary, warning + message);
}

void TradingCompany::checkPassword(const std::string &warning)
{
    const std::string message = "Введите новый пароль (пароль должен содержать:\n-не менее 6 символов\n"
                                "-хотя бы одну прописную латинскую букву\n"
                                "-хотя бы одну строчную латинскую букву\n"
                                "-хотя бы одну цифру)";
    recursion(FIELD_PASSWORD, &TradingCompany::setPassword, warning + message);
}

const TradingCompany::Type TradingCompany::checkField(std::string value, const Field &field)
{
    Type type;
    
    try
    {
        switch (field)
        {
            case FIELD_ID :
            {
                boost::regex regular ("^[0-9]{1,4}$");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой ID >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный ID >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !id_ ? Logger::info << "ID >> " << value << std::endl :
                           Logger::info << "ID << " << id_ << " >> изменен на >> " << value << std::endl;
                }
                type.uintValue = std::atoi(value.c_str());
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_POSITION :
            {
                utils::toupperandtolower(value); 
                boost::regex regular ("(Бухгалтер|Водитель|Главный_бухгалтер|Главный_юрист-консультант|Грузчик|Директор|Кассир|Логист|"
                                      "Менеджер_по_закупкам|Менеджер_по_продажам|Начальник_отдела_закупок|Начальник_склада|Юрист|Менеджер_по_персоналу)");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая должность >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная должность >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    position_.empty() ? Logger::info << "Должность >> " << value << std::endl :
                                        Logger::info << "Должность << " << position_ << " >> изменена на >> " << value << std::endl;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_SURNAME :
            {
                utils::toupperandtolower(value);
                boost::regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая фамилия >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная фамилия >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    surname_.empty() ? Logger::info << "Фамилия >> " << value << std::endl :
                                      (Logger::info << "Фамилия << " << surname_ << " >> изменена на >> " << value << std::endl,
                                       std::cout << "Фамилия успешно изменена" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_NAME :
            {
                utils::toupperandtolower(value);
                boost::regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::info << "Пустое имя >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорретное имя >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    name_.empty() ? Logger::info << "Имя >> " << value << std::endl :
                                   (Logger::info << "Имя << " << name_ << " >> изменено на >> " << value << std::endl,
                                    std::cout << "Имя успешно изменено" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_PATRONYMIC :
            {
                utils::toupperandtolower(value);
                boost::regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустое отчество >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорретное отчество >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    patronymic_.empty() ? Logger::info << "Отчество >> " << value << std::endl :
                                         (Logger::info << "Отчество << " << patronymic_ << " >> изменено на >> " << value << std::endl,
                                          std::cout << "Отчество успешно изменено" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
    
            case FIELD_SEX :
            {
                utils::toupperandtolower(value);
                boost::regex regular ("^(Муж|Жен)$");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой пол >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный пол >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    sex_.empty() ? Logger::info << "Пол >> " << value << std::endl :
                                  (Logger::info << "Пол << " << sex_ << " >> изменен на >> " << value << std::endl,
                                   std::cout << "Пол успешно изменен" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_DATE_OF_BIRTH :
            {
                std::vector<std::string> data = utils::splitString(utils::date(), " .-");
                std::vector<std::string> dateOfBirth = utils::splitString(value, " .-");
                auto age = utils::findAge(data, dateOfBirth);
                uint year = age[0];
                uint month = age[1];
                uint day = age[2];
                boost::regex regular ("^(((0[1-9]|[12][0-9]|30)[-/.]?(0[13-9]|1[012])|31[-/.]?(0[13578]|1[02])|(0[1-9]|"
                                      "1[0-9]|2[0-8])[-/.]?02)[-/.]?[0-9]{4}|29[-/.]?02[-/.]?([0-9]{2}(([2468][048]|"
                                      "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая дата рождения >> " << value << std::endl;
                }
                else if (year < 18)
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Неудовлетворительный возраст >> " << "Лет: " << year << "Месяцев: " << month << "Дней: " << day << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная дата рождения >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    dateOfBirth_.empty() ? Logger::info << "Дата рождения >> " << value << std::endl :
                                          (Logger::info << "Дата рождения << " << dateOfBirth_ << " >> изменена на >> " << value << std::endl,
                                           std::cout << "Дата рождения успешно изменена" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_PASSPORT :
            {
                boost::regex regular ("^[0-9]{10}$");
                boost::regex_match(value, regular);
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой паспорт >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный паспорт >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !passport_ ? Logger::info << "Паспорт >> " << value << std::endl :
                                (Logger::info << "Паспорт << " << passport_ << " >> изменен на >> " << value << std::endl,
                                 std::cout << "Паспорт успешно изменен" << std::endl);
                }
                type.uint64Value = std::strtoul(value.c_str(), NULL, 0);
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_PHONE :
            {
                boost::regex regular ("^[0-9]{10}$");
                boost::regex_match(value, regular);
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой телефон >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный телефон >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !phone_ ? Logger::info << "Телефон >> " << value << std::endl :
                             (Logger::info << "Телефон << " << phone_ << " >> изменен на >> " << value << std::endl,
                              std::cout << "Телефон успешно изменен" << std::endl);
                }
                type.uint64Value = std::strtoul(value.c_str(), NULL, 0);
                fieldStatus_[field] = type.status;
                return type;
            }
                
            case FIELD_EMAIL :
            {
                boost::regex regular ("^([a-z0-9]+)(\\.)([a-z0-9]+)(\\.)([a-z0-9]+)(@)(tradingcompany)(\\.)(ru)$");
                if (value.empty())
                {
                    const std::string email = utils::createEmail(std::vector<std::string>{surname_, name_, patronymic_});
                    if (boost::regex_match(email, regular))
                    {
                        value = email;
                        type.status = ST_OK;
                        Logger::info << "Почта >> " << value << std::endl;
                    }
                    else
                    {
                        type.status = ST_EMPTY;
                        Logger::error << "Пустая почта >> " << value << std::endl;
                    }
                }
                else if (!boost::regex_match(value, regular))
                {
                    const std::string email = utils::createEmail(std::vector<std::string>{surname_, name_, patronymic_});
                    if (boost::regex_match(email, regular))
                    {
                        value = email;
                        type.status = ST_OK;
                        Logger::info << "Почта >> " << value << std::endl;
                    }
                    else
                    {
                        type.status = ST_WRONGDATA;
                        Logger::warning << "Некорректная почта >> " << value << std::endl;
                    }
                }
                else
                {
                    type.status = ST_OK;
                    email_.empty() ? Logger::info << "Почта >> " << value << std::endl :
                                    (Logger::info << "Почта << " << email_ << " >> изменена на >> " << value << std::endl,
                                     std::cout << "Почта успешно изменена" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_DATE_OF_HIRING :
            {
                boost::regex regular ("^(((0[1-9]|[12][0-9]|30)[-/.]?(0[13-9]|1[012])|31[-/.]?(0[13578]|1[02])|(0[1-9]|"
                                      "1[0-9]|2[0-8])[-/.]?02)[-/.]?[0-9]{4}|29[-/.]?02[-/.]?([0-9]{2}(([2468][048]|"
                                      "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая дата принятия на работу >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная дата принятия на работу >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    dateOfHiring_.empty() ? Logger::info << "Дата принятия на работу >> " << value << std::endl :
                                           (Logger::info << "Дата принятия на работу << " << dateOfHiring_ << " >> изменена на >> " << value << std::endl,
                                            std::cout << "Дата принятия на работу успешно изменена" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_WORKING_HOURS :
            {
                boost::regex regular ("(((((Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье),*)+)|"
                                      "(Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье)-"
                                      "(Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье))="
                                      "([0-1]?[0-9]|[2][0-3]]):([0-5][0-9])-([0-1]?[0-9]|[2][0-3]):([0-5][0-9]);*)+");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустые часы работы >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректные часы работы >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    workingHours_.empty() ? Logger::info << "Часы работы >> " << value << std::endl :
                                           (Logger::info << "Часы работы << " << workingHours_ << " >> изменены на >> " << value << std::endl,
                                            std::cout << "Часы работы успешно изменены" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_SALARY :
            {
                boost::regex regular ("[0-9]+");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая зарплата >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная зарплата >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !salary_ ? Logger::info << "Зарплата >> " << value << std::endl :
                              (Logger::info << "Зарплата << " << salary_ << " >> изменена на >> " << value << std::endl,
                               std::cout << "Зарплата успешно изменена" << std::endl);
                }
                type.uintValue = std::atoi(value.c_str());
                fieldStatus_[field] = type.status;
                return type;
            }
        
            case FIELD_PASSWORD :
            {
                boost::regex regular ("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{6,}");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой пароль >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный пароль >> " << value << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    password_.empty() ? Logger::info << "Пароль >> " << value << std::endl :
                                       (Logger::info << "Пароль << " << password_ << " >> изменен на >> " << value << std::endl,
                                        std::cout << "Пароль успешно изменен" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
                
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
    return TradingCompany::empty;
}

const TradingCompany& TradingCompany::operator = (const TradingCompany &object)
{
    position_ = object.position_;
    surname_ = object.surname_;
    name_ = object.name_;
    patronymic_ = object.patronymic_;
    sex_ = object.sex_;
    dateOfBirth_ = object.dateOfBirth_;
    passport_ = object.passport_;
    phone_ = object.phone_;
    email_ = object.email_;
    dateOfHiring_ = object.dateOfHiring_;
    workingHours_ = object.workingHours_;
    salary_ = object.salary_;
    password_ = object.password_;
    return *this;
}

void operator >> (const std::string &line, TradingCompany &tradingCompany)
{
    std::string input;
    std::stringstream is(line);
    try
    {
        while (is >> input)
        {
            std::string parameter = boost::regex_replace(input, boost::regex("[^A-Za-z]"), "");
            auto found = tradingCompany.setParameters_.find(parameter);
            
            if (found != tradingCompany.setParameters_.end())
            {
                auto setParameter = found->second;
                is >> input;
                if (setParameter != nullptr)
                {
                    if (*input.begin() != ('\"') && *(input.end() - 1) != ('\"'))
                    {
                        input.clear();
                    }
                    else
                    {
                        input = input.substr(1, input.length() - 2);
                    }
                    setParameter(tradingCompany, input);
                }
            }
            else
            {
                throw input;
            }
        }
    }
    catch (const std::string &exception)
    {
        Logger::error << "Неверный параметр >> " << exception << std::endl;
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

std::ostream& operator << (std::ostream &out, const TradingCompany &tradingCompany)
{
    out << "ID: "                      << tradingCompany.id_           << ", ";
    out << "Должность: "               << tradingCompany.position_     << ", ";
    out << "Фамилия: "                 << tradingCompany.surname_      << ", ";
    out << "Имя: "                     << tradingCompany.name_         << ", ";
    out << "Отчество: "                << tradingCompany.patronymic_   << ", ";
    out << "Пол: "                     << tradingCompany.sex_          << ", ";
    out << "Дата рождения: "           << tradingCompany.dateOfBirth_  << ", ";
    out << "Паспорт: "                 << tradingCompany.passport_     << ", ";
    out << "Телефон: "                 << tradingCompany.phone_        << ", ";
    out << "Почта: "                   << tradingCompany.email_        << ", ";
    out << "Дата принятия на работу: " << tradingCompany.dateOfHiring_ << ", ";
    out << "Часы работы: "             << tradingCompany.workingHours_ << ", ";
    out << "Зарплата: "                << tradingCompany.salary_       << ", ";
    out << "Пароль: "                  << tradingCompany.password_;
    return out;
}

bool operator == (const TradingCompany &first, const TradingCompany &second)
{
    return (first.email_ == second.email_) &&
           (first.password_ == second.password_);
}



