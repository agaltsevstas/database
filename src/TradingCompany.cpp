#include <boost/regex.hpp>

#include "TradingCompany.h"
#include "Logger.h"
#include "Utils.h"

using namespace boost;
using namespace utils;

template<>
uint TradingCompany::get<uint>(string &value, const Field field)
{
    return checkField(value, field).uintValue;
}

template<>
uint64_t TradingCompany::get<uint64_t>(string &value, const Field field)
{
    return checkField(value, field).uint64Value;
}

template<>
string TradingCompany::get<string>(string &value, const Field field)
{
    return checkField(value, field).stringValue;
}

void TradingCompany::setId(string &id)
{
    id_ = get<uint>(id, FIELD_ID);
}

void TradingCompany::setPosition(string &position)
{
    position_ = get<string>(position, FIELD_POSITION);
}

void TradingCompany::setSurname(string &surname)
{
    surname_ = get<string>(surname, FIELD_SURNAME);
}

void TradingCompany::setName(string &name)
{
    name_ = get<string>(name, FIELD_NAME);
}

void TradingCompany::setPatronymic(string &patronymic)
{
    patronymic_ = get<string>(patronymic, FIELD_PATRONYMIC);
}

void TradingCompany::setSex(string &sex)
{
    sex_ = get<string>(sex, FIELD_SEX);
}

void TradingCompany::setDateOfBirth(string &dateOfBirth)
{
    dateOfBirth_ = get<string>(dateOfBirth, FIELD_DATE_OF_BIRTH);
}

void TradingCompany::setPassport(string &passport)
{
    passport_ = get<uint64_t>(passport, FIELD_PASSPORT);
}

void TradingCompany::setPhone(string &phone)
{
    phone_ = get<uint64_t>(phone, FIELD_PHONE);
}

void TradingCompany::setEmail(string &email)
{
    email_ = get<string>(email, FIELD_EMAIL);
}

void TradingCompany::setDateOfHiring(string &dateOfHiring)
{
    dateOfHiring_ = get<string>(dateOfHiring, FIELD_DATE_OF_HIRING);
}

void TradingCompany::setWorkingHours(string &workingHours)
{
    workingHours_ = get<string>(workingHours, FIELD_WORKING_HOURS);
}

void TradingCompany::setSalary(string &salary)
{
    salary_ = get<uint>(salary, FIELD_SALARY);
}

void TradingCompany::setPassword(string &password)
{
    password_ = get<string>(password, FIELD_PASSWORD);
}

uint TradingCompany::getId() const
{
    return id_;
}

string TradingCompany::getPosition() const
{
    return position_;
}

string TradingCompany::getSurname() const
{
    return surname_;
}

string TradingCompany::getName() const
{
    return name_;
}

string TradingCompany::getPatronymic() const
{
    return patronymic_;
}

string TradingCompany::getSex() const
{
    return sex_;
}

string TradingCompany::getDateOfBirth() const
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

string TradingCompany::getEmail() const
{
    return email_;
}

string TradingCompany::getDateOfHiring() const
{
    return dateOfHiring_;
}

string TradingCompany::getWorkingHours() const
{
    return workingHours_;
}

uint TradingCompany::getSalary() const
{
    return salary_;
}

string TradingCompany::getPassword() const
{
    return password_;
}

void TradingCompany::changeStatusId()
{
    Logger::warning << "Повторяющийся id >> " << id_ << endl;
    id_ = rand();
    fieldStatus_[FIELD_ID] = ST_DUBLICATE;
}

void TradingCompany::changeStatusPassport()
{
    Logger::warning << "Повторяющийся паспорт >> " << passport_ << endl;
    passport_ = rand();
    fieldStatus_[FIELD_PASSPORT] = ST_DUBLICATE;
}

void TradingCompany::changeStatusPhone()
{
    Logger::warning << "Повторяющийся телефон >> " << phone_ << endl;
    phone_ = rand();
    fieldStatus_[FIELD_PHONE] = ST_DUBLICATE;
}

void TradingCompany::changeStatusEmail()
{
    Logger::warning << "Повторяющаяся почта >> " << email_ << endl;
    email_ += to_string(rand());
    fieldStatus_[FIELD_EMAIL] = ST_DUBLICATE;
}

