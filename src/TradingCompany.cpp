#include <boost/regex.hpp>

#include "TradingCompany.h"

const TradingCompany& TradingCompany::operator = (const TradingCompany &object)
{
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

    // Передача статусов полей от объекта к *this
    std::for_each(std::begin(fieldStatus_), std::end(fieldStatus_), [this, &object](auto &field)
    {
        this->fieldStatus_[field.first] = object.fieldStatus_.at(field.first);
    });

    return *this;
}

void operator >> (const std::string &line, TradingCompany &object)
{
    std::string input;
    std::stringstream is(line);
    try
    {
        while (is >> input)
        {
            // Удаление всех символов, кроме латинских букв
            std::string parameter = boost::regex_replace(input, boost::regex("[^A-Za-z]"), "");
            auto found = object.setParameters_.find(parameter); // Поиск обертки инициализации поля по параметру

            if (found != object.setParameters_.end())
            {
                auto setParameter = found->second;
                is >> input;
                if (setParameter != nullptr)
                {
                    // Поиск кавычек
                    if (*input.begin() != ('\"') && *(input.end() - 1) != ('\"'))
                    {
                        input.clear();
                    }
                    else
                    {
                        input = input.substr(1, input.length() - 2);
                    }
                    setParameter(object, input); // Инициализация поля
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
}

std::ostream& operator << (std::ostream &out, const TradingCompany &object)
{
    out << "ID: "                      << object.id_           << ", ";
    out << "Должность: "               << object.position_     << ", ";
    out << "Фамилия: "                 << object.surname_      << ", ";
    out << "Имя: "                     << object.name_         << ", ";
    out << "Отчество: "                << object.patronymic_   << ", ";
    out << "Пол: "                     << object.sex_          << ", ";
    out << "Дата рождения: "           << object.dateOfBirth_  << ", ";
    out << "Паспорт: "                 << object.passport_     << ", ";
    out << "Телефон: "                 << object.phone_        << ", ";
    out << "Почта: "                   << object.email_        << ", ";
    out << "Дата принятия на работу: " << object.dateOfHiring_ << ", ";
    out << "Часы работы: "             << object.workingHours_ << ", ";
    out << "Зарплата: "                << object.salary_       << ", ";
    out << "Пароль: "                  << object.password_;
    return out;
}

bool operator == (const TradingCompany &first, const TradingCompany &second)
{
    return (first.email_ == second.email_) &&
           (first.password_ == second.password_);
}

template<>
uint TradingCompany::Get<uint>(const std::string &value, const Field field)
{
    return CheckField(value, field).uintValue;
}

template<>
uint64_t TradingCompany::Get<uint64_t>(const std::string &value, const Field field)
{
    return CheckField(value, field).uint64Value;
}

template<>
std::string TradingCompany::Get<std::string>(const std::string &value, const Field field)
{
    return CheckField(value, field).stringValue;
}

void TradingCompany::SetId(const std::string &id)
{
    id_ = Get<uint>(id, FIELD_ID);
}

void TradingCompany::SetPosition(const std::string &position)
{
    position_ = Get<std::string>(position, FIELD_POSITION);
}

void TradingCompany::SetSurname(const std::string &surname)
{
    surname_ = Get<std::string>(surname, FIELD_SURNAME);
}

void TradingCompany::SetName(const std::string &name)
{
    name_ = Get<std::string>(name, FIELD_NAME);
}

void TradingCompany::SetPatronymic(const std::string &patronymic)
{
    patronymic_ = Get<std::string>(patronymic, FIELD_PATRONYMIC);
}

void TradingCompany::SetSex(const std::string &sex)
{
    sex_ = Get<std::string>(sex, FIELD_SEX);
}

void TradingCompany::SetDateOfBirth(const std::string &dateOfBirth)
{
    dateOfBirth_ = Get<std::string>(dateOfBirth, FIELD_DATE_OF_BIRTH);
}

void TradingCompany::SetPassport(const std::string &passport)
{
    passport_ = Get<uint64_t>(passport, FIELD_PASSPORT);
}

void TradingCompany::SetPhone(const std::string &phone)
{
    phone_ = Get<uint64_t>(phone, FIELD_PHONE);
}

void TradingCompany::SetEmail(const std::string &email)
{
    email_ = Get<std::string>(email, FIELD_EMAIL);
}

void TradingCompany::SetDateOfHiring(const std::string &dateOfHiring)
{
    dateOfHiring_ = Get<std::string>(dateOfHiring, FIELD_DATE_OF_HIRING);
}

void TradingCompany::SetWorkingHours(const std::string &workingHours)
{
    workingHours_ = Get<std::string>(workingHours, FIELD_WORKING_HOURS);
}

void TradingCompany::SetSalary(const std::string &salary)
{
    salary_ = Get<uint>(salary, FIELD_SALARY);
}

void TradingCompany::SetPassword(const std::string &password)
{
    password_ = Get<std::string>(password, FIELD_PASSWORD);
}

uint TradingCompany::GetId() const
{
    return id_;
}

std::string TradingCompany::GetPosition() const
{
    return position_;
}

std::string TradingCompany::GetSurname() const
{
    return surname_;
}

std::string TradingCompany::GetName() const
{
    return name_;
}

std::string TradingCompany::GetPatronymic() const
{
    return patronymic_;
}

std::string TradingCompany::GetSex() const
{
    return sex_;
}

std::string TradingCompany::GetDateOfBirth() const
{
    return dateOfBirth_;
}

uint64_t TradingCompany::GetPassport() const
{
    return passport_;
}

uint64_t TradingCompany::GetPhone() const
{
    return phone_;
}

std::string TradingCompany::GetEmail() const
{
    return email_;
}

std::string TradingCompany::GetDateOfHiring() const
{
    return dateOfHiring_;
}

std::string TradingCompany::GetWorkingHours() const
{
    return workingHours_;
}

uint TradingCompany::GetSalary() const
{
    return salary_;
}

std::string TradingCompany::GetPassword() const
{
    return password_;
}

const TradingCompany::Type TradingCompany::CheckField(std::string value, const Field field)
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
                          (Logger::info << "ID << " << id_ << " >> изменен на >> " << value << std::endl,
                           std::cout << "ID успешно изменен" << std::endl);
                }
                type.uintValue = std::atoi(value.c_str());
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_POSITION :
            {
                Utils::ToUpperandtolower(value);
                boost::regex regular ("(Бухгалтер|Водитель|Главный_бухгалтер|Главный_юрист-консультант|Грузчик|Директор|Кассир|Логист|"
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
                                       (Logger::info << "Должность << " << position_ << " >> изменена на >> " << value << std::endl,
                                        std::cout << "Должность успешно изменена" << std::endl);
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_SURNAME :
            {
                Utils::ToUpperandtolower(value);
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
                Utils::ToUpperandtolower(value);
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
                Utils::ToUpperandtolower(value);
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
                Utils::ToUpperandtolower(value);
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
                boost::regex regular ("^(((((0[1-9]|[12][0-9]|30)[-/.])?(0[13-9]|1[012])|(31[-/.])?(0[13578]|1[02])|((0[1-9]|"
                                      "1[0-9]|2[0-8])[-/.])?02)[-/.])?[0-9]{4}|(29[-/.])?(02[-/.])?([0-9]{2}(([2468][048]|"
                                      "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (value.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая дата рождения >> " << value << std::endl;
                }
                else if (!boost::regex_match(value, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная дата рождения >> " << value << std::endl;
                }
                else
                {
                    // Нахождение возраста
                    std::vector<std::string> data = Utils::SplitString(Utils::Date(), " .-");
                    std::vector<std::string> dateOfBirth = Utils::SplitString(value, " .-");
                    auto age = Utils::FindAge(data, dateOfBirth);
                    int year = age[0];
                    int month = age[1];
                    int day = age[2];
                    if (year < 18)
                    {
                        type.status = ST_WRONGDATA;
                        Logger::warning << "Неудовлетворительный возраст >> " << "Лет: " << year << "Месяцев: " << month << "Дней: " << day << std::endl;
                    }
                    else
                    {
                        type.status = ST_OK;
                        dateOfBirth_.empty() ? Logger::info << "Дата рождения >> " << value << std::endl :
                                              (Logger::info << "Дата рождения << " << dateOfBirth_ << " >> изменена на >> " << value << std::endl,
                                               std::cout << "Дата рождения успешно изменена" << std::endl);
                    }
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
                    // Создание почты из фамилии, имени и отчества
                    const std::string email = Utils::CreateEmail(std::vector<std::string>{surname_, name_, patronymic_});
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
                     // Создание почты из фамилии, имени и отчества
                    const std::string email = Utils::CreateEmail(std::vector<std::string>{surname_, name_, patronymic_});
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
                boost::regex regular ("^(((((0[1-9]|[12][0-9]|30)[-/.])?(0[13-9]|1[012])|(31[-/.])?(0[13578]|1[02])|((0[1-9]|"
                                      "1[0-9]|2[0-8])[-/.])?02)[-/.])?[0-9]{4}|(29[-/.])?(02[-/.])?([0-9]{2}(([2468][048]|"
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
    catch(const Field field)
    {
        Logger::error << "Неверный параметр поля >> " + std::to_string(field) << std::endl;
    }
    return TradingCompany::empty;
}

void TradingCompany::Recursion(const Field field,
                               std::function<void(TradingCompany&, std::string&)> setParameter,
                               const std::string &message)
{
    if (fieldStatus_[field] != ST_OK)
    {
        std::cout << message << std::endl;
        std::string newMessage;
        auto condition = message.find("ведите"); // Отсечение заглавной буквы "В" от слова "Введите"
        if (condition != std::string::npos)
        {
            newMessage = message.substr(condition);
        }
        std::cout << "Ввод: ";
        std::string input;
        std::cin >> input;
        setParameter(*this, input);
        // Рекурсионный вызов после ввода значения поля
        Recursion(field, setParameter, "Некорректно введен параметр, в" + newMessage);
    }
}

void TradingCompany::CheckId(const std::string &warning)
{
    const std::string message = "Введите ID (например, 100)";
    Recursion(FIELD_ID, &TradingCompany::SetId, warning + message);
}

void TradingCompany::CheckPosition(const std::string &warning)
{
    const std::string message = "Введите должность";
    Recursion(FIELD_POSITION, &TradingCompany::SetPosition, warning + message);
}

void TradingCompany::CheckSurname(const std::string &warning)
{
    const std::string message = "Введите фамилию";
    Recursion(FIELD_SURNAME, &TradingCompany::SetSurname, warning + message);
}

void TradingCompany::CheckName(const std::string &warning)
{
    const std::string message = "Введите имя";
    Recursion(FIELD_NAME, &TradingCompany::SetName, warning + message);
}

void TradingCompany::CheckPatronymic(const std::string &warning)
{
    const std::string message = "Введите отчество";
    Recursion(FIELD_PATRONYMIC, &TradingCompany::SetPatronymic, warning + message);
}

void TradingCompany::CheckSex(const std::string &warning)
{
    const std::string message = "Введите пол (например, Муж)";
    Recursion(FIELD_SEX, &TradingCompany::SetSex, warning + message);
}

void TradingCompany::CheckDateOfBirth(const std::string &warning)
{
    const std::string message = "Введите дату рождения (например, 16.12.1995 или 16/12/1995 или 16-12-1995)";
    Recursion(FIELD_DATE_OF_BIRTH, &TradingCompany::SetDateOfBirth, warning + message);
}

void TradingCompany::CheckPassport(const std::string &warning)
{
    const std::string message = "Введите номер паспорта (например, 4516561974)";
    Recursion(FIELD_PASSPORT, &TradingCompany::SetPassport, warning + message);
}

void TradingCompany::CheckPhone(const std::string &warning)
{
    const std::string message = "Введите номер телефона (например, 9032697963)";
    Recursion(FIELD_PHONE, &TradingCompany::SetPhone, warning + message);
}

void TradingCompany::CheckEmail(const std::string &warning)
{
    // Создание почты автоматически из фамилии, имени и отчества
    if (fieldStatus_[FIELD_EMAIL] == ST_EMPTY || fieldStatus_[FIELD_EMAIL] == ST_WRONGDATA)
    {
        const std::string email = Utils::CreateEmail(std::vector<std::string>{surname_, name_, patronymic_});
        SetEmail(email);
    }
    // Создание почты вручную
    else if (fieldStatus_[FIELD_EMAIL] == ST_OVERWRITEDATA)
    {
        const std::string message = "Введите почту (например, surname.name.patronymic@tradingcompany.ru)";
        Recursion(FIELD_EMAIL, &TradingCompany::SetEmail, warning + message);
    }
    // Добавление доп. числа (от 0 до 100) к существующей почте
    if (fieldStatus_[FIELD_EMAIL] == ST_DUBLICATE)
    {
        const std::string email = Utils::CreateEmail(std::vector<std::string>{surname_, name_, patronymic_});
        std::string firstPartEmail = email.substr(0, email.find("@"));
        uint secondPartEmail = 0;
        std::cout << warning;
        std::cout << "Ваша первая часть почты: " + firstPartEmail << std::endl;
        std::cout << "Введите вторую часть почты (это должно быть число от 1 до 99)" << std::endl;
        std::cout << "Ввод: ";
        while (true)
        {
            std::cin >> secondPartEmail;
            if (secondPartEmail > 0 && secondPartEmail < 100)
            {
                break;
            }
            else
            {
                std::cout << "Некорректно введен параметр, введите вторую часть почты (это должно быть число от 1 до 99)" << std::endl;
            }
        }
        SetEmail(firstPartEmail + std::to_string(secondPartEmail) + "@tradingcompany.ru");
    }
}

void TradingCompany::CheckDateOfHiring(const std::string &warning)
{
    const std::string message = "Введите дату принятия на работу (например, 16.04.2018 или 16/04/2018 или 16-04-2018)";
    Recursion(FIELD_DATE_OF_HIRING, &TradingCompany::SetDateOfHiring, warning + message);
}

void TradingCompany::CheckWorkingHours(const std::string &warning)
{
    const std::string message = "Введите время работы (например, Понедельник=09:00-18:00 или "
                                                                "Понедельник-Пятница=09:00-18:00 или "
                                                                "Понедельник=09:00-18:00;Пятница=09:00-18:00)";
    Recursion(FIELD_WORKING_HOURS, &TradingCompany::SetWorkingHours, warning + message);
}

void TradingCompany::CheckSalary(const std::string &warning)
{
    const std::string message = "Введите зарплату (в рублях)";
    Recursion(FIELD_SALARY, &TradingCompany::SetSalary, warning + message);
}

void TradingCompany::CheckPassword(const std::string &warning)
{
    const std::string message = "Введите новый пароль (пароль должен содержать:\n-не менее 6 символов\n"
                                "-хотя бы одну прописную латинскую букву\n"
                                "-хотя бы одну строчную латинскую букву\n"
                                "-хотя бы одну цифру)";
    Recursion(FIELD_PASSWORD, &TradingCompany::SetPassword, warning + message);
}

void TradingCompany::ChangeStatusPosition()
{
    fieldStatus_[FIELD_POSITION] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись должности >> " << position_ << std::endl;
}

void TradingCompany::ChangeStatusSurname()
{
    fieldStatus_[FIELD_SURNAME] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись фамилии >> " << surname_ << std::endl;
}

void TradingCompany::ChangeStatusName()
{
    fieldStatus_[FIELD_NAME] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись имени >> " << name_ << std::endl;
}

void TradingCompany::ChangeStatusPatronymic()
{
    fieldStatus_[FIELD_PATRONYMIC] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись отчества >> " << patronymic_ << std::endl;
}

void TradingCompany::ChangeStatusSex()
{
    fieldStatus_[FIELD_SEX] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись пола >> " << sex_ << std::endl;
}

void TradingCompany::ChangeStatusDateOfBirth()
{
    fieldStatus_[FIELD_DATE_OF_BIRTH] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись даты рождения >> " << dateOfBirth_ << std::endl;
}

void TradingCompany::ChangeStatusPassport(const bool canOverwrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_PASSPORT] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись паспорта >> " << passport_ << std::endl;
    }
    else
    {
        uint64_t passport = passport_;
        passport_ = rand(); // Перезапись на случайное число
        fieldStatus_[FIELD_PASSPORT] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся паспорт >> " << passport << " изменен на >> " << passport_ << std::endl;
    }
}

void TradingCompany::ChangeStatusPhone(const bool canOverwrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_PHONE] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись телефона >> " << phone_ << std::endl;
    }
    else
    {
        uint64_t phone = phone_;
        phone_ = rand(); // Перезапись на случайное число
        fieldStatus_[FIELD_PHONE] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся телефон >> " << phone << " изменен на >> " << phone_ << std::endl;
    }
}

void TradingCompany::ChangeStatusEmail(const bool canOverwrite)
{
    if (canOverwrite)
    {
        fieldStatus_[FIELD_EMAIL] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись почты >> " << email_ << std::endl;
    }
    else
    {
        fieldStatus_[FIELD_EMAIL] = ST_DUBLICATE;
        Logger::warning << "Повторяющаяся почта >> " << email_ << std::endl;
    }
}

void TradingCompany::ChangeStatusDateOfHiring()
{
    fieldStatus_[FIELD_DATE_OF_HIRING] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись даты принятия на работу >> " << dateOfHiring_ << std::endl;
}

void TradingCompany::ChangeStatusWorkingHours()
{
    fieldStatus_[FIELD_WORKING_HOURS] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись часов работы >> " << workingHours_ << std::endl;
}

void TradingCompany::ChangeStatusSalary()
{
    fieldStatus_[FIELD_SALARY] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись зарплаты >> " << salary_ << std::endl;
}

void TradingCompany::ChangeStatusPassword()
{
    fieldStatus_[FIELD_PASSWORD] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись пароля >> " << password_ << std::endl;
}


