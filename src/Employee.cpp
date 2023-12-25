#include "Employee.h"
#include "Utils.h"

#include <boost/regex.hpp>

const IEmployee& Employee::operator = (const IEmployee &other)
{
    _surname = static_cast<const Employee&>(other)._surname;
    _name = static_cast<const Employee&>(other)._name;
    _patronymic = static_cast<const Employee&>(other)._patronymic;
    _sex = static_cast<const Employee&>(other)._sex;
    _dateOfBirth = static_cast<const Employee&>(other)._dateOfBirth;
    _passport = static_cast<const Employee&>(other)._passport;
    _phone = static_cast<const Employee&>(other)._phone;
    _email = static_cast<const Employee&>(other)._email;
    _dateOfHiring = static_cast<const Employee&>(other)._dateOfHiring;
    _salary = static_cast<const Employee&>(other)._salary;
    _workingHours = static_cast<const Employee&>(other)._workingHours;
    _password = static_cast<const Employee&>(other)._password;

//     Передача статусов полей от объекта к *this
    std::for_each(std::begin(_fieldStatus), std::end(_fieldStatus), [this, &other](auto &field)
    {
        this->_fieldStatus[field.first] = static_cast<const Employee&>(other)._fieldStatus.at(field.first);
    });

    return *this;
}