void TradingCompany::changeStatusPassword(bool isWrite)
{
    if (isWrite)
    {
        Logger::error << "Повторяющийся пароль >> " << password_ << endl;
    }
    fieldStatus_[FIELD_PASSWORD] = ST_DUBLICATE;
}

bool TradingCompany::hasDublicatePassword()
{
    return fieldStatus_[FIELD_PASSWORD] == ST_DUBLICATE;
}

void TradingCompany::recursion(const Field &field,
                               std::function<void(TradingCompany&, string&)> setParameter,
                               const string &message)
{
    string input;
    if (fieldStatus_[field] != ST_OK)
    {
        cout << message << endl;
        string newMessage;
        auto condition = message.find("ведите");
        if (condition != string::npos)
        {
            newMessage = message.substr(condition);
        }
        cout << "Ввод: " << endl;
        cin >> input;
        setParameter(*this, input);
        recursion(field, setParameter, "Некорректно введен параметр, в" + newMessage);
    }
}

void TradingCompany::checkId(const string &warning)
{
    const string message = "Введите ID (например, 100)";
    recursion(FIELD_ID, &TradingCompany::setId, warning + message);
}

void TradingCompany::checkPosition(const string &warning)
{
    const string message = "Введите должность";
    recursion(FIELD_POSITION, &TradingCompany::setPosition, warning + message);
}

void TradingCompany::checkSurname(const string &warning)
{
    const string message = "Введите фамилию";
    recursion(FIELD_SURNAME, &TradingCompany::setSurname, warning + message);
}

void TradingCompany::checkName(const string &warning)
{
    const string message = "Введите имя";
    recursion(FIELD_NAME, &TradingCompany::setName, warning + message);
}

void TradingCompany::checkPatronymic(const string &warning)
{
    const string message = "Введите отчество";
    recursion(FIELD_PATRONYMIC, &TradingCompany::setPatronymic, warning + message);
}

void TradingCompany::checkSex(const string &warning)
{
    const string message = "Введите пол (например, Муж)";
    recursion(FIELD_SEX, &TradingCompany::setSex, warning + message);
}

void TradingCompany::checkDateOfBirth(const string &warning)
{
    const string message = "Введите дату рождения (например, 16.12.1995)";
    recursion(FIELD_DATE_OF_BIRTH, &TradingCompany::setDateOfBirth, warning + message);
}

void TradingCompany::checkPassport(const string &warning)
{
    const string message = "Введите номер паспорта (например, 4516561974)";
    recursion(FIELD_PASSPORT, &TradingCompany::setPassport, warning + message);
}

void TradingCompany::checkPhone(const string &warning)
{
    const string message = "Введите номер телефона (например, 9032697963)";
    recursion(FIELD_PHONE, &TradingCompany::setPhone, warning + message);
}

void TradingCompany::checkEmail(const string &warning)
{
    const string message = "Введите почту (например, surname.name.patronymic@tradingcompany.ru)";
    recursion(FIELD_EMAIL, &TradingCompany::setEmail, warning + message);
}

void TradingCompany::checkDateOfHiring(const string &warning)
{
    const string message = "Введите дату принятия на работу (например, 16.04.2018)";
    recursion(FIELD_DATE_OF_HIRING, &TradingCompany::setDateOfHiring, warning + message);
}

void TradingCompany::checkWorkingHours(const string &warning)
{
    const string message = "Введите время работы (например, Понедельник-Пятница=09:00-18:00)";
    recursion(FIELD_WORKING_HOURS, &TradingCompany::setWorkingHours, warning + message);
}

void TradingCompany::checkSalary(const string &warning)
{
    const string message = "Введите зарплату (в рублях)";
    recursion(FIELD_SALARY, &TradingCompany::setSalary, warning + message);
}

void TradingCompany::checkPassword(const string &warning)
{
    const string message = "Введите новый пароль (пароль должен содержать:\n-не менее 6 символов\n"
                           "-хотя бы одну прописную латинскую букву\n"
                           "-хотя бы одну строчную латинскую букву\n"
                           "-хотя бы одну цифру)";
    recursion(FIELD_PASSWORD, &TradingCompany::setPassword, warning + message);
}

