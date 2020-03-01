#include <boost/regex.hpp>

#include "TradingCompany.h"
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

void TradingCompany::setPassport(string &passport)
{
    passport_ = get<uint64_t>(passport, FIELD_PASSPORT);
}

void TradingCompany::setSalary(string &salary)
{
    salary_ = get<uint>(salary, FIELD_SALARY);
}

void TradingCompany::setPassword(string &password)
{
    password_ = get<string>(password, FIELD_PASSWORD);
}

uint TradingCompany::getId()
{
    return id_;
}

string TradingCompany::getPosition()
{
    return position_;
}

string TradingCompany::getSurname()
{
    return surname_;
}

string TradingCompany::getName()
{
    return name_;
}

string TradingCompany::getPatronymic()
{
    return patronymic_;
}

string TradingCompany::getSex()
{
    return sex_;
}

string TradingCompany::getDateOfBirth()
{
    return dateOfBirth_;
}

uint64_t TradingCompany::getPassport()
{
    return passport_;
}

uint64_t TradingCompany::getPhone()
{
    return phone_;
}

string TradingCompany::getEmail()
{
    return email_;
}

string TradingCompany::getDateOfHiring()
{
    return dateOfHiring_;
}

string TradingCompany::getWorkingHours()
{
    return workingHours_;
}

uint TradingCompany::getSalary()
{
    return salary_;
}

string TradingCompany::getPassword()
{
    return password_;
}

void TradingCompany::switchCaseParameter(string &parameter, const Field &field)
{
    switch (field)
    {
        case FIELD_ID :
            setId(parameter);
            break;
            
        case FIELD_POSITION :
            setPosition(parameter);
            break;
            
        case FIELD_SURNAME :
            setSurname(parameter);
            break;
            
        case FIELD_NAME :
            setName(parameter);
            break;
            
        case FIELD_PATRONYMIC :
            setPatronymic(parameter);
            break;
            
        case FIELD_SEX :
            setSex(parameter);
            break;
            
        case FIELD_DATE_OF_BIRTH :
            setDateOfBirth(parameter);
            break;
            
        case FIELD_PASSPORT :
            setPassport(parameter);
            break;
            
        case FIELD_PHONE :
            setPhone(parameter);
            break;
            
        case FIELD_EMAIL :
            setEmail(parameter);
            break;
            
        case FIELD_DATE_OF_HIRING :
            setDateOfHiring(parameter);
            break;
            
        case FIELD_WORKING_HOURS :
            setWorkingHours(parameter);
            break;
            
        case FIELD_SALARY :
            setSalary(parameter);
            break;
            
        case FIELD_PASSWORD :
            setPassword(parameter);
            break;
    }
}

void TradingCompany::changeStatusId()
{
    Logger::warning << "Повторяющийся id >> " << id_ << endl;
    fieldStatus_[FIELD_ID] = ST_DUBLICATE;
}

void TradingCompany::changeStatusPassport()
{
    Logger::warning << "Повторяющийся паспорт >> " << passport_ << endl;
    fieldStatus_[FIELD_PASSPORT] = ST_DUBLICATE;
}

void TradingCompany::changeStatusPhone()
{
    Logger::warning << "Повторяющийся телефон >> " << phone_ << endl;
    fieldStatus_[FIELD_PHONE] = ST_DUBLICATE;
}

void TradingCompany::changeStatusPassword(bool isWrite)
{
    if (isWrite)
    {
        Logger::error << "Повторяющийся пароль >> " << password_ << endl;
    }
    fieldStatus_[FIELD_PASSWORD] = ST_DUBLICATE;
}

template <typename T> void TradingCompany::recursion(const Field &field,
                                                     const string &message,
                                                     const T &parameter)
{
    string input;
    if (fieldStatus_[field] != ST_OK)
    {
        auto condition = message.find("(");
        cout << message << parameter << endl;
        cout << "Ввод: ";
        cin >> input;
        switchCaseParameter(input, field);
        recursion(field, "Некорректно введен параметр " + message.substr(condition) + ": ", parameter);
    }
}

void TradingCompany::checkId(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите ID (например, 100) ";
    recursion(FIELD_ID, message, id_);
}

void TradingCompany::checkPosition(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите должность ";
    recursion(FIELD_POSITION, message, position_);
}

void TradingCompany::checkSurname(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите фамилию ";
    recursion(FIELD_SURNAME, message, surname_);
}

void TradingCompany::checkName(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите имя ";
    recursion(FIELD_NAME, message, name_);
}