void Employee::operator >> (const std::string &iLine)
{
    std::string input;
    std::stringstream is(iLine);
    try
    {
        while (is >> input)
        {
            // Удаление всех символов, кроме латинских букв
            std::string parameter = boost::regex_replace(input, boost::regex("[^A-Za-z]"), "");
            auto found = _setParameters.find(parameter); // Поиск обертки инициализации поля по параметру

            if (found != _setParameters.end())
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
                    setParameter(*this, input); // Инициализация поля
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

std::ostream& Employee::operator << (std::ostream &ioOut) const noexcept
{
    ioOut << "ID: "                      << _id           << ", ";
    ioOut << "Должность: "               << _position     << ", ";
    ioOut << "Фамилия: "                 << _surname      << ", ";
    ioOut << "Имя: "                     << _name         << ", ";
    ioOut << "Отчество: "                << _patronymic   << ", ";
    ioOut << "Пол: "                     << _sex          << ", ";
    ioOut << "Дата рождения: "           << _dateOfBirth  << ", ";
    ioOut << "Паспорт: "                 << _passport     << ", ";
    ioOut << "Телефон: "                 << _phone        << ", ";
    ioOut << "Почта: "                   << _email        << ", ";
    ioOut << "Дата принятия на работу: " << _dateOfHiring << ", ";
    ioOut << "Часы работы: "             << _workingHours << ", ";
    ioOut << "Зарплата: "                << _salary       << ", ";
    ioOut << "Пароль: "                  << _password;
    return ioOut;
}

bool Employee::operator == (const IEmployee &other) const noexcept
{
    return (_email == static_cast<const Employee&>(other)._email) &&
           (_password == static_cast<const Employee&>(other)._password);
}

template<>
uint Employee::Get<uint>(const std::string &iValue, const Field iField)
{
    return CheckField(iValue, iField).uintValue;
}

template<>
uint64_t Employee::Get<uint64_t>(const std::string &iValue, const Field iField)
{
    return CheckField(iValue, iField).uint64Value;
}

template<>
std::string Employee::Get<std::string>(const std::string &iValue, const Field iField)
{
    return CheckField(iValue, iField).stringValue;
}

void Employee::SetId(const std::string &iID)
{
    _id = Get<uint>(iID, FIELD_ID);
}

void Employee::SetPosition(const std::string &iPosition)
{
    _position = Get<std::string>(iPosition, FIELD_POSITION);
}

void Employee::SetSurname(const std::string &iSurname)
{
    _surname = Get<std::string>(iSurname, FIELD_SURNAME);
}

void Employee::SetName(const std::string &iName)
{
    _name = Get<std::string>(iName, FIELD_NAME);
}

void Employee::SetPatronymic(const std::string &iPatronymic)
{
    _patronymic = Get<std::string>(iPatronymic, FIELD_PATRONYMIC);
}

void Employee::SetSex(const std::string &iSex)
{
    _sex = Get<std::string>(iSex, FIELD_SEX);
}

void Employee::SetDateOfBirth(const std::string &iDateOfBirth)
{
    _dateOfBirth = Get<std::string>(iDateOfBirth, FIELD_DATE_OF_BIRTH);
}

void Employee::SetPassport(const std::string &iPassport)
{
    _passport = Get<uint64_t>(iPassport, FIELD_PASSPORT);
}

void Employee::SetPhone(const std::string &iPhone)
{
    _phone = Get<uint64_t>(iPhone, FIELD_PHONE);
}

void Employee::SetEmail(const std::string &iEmail)
{
    _email = Get<std::string>(iEmail, FIELD_EMAIL);
}

void Employee::SetDateOfHiring(const std::string &iDateOfHiring)
{
    _dateOfHiring = Get<std::string>(iDateOfHiring, FIELD_DATE_OF_HIRING);
}

void Employee::SetWorkingHours(const std::string &iWorkingHours)
{
    _workingHours = Get<std::string>(iWorkingHours, FIELD_WORKING_HOURS);
}

void Employee::SetSalary(const std::string &iSalary)
{
    _salary = Get<uint>(iSalary, FIELD_SALARY);
}

void Employee::SetPassword(const std::string &iPassword)
{
    _password = Get<std::string>(iPassword, FIELD_PASSWORD);
}

uint Employee::GetId() const noexcept
{
    return _id;
}

std::string Employee::GetPosition() const noexcept
{
    return _position;
}

std::string Employee::GetSurname() const noexcept
{
    return _surname;
}

std::string Employee::GetName() const noexcept
{
    return _name;
}

std::string Employee::GetPatronymic() const noexcept
{
    return _patronymic;
}

std::string Employee::GetSex() const noexcept
{
    return _sex;
}

std::string Employee::GetDateOfBirth() const noexcept
{
    return _dateOfBirth;
}

uint64_t Employee::GetPassport() const noexcept
{
    return _passport;
}

uint64_t Employee::GetPhone() const noexcept
{
    return _phone;
}

std::string Employee::GetEmail() const noexcept
{
    return _email;
}

std::string Employee::GetDateOfHiring() const noexcept
{
    return _dateOfHiring;
}

std::string Employee::GetWorkingHours() const noexcept
{
    return _workingHours;
}

uint Employee::GetSalary() const noexcept
{
    return _salary;
}

std::string Employee::GetPassword() const noexcept
{
    return _password;
}

void Employee::PrintPersonalData() noexcept
{
    Logger::info << "***************** Вывод личных данных ******************" << std::endl;
    std::cout << std::endl;
    std::cout << "***************** Вывод личных данных ******************" << std::endl;
    std::cout << this << std::endl;
}

const Employee::Type Employee::CheckField(std::string iValue, const Field iField)
{
    Type type;

    try
    {
        switch (iField)
        {
            case FIELD_ID :
            {
                boost::regex regular ("^[0-9]{1,4}$");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой ID >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный ID >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !_id ? Logger::info << "ID >> " << iValue << std::endl :
                          (Logger::info << "ID << " << _id << " >> изменен на >> " << iValue << std::endl,
                           std::cout << "ID успешно изменен" << std::endl);
                }
                type.uintValue = std::atoi(iValue.c_str());
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_POSITION :
            {
                Utils::ToUpperandtolower(iValue);
                boost::regex regular ("(Бухгалтер|Водитель|Главный_бухгалтер|Главный_юрист-консультант|Грузчик|Директор|Кассир|Логист|"
                                      "Менеджер_по_закупкам|Менеджер_по_продажам|Начальник_отдела_закупок|Начальник_склада|Юрист|Менеджер_по_персоналу)");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая должность >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная должность >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _position.empty() ? Logger::info << "Должность >> " << iValue << std::endl :
                                       (Logger::info << "Должность << " << _position << " >> изменена на >> " << iValue << std::endl,
                                        std::cout << "Должность успешно изменена" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_SURNAME :
            {
                Utils::ToUpperandtolower(iValue);
                boost::regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая фамилия >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная фамилия >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _surname.empty() ? Logger::info << "Фамилия >> " << iValue << std::endl :
                                      (Logger::info << "Фамилия << " << _surname << " >> изменена на >> " << iValue << std::endl,
                                       std::cout << "Фамилия успешно изменена" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_NAME :
            {
                Utils::ToUpperandtolower(iValue);
                boost::regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::info << "Пустое имя >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорретное имя >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _name.empty() ? Logger::info << "Имя >> " << iValue << std::endl :
                                   (Logger::info << "Имя << " << _name << " >> изменено на >> " << iValue << std::endl,
                                    std::cout << "Имя успешно изменено" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_PATRONYMIC :
            {
                Utils::ToUpperandtolower(iValue);
                boost::regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустое отчество >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорретное отчество >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _patronymic.empty() ? Logger::info << "Отчество >> " << iValue << std::endl :
                                         (Logger::info << "Отчество << " << _patronymic << " >> изменено на >> " << iValue << std::endl,
                                          std::cout << "Отчество успешно изменено" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_SEX :
            {
                Utils::ToUpperandtolower(iValue);
                boost::regex regular ("^(Муж|Жен)$");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой пол >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный пол >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _sex.empty() ? Logger::info << "Пол >> " << iValue << std::endl :
                                  (Logger::info << "Пол << " << _sex << " >> изменен на >> " << iValue << std::endl,
                                   std::cout << "Пол успешно изменен" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_DATE_OF_BIRTH :
            {
                boost::regex regular ("^(((((0[1-9]|[12][0-9]|30)[-/.])?(0[13-9]|1[012])|(31[-/.])?(0[13578]|1[02])|((0[1-9]|"
                                      "1[0-9]|2[0-8])[-/.])?02)[-/.])?[0-9]{4}|(29[-/.])?(02[-/.])?([0-9]{2}(([2468][048]|"
                                      "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая дата рождения >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная дата рождения >> " << iValue << std::endl;
                }
                else
                {
                    // Нахождение возраста
                    std::vector<std::string> data = Utils::SplitString(Utils::Date(), " .-");
                    std::vector<std::string> dateOfBirth = Utils::SplitString(iValue, " .-");
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
                        _dateOfBirth.empty() ? Logger::info << "Дата рождения >> " << iValue << std::endl :
                                              (Logger::info << "Дата рождения << " << _dateOfBirth << " >> изменена на >> " << iValue << std::endl,
                                               std::cout << "Дата рождения успешно изменена" << std::endl);
                    }
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_PASSPORT :
            {
                boost::regex regular ("^[0-9]{10}$");
                boost::regex_match(iValue, regular);
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой паспорт >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный паспорт >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !_passport ? Logger::info << "Паспорт >> " << iValue << std::endl :
                                (Logger::info << "Паспорт << " << _passport << " >> изменен на >> " << iValue << std::endl,
                                 std::cout << "Паспорт успешно изменен" << std::endl);
                }
                type.uint64Value = std::strtoul(iValue.c_str(), NULL, 0);
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_PHONE :
            {
                boost::regex regular ("^[0-9]{10}$");
                boost::regex_match(iValue, regular);
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой телефон >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный телефон >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !_phone ? Logger::info << "Телефон >> " << iValue << std::endl :
                             (Logger::info << "Телефон << " << _phone << " >> изменен на >> " << iValue << std::endl,
                              std::cout << "Телефон успешно изменен" << std::endl);
                }
                type.uint64Value = std::strtoul(iValue.c_str(), NULL, 0);
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_EMAIL :
            {
                boost::regex regular ("^([a-z0-9]+)(\\.)([a-z0-9]+)(\\.)([a-z0-9]+)(@)(tradingcompany)(\\.)(ru)$");
                if (iValue.empty())
                {
                    // Создание почты из фамилии, имени и отчества
                    const std::string email = Utils::CreateEmail(std::vector<std::string>{_surname, _name, _patronymic});
                    if (boost::regex_match(email, regular))
                    {
                        iValue = email;
                        type.status = ST_OK;
                        Logger::info << "Почта >> " << iValue << std::endl;
                    }
                    else
                    {
                        type.status = ST_EMPTY;
                        Logger::error << "Пустая почта >> " << iValue << std::endl;
                    }
                }
                else if (!boost::regex_match(iValue, regular))
                {
                     // Создание почты из фамилии, имени и отчества
                    const std::string email = Utils::CreateEmail(std::vector<std::string>{_surname, _name, _patronymic});
                    if (boost::regex_match(email, regular))
                    {
                        iValue = email;
                        type.status = ST_OK;
                        Logger::info << "Почта >> " << iValue << std::endl;
                    }
                    else
                    {
                        type.status = ST_WRONGDATA;
                        Logger::warning << "Некорректная почта >> " << iValue << std::endl;
                    }
                }
                else
                {
                    type.status = ST_OK;
                    _email.empty() ? Logger::info << "Почта >> " << iValue << std::endl :
                                    (Logger::info << "Почта << " << _email << " >> изменена на >> " << iValue << std::endl,
                                     std::cout << "Почта успешно изменена" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_DATE_OF_HIRING :
            {
                boost::regex regular ("^(((((0[1-9]|[12][0-9]|30)[-/.])?(0[13-9]|1[012])|(31[-/.])?(0[13578]|1[02])|((0[1-9]|"
                                      "1[0-9]|2[0-8])[-/.])?02)[-/.])?[0-9]{4}|(29[-/.])?(02[-/.])?([0-9]{2}(([2468][048]|"
                                      "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая дата принятия на работу >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная дата принятия на работу >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _dateOfHiring.empty() ? Logger::info << "Дата принятия на работу >> " << iValue << std::endl :
                                           (Logger::info << "Дата принятия на работу << " << _dateOfHiring << " >> изменена на >> " << iValue << std::endl,
                                            std::cout << "Дата принятия на работу успешно изменена" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_WORKING_HOURS :
            {
                boost::regex regular ("(((((Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье),*)+)|"
                                      "(Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье)-"
                                      "(Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье))="
                                      "([0-1]?[0-9]|[2][0-3]):([0-5][0-9])-([0-1]?[0-9]|[2][0-3]):([0-5][0-9]);*)+");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустые часы работы >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректные часы работы >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _workingHours.empty() ? Logger::info << "Часы работы >> " << iValue << std::endl :
                                           (Logger::info << "Часы работы << " << _workingHours << " >> изменены на >> " << iValue << std::endl,
                                            std::cout << "Часы работы успешно изменены" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_SALARY :
            {
                boost::regex regular ("[0-9]+");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустая зарплата >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректная зарплата >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    !_salary ? Logger::info << "Зарплата >> " << iValue << std::endl :
                              (Logger::info << "Зарплата << " << _salary << " >> изменена на >> " << iValue << std::endl,
                               std::cout << "Зарплата успешно изменена" << std::endl);
                }
                type.uintValue = std::atoi(iValue.c_str());
                _fieldStatus[iField] = type.status;
                return type;
            }

            case FIELD_PASSWORD :
            {
                boost::regex regular ("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{6,}");
                if (iValue.empty())
                {
                    type.status = ST_EMPTY;
                    Logger::error << "Пустой пароль >> " << iValue << std::endl;
                }
                else if (!boost::regex_match(iValue, regular))
                {
                    type.status = ST_WRONGDATA;
                    Logger::warning << "Некорректный пароль >> " << iValue << std::endl;
                }
                else
                {
                    type.status = ST_OK;
                    _password.empty() ? Logger::info << "Пароль >> " << iValue << std::endl :
                                       (Logger::info << "Пароль << " << _password << " >> изменен на >> " << iValue << std::endl,
                                        std::cout << "Пароль успешно изменен" << std::endl);
                }
                type.stringValue = iValue;
                _fieldStatus[iField] = type.status;
                return type;
            }

            default:
                throw iField;
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
    return Employee::empty;
}

void Employee::Recursion(const Field iField,
                               std::function<void(Employee&, std::string&)> setParameter,
                               const std::string &iMessage)
{
    if (_fieldStatus[iField] != ST_OK)
    {
        std::cout << iMessage << std::endl;
        std::string newMessage;
        auto condition = iMessage.find("ведите"); // Отсечение заглавной буквы "В" от слова "Введите"
        if (condition != std::string::npos)
        {
            newMessage = iMessage.substr(condition);
        }
        std::cout << "Ввод: ";
        std::string input;
        std::cin >> input;
        setParameter(*this, input);
        // Рекурсионный вызов после ввода значения поля
        Recursion(iField, setParameter, "Некорректно введен параметр, в" + newMessage);
    }
}

void Employee::CheckId(const std::string &iWarning)
{
    const std::string message = "Введите ID (например, 100)";
    Recursion(FIELD_ID, &Employee::SetId, iWarning + message);
}

void Employee::CheckPosition(const std::string &iWarning)
{
    const std::string message = "Введите должность";
    Recursion(FIELD_POSITION, &Employee::SetPosition, iWarning + message);
}

void Employee::CheckSurname(const std::string &iWarning)
{
    const std::string message = "Введите фамилию";
    Recursion(FIELD_SURNAME, &Employee::SetSurname, iWarning + message);
}

void Employee::CheckName(const std::string &iWarning)
{
    const std::string message = "Введите имя";
    Recursion(FIELD_NAME, &Employee::SetName, iWarning + message);
}

void Employee::CheckPatronymic(const std::string &iWarning)
{
    const std::string message = "Введите отчество";
    Recursion(FIELD_PATRONYMIC, &Employee::SetPatronymic, iWarning + message);
}

void Employee::CheckSex(const std::string &iWarning)
{
    const std::string message = "Введите пол (например, Муж)";
    Recursion(FIELD_SEX, &Employee::SetSex, iWarning + message);
}

void Employee::CheckDateOfBirth(const std::string &iWarning)
{
    const std::string message = "Введите дату рождения (например, 16.12.1995 или 16/12/1995 или 16-12-1995)";
    Recursion(FIELD_DATE_OF_BIRTH, &Employee::SetDateOfBirth, iWarning + message);
}

void Employee::CheckPassport(const std::string &iWarning)
{
    const std::string message = "Введите номер паспорта (например, 4516561974)";
    Recursion(FIELD_PASSPORT, &Employee::SetPassport, iWarning + message);
}

void Employee::CheckPhone(const std::string &iWarning)
{
    const std::string message = "Введите номер телефона (например, 9032697963)";
    Recursion(FIELD_PHONE, &Employee::SetPhone, iWarning + message);
}

void Employee::CheckEmail(const std::string &iWarning)
{
    // Создание почты автоматически из фамилии, имени и отчества
    if (_fieldStatus[FIELD_EMAIL] == ST_EMPTY || _fieldStatus[FIELD_EMAIL] == ST_WRONGDATA)
    {
        const std::string email = Utils::CreateEmail(std::vector<std::string>{_surname, _name, _patronymic});
        SetEmail(email);
    }
    // Создание почты вручную
    else if (_fieldStatus[FIELD_EMAIL] == ST_OVERWRITEDATA)
    {
        const std::string message = "Введите почту (например, surname.name.patronymic@tradingcompany.ru)";
        Recursion(FIELD_EMAIL, &Employee::SetEmail, iWarning + message);
    }
    // Добавление доп. числа (от 0 до 100) к существующей почте
    if (_fieldStatus[FIELD_EMAIL] == ST_DUBLICATE)
    {
        const std::string email = Utils::CreateEmail(std::vector<std::string>{_surname, _name, _patronymic});
        std::string firstPartEmail = email.substr(0, email.find("@"));
        uint secondPartEmail = 0;
        std::cout << iWarning;
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

void Employee::CheckDateOfHiring(const std::string &iWarning)
{
    const std::string message = "Введите дату принятия на работу (например, 16.04.2018 или 16/04/2018 или 16-04-2018)";
    Recursion(FIELD_DATE_OF_HIRING, &Employee::SetDateOfHiring, iWarning + message);
}

void Employee::CheckWorkingHours(const std::string &iWarning)
{
    const std::string message = "Введите время работы (например, Понедельник=09:00-18:00 или "
                                                                "Понедельник-Пятница=09:00-18:00 или "
                                                                "Понедельник=09:00-18:00;Пятница=09:00-18:00)";
    Recursion(FIELD_WORKING_HOURS, &Employee::SetWorkingHours, iWarning + message);
}

void Employee::CheckSalary(const std::string &iWarning)
{
    const std::string message = "Введите зарплату (в рублях)";
    Recursion(FIELD_SALARY, &Employee::SetSalary, iWarning + message);
}

void Employee::CheckPassword(const std::string &iWarning)
{
    const std::string message = "Введите новый пароль (пароль должен содержать:\n-не менее 6 символов\n"
                                "-хотя бы одну прописную латинскую букву\n"
                                "-хотя бы одну строчную латинскую букву\n"
                                "-хотя бы одну цифру)";
    Recursion(FIELD_PASSWORD, &Employee::SetPassword, iWarning + message);
}

void Employee::ChangeStatusPosition()
{
    _fieldStatus[FIELD_POSITION] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись должности >> " << _position << std::endl;
}

void Employee::ChangeStatusSurname()
{
    _fieldStatus[FIELD_SURNAME] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись фамилии >> " << _surname << std::endl;
}

void Employee::ChangeStatusName()
{
    _fieldStatus[FIELD_NAME] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись имени >> " << _name << std::endl;
}

void Employee::ChangeStatusPatronymic()
{
    _fieldStatus[FIELD_PATRONYMIC] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись отчества >> " << _patronymic << std::endl;
}

void Employee::ChangeStatusSex()
{
    _fieldStatus[FIELD_SEX] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись пола >> " << _sex << std::endl;
}

void Employee::ChangeStatusDateOfBirth()
{
    _fieldStatus[FIELD_DATE_OF_BIRTH] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись даты рождения >> " << _dateOfBirth << std::endl;
}

void Employee::ChangeStatusPassport(const bool canOverwrite)
{
    if (canOverwrite)
    {
        _fieldStatus[FIELD_PASSPORT] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись паспорта >> " << _passport << std::endl;
    }
    else
    {
        uint64_t passport = _passport;
        _passport = rand(); // Перезапись на случайное число
        _fieldStatus[FIELD_PASSPORT] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся паспорт >> " << passport << " изменен на >> " << _passport << std::endl;
    }
}

void Employee::ChangeStatusPhone(const bool canOverwrite)
{
    if (canOverwrite)
    {
        _fieldStatus[FIELD_PHONE] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись телефона >> " << _phone << std::endl;
    }
    else
    {
        uint64_t phone = _phone;
        _phone = rand(); // Перезапись на случайное число
        _fieldStatus[FIELD_PHONE] = ST_DUBLICATE;
        Logger::warning << "Повторяющийся телефон >> " << phone << " изменен на >> " << _phone << std::endl;
    }
}

void Employee::ChangeStatusEmail(const bool canOverwrite)
{
    if (canOverwrite)
    {
        _fieldStatus[FIELD_EMAIL] = ST_OVERWRITEDATA;
        Logger::info << "Перезапись почты >> " << _email << std::endl;
    }
    else
    {
        _fieldStatus[FIELD_EMAIL] = ST_DUBLICATE;
        Logger::warning << "Повторяющаяся почта >> " << _email << std::endl;
    }
}

void Employee::ChangeStatusDateOfHiring()
{
    _fieldStatus[FIELD_DATE_OF_HIRING] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись даты принятия на работу >> " << _dateOfHiring << std::endl;
}

void Employee::ChangeStatusWorkingHours()
{
    _fieldStatus[FIELD_WORKING_HOURS] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись часов работы >> " << _workingHours << std::endl;
}

void Employee::ChangeStatusSalary()
{
    _fieldStatus[FIELD_SALARY] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись зарплаты >> " << _salary << std::endl;
}

void Employee::ChangeStatusPassword()
{
    _fieldStatus[FIELD_PASSWORD] = ST_OVERWRITEDATA;
    Logger::info << "Перезапись пароля >> " << _password << std::endl;
}


