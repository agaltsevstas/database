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

void checkId()
{
    
}

void checkPosition()
{
    
}

void checkSurname()
{
    
}

void checkName()
{
    
}

void checkPatronymic()
{
    
}

void checkSex()
{
    
}

void checkDateOfBirth()
{
    
}

void checkAge()
{
    
}

void checkPhone()
{
    
}

void checkEmail()
{
    
}

void checkDateOfHiring()
{
    
}

void checkWorkingHours()
{
    
}

void checkPassport()
{
    
}

void checkSalary()
{
    
}

void checkPassword()
{
    
}

void TradingCompany::checkData()
{
    for (const auto &[key, value]: fieldStatus_)
    {
        string input;
        if (value != ST_OK)
        {
            switch (key)
            {
                case FIELD_ID :
                    cout << "Измените свой текущий ID " << id_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_POSITION :
                    cout << "Измените свой текущую должность  " << position_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_SURNAME :
                    cout << "Измените свою текущую фамилию  " << surname_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_NAME :
                    cout << "Измените свое текущее имя << " << name_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_PATRONYMIC :
                    cout << "Измените свое текущее отчество << " << patronymic_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_SEX :
                    cout << "Измените свой текущий пол << " << sex_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_DATE_OF_BIRTH :
                    cout << "Измените свою текущую дату рождения << " << dateOfBirth_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_PASSPORT :
                    cout << "Измените свой текущий паспорт << " << passport_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_PHONE :
                    cout << "Измените свой текущий телефон << " << phone_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_EMAIL :
                    cout << "Измените свою текущую почту << " << email_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_DATE_OF_HIRING :
                    cout << "Измените свою текущую дату принятия на работу << " << dateOfHiring_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_WORKING_HOURS :
                    cout << "Измените свои текущие часы работы << " << workingHours_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_SALARY :
                    cout << "Измените свою текущую зарплату << " << salary_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
                case FIELD_PASSWORD :
                    cout << "Измените свой текущий пароль << " << password_ << " на >> " << endl;
                    cin >> input;
                    setId(input);
            }
        }
    }
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
        cout << "Неверный параметр: " << ex << endl;
    }
    catch(const Field &ex)
    {
        cout << "Введен неверный параметр поля >> " + to_string(ex) << endl;
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
    string word;
    Field field;
    
    istringstream is(line);
    while (is >> word)
    {
        string parameter = regex_replace(word, regex("[^A-Za-z]"), "");
        auto found = tradingCompany.parameters.find(parameter);

        if (found != tradingCompany.parameters.end())
        {
            field = found->second;
            is >> word;
            isRecord = true;
        }
        if (isRecord)
        {
            if (*word.begin() != ('\"') && *(word.end() - 1) != ('\"'))
                word.clear();
            else
                word = word.substr(1, word.length() - 2);
            switch (field)
            {
                case FIELD_ID :
                    tradingCompany.setId(word);
                    break;
                    
                case FIELD_POSITION :
                    tradingCompany.setPosition(word);
                    break;
                    
                case FIELD_SURNAME :
                    tradingCompany.setSurname(word);
                    break;
                    
                case FIELD_NAME :
                    tradingCompany.setName(word);
                    break;
                    
                case FIELD_PATRONYMIC :
                    tradingCompany.setPatronymic(word);
                    break;
                    
                case FIELD_SEX :
                    tradingCompany.setSex(word);
                    break;
                    
                case FIELD_DATE_OF_BIRTH :
                    tradingCompany.setDateOfBirth(word);
                    break;
                    
                case FIELD_PASSPORT :
                    tradingCompany.setPassport(word);
                    break;
                    
                case FIELD_PHONE :
                    tradingCompany.setPhone(word);
                    break;
                    
                case FIELD_EMAIL :
                    tradingCompany.setEmail(word);
                    break;
                    
                case FIELD_DATE_OF_HIRING :
                    tradingCompany.setDateOfHiring(word);
                    break;
                    
                case FIELD_WORKING_HOURS :
                    tradingCompany.setWorkingHours(word);
                    break;
                    
                case FIELD_SALARY :
                    tradingCompany.setSalary(word);
                    break;
                    
                case FIELD_PASSWORD :
                    tradingCompany.setPassword(word);
                    break;
            }
            isRecord = false;
        }
    }
}