void TradingCompany::checkPatronymic(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите отчество ";
    recursion(FIELD_PATRONYMIC, message, patronymic_);
}

void TradingCompany::checkSex(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите пол (например, Муж) ";
    recursion(FIELD_SEX, message, sex_);
}

void TradingCompany::checkDateOfBirth(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите дату рождения (например, 16.12.1995) ";
    recursion(FIELD_DATE_OF_BIRTH, message, dateOfBirth_);
}

void TradingCompany::checkPassport(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите номер паспорта (например, 4516561974) ";
    recursion(FIELD_PASSPORT, message, passport_);
}

void TradingCompany::checkPhone(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите номер телефона (например, 9032697963) ";
    recursion(FIELD_PHONE, message, phone_);
}

void TradingCompany::checkEmail(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите почту (например, surname.name.patronymic@tradingcompany.ru) ";
    recursion(FIELD_EMAIL, message, email_);
}

void TradingCompany::checkDateOfHiring(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите дату принятия на работу (например, 16.04.2018) ";
    recursion(FIELD_DATE_OF_BIRTH, message, dateOfHiring_);
}

void TradingCompany::checkWorkingHours(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите время работы (например, Понедельник-Пятница=09:00-18:00) ";
    recursion(FIELD_WORKING_HOURS, message, workingHours_);
}

void TradingCompany::checkSalary(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите зарплату (в рублях) ";
    recursion(FIELD_SALARY, message, salary_);
}

void TradingCompany::checkPassword(const string &warning)
{
    if (!warning.empty())
        cout << warning << endl;
    const string message = "Введите пароль (пароль должен содержать:\n-не менее 6 символов\n"
                                                                     "-хотя бы одну прописную латинскую букву\n"
                                                                     "-хотя бы одну строчную латинскую букву\n"
                                                                     "-хотя бы одну цифру) ";
    recursion(FIELD_PASSWORD, message, password_);
}

void TradingCompany::displayUser()
{
    cout << "Вы зашли за " << getPosition() << "'a. " << endl;
    cout << "Приветствуем вас, "
         << getSurname() << " "
         << getName() << " "
         << getPatronymic() << "!" << endl;
}