void TradingCompany::displayUser()
{
    Logger::info << "Вход в аккаунт >> " << getPosition() << "'a. " << endl;
    Logger::info << getSurname() << " "
                 << getName() << " "
                 << getPatronymic() << endl;
    cout << "Вы зашли за " << getPosition() << "'a. " << endl;
    cout << "Приветствуем вас, "
         << getSurname() << " "
         << getName() << " "
         << getPatronymic() << "!" << endl;
}

const TradingCompany::Type TradingCompany::checkField(string &value, const Field &field)
{
    Type type;
    
    try
    {
        switch (field)
        {
            case FIELD_ID :
            {
                regex regular ("^[0-9]{1,4}$");
                if (value.empty())
                {
                    Logger::error << "Пустой ID >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректный ID >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "ID >> " << value << endl;
                    type.status = ST_OK;
                }
                type.uintValue = atoi(value.c_str());
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_POSITION :
            {
                toUpperAndToLower(value);
                regex regular ("(Бухгалтер|Водитель|Главный_бухгалтер|Главный_юрист-консультант|Грузчик|Директор|Кассир|Логист|"
                               "Менеджер_по_закупкам|Менеджер_по_продажам|Начальник_отдела_закупок|Начальник_склада|Юрист)");
                if (value.empty())
                {
                    Logger::error << "Пустая должность >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректная должность >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Должность >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_SURNAME :
            {
                toUpperAndToLower(value);
                regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    Logger::error << "Пустая фамилия >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректная фамилия >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Фамилия >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_NAME :
            {
                toUpperAndToLower(value);
                regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    Logger::info << "Пустое имя >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорретное имя >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Имя >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_PATRONYMIC :
            {
                toUpperAndToLower(value);
                regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    Logger::error << "Пустое отчество >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорретное отчество >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Отчество >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
    
            case FIELD_SEX :
            {
                toUpperAndToLower(value);
                regex regular ("^(Муж|Жен)$");
                if (value.empty())
                {
                    Logger::error << "Пустой пол >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректный пол >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Пол >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_DATE_OF_BIRTH :
            {
                vector<string> data = utils::splitString(date(), " .-");
                vector<string> dateOfBirth = utils::splitString(value, " .-");
                auto age = findAge(data, dateOfBirth);
                uint year = age[0];
                uint month = age[1];
                uint day = age[2];
                regex regular ("^(((0[1-9]|[12][0-9]|30)[-/.]?(0[13-9]|1[012])|31[-/.]?(0[13578]|1[02])|(0[1-9]|"
                               "1[0-9]|2[0-8])[-/.]?02)[-/.]?[0-9]{4}|29[-/.]?02[-/.]?([0-9]{2}(([2468][048]|"
                               "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (value.empty())
                {
                    Logger::error << "Пустая дата рождения >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (year < 18)
                {
                    Logger::warning << "Неудовлетворительный возраст >> " << "Лет: " << year << "Месяцев: " << month << "Дней: " << day << endl;
                    type.status = ST_WRONGDATA;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректная дата рождения >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Дата рождения >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_PASSPORT :
            {
                regex regular ("^[0-9]{10}$");
                regex_match(value, regular);
                if (value.empty())
                {
                    Logger::error << "Пустой паспорт >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректный паспорт >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Паспорт >> " << value << endl;
                    type.status = ST_OK;
                }
                type.uint64Value = strtoul(value.c_str(), NULL, 0);
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_PHONE :
            {
                regex regular ("^[0-9]{10}$");
                regex_match(value, regular);
                if (value.empty())
                {
                    Logger::error << "Пустой телефон >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректный телефон >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Телефон >> " << value << endl;
                    type.status = ST_OK;
                }
                type.uint64Value = strtoul(value.c_str(), NULL, 0);
                fieldStatus_[field] = type.status;
                return type;
            }
                
            case FIELD_EMAIL :
            {
                string email = createEmail(vector<string>{surname_, name_, patronymic_});
                regex regular ("^([a-z0-9]+)(\\.)([a-z0-9]+)(\\.)([a-z0-9]+)(@)(tradingcompany)(\\.)(ru)$");
                if (regex_match(email, regular))
                {
                    value = email;
                    Logger::info << "Почта >> " << value << endl;
                    type.status = ST_OK;
                }
                else if (value.empty())
                {
                    Logger::error << "Пустая почта >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректная почта >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Почта >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_DATE_OF_HIRING :
            {
                regex regular ("^(((0[1-9]|[12][0-9]|30)[-/.]?(0[13-9]|1[012])|31[-/.]?(0[13578]|1[02])|(0[1-9]|"
                               "1[0-9]|2[0-8])[-/.]?02)[-/.]?[0-9]{4}|29[-/.]?02[-/.]?([0-9]{2}(([2468][048]|"
                               "[02468][48])|[13579][26])|([13579][26]|[02468][048]|0[0-9]|1[0-6])00))$");
                if (value.empty())
                {
                    Logger::error << "Пустая дата принятия на работу >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректная дата принятия на работу >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Дата принятия на работу >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_WORKING_HOURS :
            {
                regex regular ("(((((Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье),*)+)|"
                               "(Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье)-"
                               "(Понедельник|Вторник|Среда|Четверг|Пятница|Суббота|Воскресенье))="
                               "([0-1]?[0-9]|[2][0-3]]):([0-5][0-9])-([0-1]?[0-9]|[2][0-3]):([0-5][0-9]);*)+");
                if (value.empty())
                {
                    Logger::error << "Пустые часы работы >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректные часы работы >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Часы работы >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_SALARY :
            {
                regex regular ("[0-9]+");
                if (value.empty())
                {
                    Logger::error << "Пустая зарплата >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректная зарплата >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Зарплата >> " << value << endl;
                    type.status = ST_OK;
                }
                type.uintValue = atoi(value.c_str());
                fieldStatus_[field] = type.status;
                return type;
            }
        
            case FIELD_PASSWORD :
            {
                regex regular ("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{6,}");
                if (value.empty())
                {
                    Logger::error << "Пустой пароль >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорректный пароль >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Пароль >> " << value << endl;
                    type.status = ST_OK;
                }
                type.stringValue = value;
                fieldStatus_[field] = type.status;
                return type;
            }
                
            default:
                throw field;
        }
    }
    catch (const string &exception)
    {
        Logger::error << "Невернное значение >> " << exception << endl;
    }
    catch(const Field &field)
    {
        Logger::error << "Неверный параметр поля >> " + to_string(field) << endl;
    }
    catch(const std::exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << endl;
    }
    catch(...)
    {
        Logger::error << "Неизвестная ошибка!";
    }
    return TradingCompany::empty;
}

void operator >> (const string &line, TradingCompany &tradingCompany)
{
    string input;
    Field field;
    
    istringstream is(line);
    while (is >> input)
    {
        string parameter = regex_replace(input, regex("[^A-Za-z]"), "");
        auto found = tradingCompany.parameters_.find(parameter);
        
        if (found != tradingCompany.parameters_.end())
        {
            auto setParameter = found->second;
            is >> input;
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
}

ostream& operator << (ostream &out, const TradingCompany &tradingCompany)
{
    out << tradingCompany.id_ << " ";
    out << tradingCompany.position_ << " ";
    out << tradingCompany.surname_ << " ";
    out << tradingCompany.name_ << " ";
    out << tradingCompany.patronymic_ << " ";
    out << tradingCompany.sex_ << " ";
    out << tradingCompany.dateOfBirth_ << " ";
    out << tradingCompany.phone_ << " ";
    out << tradingCompany.dateOfHiring_ << " ";
    out << tradingCompany.workingHours_ << " ";
    out << tradingCompany.passport_ << " ";
    out << tradingCompany.salary_ << " ";
    out << tradingCompany.password_;
    return out;
}

bool operator == (const TradingCompany &first, const TradingCompany &second)
{
    return (first.passport_ == second.passport_) &&
           (first.password_ == second.password_);
}