void TradingCompany::changePersonalData()
{
    string input;
    while (true)
    {
        cout << "Изменить свою должность - нажмите 1" << endl;
        cout << "Изменить свою фамилию - нажмите 2" << endl;
        cout << "Изменить своё имя - нажмите 3" << endl;
        cout << "Изменить своё отчество - нажмите 4" << endl;
        cout << "Изменить свой пол - нажите 5" << endl;
        cout << "Изменить свою дату рождения - нажмите 6" << endl;
        cout << "Изменить свой номер паспорта - нажмите 7" << endl;
        cout << "Изменить свой номер телефона - нажмите 8" << endl;
        cout << "Изменить свой пароль к доступу - нажмите 9" << endl;
        cout << "Хотите вернуться назад? - введите B: " << endl;
        cout << "Хотите выйти из программы? - введите ESC: " << endl;
        try
        {
            cin >> input;
            toLower(input);
            switch (str(input.c_str()))
            {
                case str("1") :
                    cout << "Текущее значение: " << getPosition() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPosition(input);
                    break;
                case str("2") :
                    cout << "Текущее значение: " << getSurname() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setSurname(input);
                    break;
                case str("3") :
                    cout << "Текущее значение: " << getName() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setName(input);
                    break;
                case str("4") :
                    cout << "Текущее значение: " <<  getPatronymic() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPatronymic(input);
                    break;
                case str("5") :
                    cout << "Текущее значение: " <<  getSex() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setSex(input);
                    break;
                case str("6") :
                    cout << "Текущее значение: " <<  getDateOfBirth() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setDateOfHiring(input);
                    break;
                case str("7") :
                    cout << "Текущее значение: " <<  getPassport() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPassport(input);
                    break;
                case str("8") :
                    cout << "Текущее значение: " <<  getPhone() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPhone(input);
                    break;
                case str("9") :
                    cout << "Текущее значение: " <<  getPassword() << endl;
                    cout << "Введите свое значение: " << endl;
                    cin >> input;
                    setPassword(input);
                    break;
                case str("b") :
                    return;
                case str("esc") :
                    cout << "Вы вышли из программы!" << endl;
                    exit(0);
                default:
                    throw input;
            }
        }
        catch (const string &ex)
        {
            cout << "Вы ввели: " << ex << " - неверная команда! Попробуйте ввести заново: "<< endl;
        }
        catch(...)
        {
            cout << "Неизвестная ошибка!";
            exit(0);
        }
    }
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
                type.uintValue = atoi(value.c_str());
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
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_POSITION :
            {
                toUpperAndToLower(value);
                type.stringValue = value;
                regex regular ("(Бухгалтер|Водитель|Главный_бухгалтер|Главный_юрист-консультант|Грузчик|Директор|Кассир|Логист|"
                               "Менеджер_по_закупкам|Менеджер_по_продажам|Начальник_отдела_закупок|Начальник_склада|Юрист)");
                if (value.empty())
                {
                    Logger::error << "Пустая должность >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорретная должность >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Должность >> " << value << endl;
                    type.status = ST_OK;
                }
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_SURNAME :
            {
                toUpperAndToLower(value);
                type.stringValue = value;
                regex regular ("[А-Яабвгдеёжзийклмнопрстуфхцчшщъыьэюя]+");
                if (value.empty())
                {
                    Logger::error << "Пустая фамилия >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорретная фамилия >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Фамилия >> " << value << endl;
                    type.status = ST_OK;
                }
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_NAME :
            {
                toUpperAndToLower(value);
                type.stringValue = value;
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
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_PATRONYMIC :
            {
                toUpperAndToLower(value);
                type.stringValue = value;
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
                fieldStatus_[field] = type.status;
                return type;
            }
    
            case FIELD_SEX :
            {
                toUpperAndToLower(value);
                type.stringValue = value;
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
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_DATE_OF_BIRTH :
            {
                type.stringValue = value;
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
                    Logger::warning << "Некорретная дата рождения >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Дата рождения >> " << value << endl;
                    type.status = ST_OK;
                }
                fieldStatus_[field] = type.status;
                return type;
            }

            case FIELD_PASSPORT :
            {
                type.uint64Value = strtoul(value.c_str(), NULL, 0);
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
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_PHONE :
            {
                type.uint64Value = strtoul(value.c_str(), NULL, 0);
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
                fieldStatus_[field] = type.status;
                return type;
            }
                
            case FIELD_EMAIL :
            {
                type.stringValue = value;
                regex regular ("^([a-z0-9]+)(\\.)([a-z0-9]+)(\\.)([a-z0-9]+)(@)(tradingcompany)(\\.)(ru)$");
                if (value.empty())
                {
                    Logger::error << "Пустая почта >> " << value << endl;
                    type.status = ST_EMPTY;
                }
                else if (!regex_match(value, regular))
                {
                    Logger::warning << "Некорретная почта >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Почта >> " << value << endl;
                    type.status = ST_OK;
                }
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_DATE_OF_HIRING :
            {
                type.stringValue = value;
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
                    Logger::warning << "Некорретная дата принятия на работу >> " << value << endl;
                    type.status = ST_WRONGDATA;
                }
                else
                {
                    Logger::info << "Дата принятия на работу >> " << value << endl;
                    type.status = ST_OK;
                }
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_WORKING_HOURS :
            {
                type.stringValue = value;
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
                fieldStatus_[field] = type.status;
                return type;
            }
            
            case FIELD_SALARY :
            {
                type.uintValue = atoi(value.c_str());
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
                fieldStatus_[field] = type.status;
                return type;
            }
        
            case FIELD_PASSWORD :
            {
                type.stringValue = value;
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
                fieldStatus_[field] = type.status;
                return type;
            }
                
            default:
                throw (field);
        }
    }
    catch (const string &ex)
    {
        cout << "Неверный uint64_tметр: " << ex << endl;
    }
    catch(const Field &ex)
    {
        cout << "Введен неверный uint64_tметр поля >> " + to_string(ex) << endl;
    }
    catch(...)
    {
        cout << "Неизвестная ошибка!";
    }
    return TradingCompany::empty;
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

void operator >> (const string &line, TradingCompany &tradingCompany)
{
    bool isRecord = false;
    string input;
    Field field;
    
    istringstream is(line);
    while (is >> input)
    {
        string parameter = regex_replace(input, regex("[^A-Za-z]"), "");
        auto found = tradingCompany.parameters.find(parameter);

        if (found != tradingCompany.parameters.end())
        {
            field = found->second;
            is >> input;
            isRecord = true;
        }
        if (isRecord)
        {
            if (*input.begin() != ('\"') && *(input.end() - 1) != ('\"'))
                input.clear();
            else
                input = input.substr(1, input.length() - 2);
            tradingCompany.switchCaseParameter(input, field);
            isRecord = false;
        }
    }
}



