#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

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
unsigned long long TradingCompany::get<unsigned long long>(string &value, const Field field)
{
    return checkField(value, field).ulonglongValue;
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
    phone_ = get<unsigned long long>(phone, FIELD_PHONE);
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
    passport_ = get<unsigned long long>(passport, FIELD_PASSPORT);
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

unsigned long long TradingCompany::getPassport()
{
    return passport_;
}

unsigned long long TradingCompany::getPhone()
{
    return phone_;
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

void TradingCompany::displayUser(TradingCompany& tradingCompany)
{
    cout << "Вы зашли за " << tradingCompany.getPosition() << "'a. " << endl;
    cout << "Приветствуем вас, "
    << tradingCompany.getSurname() << " "
    << tradingCompany.getName() << " "
    << tradingCompany.getPatronymic() << "!" << endl;
}

void TradingCompany::changePersonalData(TradingCompany& tradingCompany)
{
    cout << ("Изменить свою должность - нажмите 1") << endl;
    cout << ("Изменить свою фамилию - нажмите 2") << endl;
    cout << ("Изменить своё имя - нажмите 3") << endl;
    cout << ("Изменить своё отчество - нажмите 4") << endl;
    cout << ("Изменить свой пол - нажите 5") << endl;
    cout << ("Изменить свою дату рождения - нажмите 6") << endl;
    cout << ("Изменить свой номер паспорта - нажмите 7") << endl;
    cout << ("Изменить свой номер телефона - нажмите 8") << endl;
    cout << ("Изменить свой пароль к доступу - нажмите 9") << endl;
    string input;
    Field field;
    input = (Field)field;
    cin >> input;
    switch(stoi(input))
    {
        case FIELD_POSITION:
            cout << "Текущее значение: " << tradingCompany.getPosition() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setPosition(input);
            break;
        case FIELD_SURNAME:
            cout << "Текущее значение: " << tradingCompany.getSurname() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setSurname(input);
            break;
        case FIELD_NAME:
            cout << "Текущее значение: " << tradingCompany.getName() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setName(input);
            break;
        case FIELD_PATRONYMIC:
            cout << "Текущее значение: " <<  tradingCompany.getPatronymic() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setPatronymic(input);
            break;
        case FIELD_SEX:
            cout << "Текущее значение: " <<  tradingCompany.getSex() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setSex(input);
            break;
        case FIELD_DATE_OF_BIRTH:
            cout << "Текущее значение: " <<  tradingCompany.getDateOfBirth() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setDateOfHiring(input);
            break;
        case FIELD_PASSPORT:
            cout << "Текущее значение: " <<  tradingCompany.getPassport() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setPassport(input);
            break;
        case FIELD_PHONE:
            cout << "Текущее значение: " <<  tradingCompany.getPhone() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setPhone(input);
            break;
        case FIELD_PASSWORD:
            cout << "Текущее значение: " <<  tradingCompany.getPassword() << endl;
            cout << "Введите свое значение: " << endl;
            cin >> input;
            tradingCompany.setPassword(input);
            break;
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
//                toUpperAndToLower(value);
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
//                toUpperAndToLower(value);
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
//                toUpperAndToLower(value);
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
//                toUpperAndToLower(value);
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
//                toUpperAndToLower(value);
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
                type.ulonglongValue = atoi(value.c_str());
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
                type.ulonglongValue = atoi(value.c_str());
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

ostream& operator << (ostream &output, const TradingCompany &tradingCompany)
{
    output << tradingCompany.id_ << " ";
    output << tradingCompany.position_ << " ";
    output << tradingCompany.surname_ << " ";
    output << tradingCompany.name_ << " ";
    output << tradingCompany.patronymic_ << " ";
    output << tradingCompany.sex_ << " ";
    output << tradingCompany.dateOfBirth_ << " ";
    output << tradingCompany.phone_ << " ";
    output << tradingCompany.dateOfHiring_ << " ";
    output << tradingCompany.workingHours_ << " ";
    output << tradingCompany.passport_ << " ";
    output << tradingCompany.salary_ << " ";
    output << tradingCompany.password_;
    return output;
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

//istream& operator >> (istream& stream, TradingCompany& tradingCompany)
//{
//    string parameter;
//    cout << "Начало загрузки данных сотрудника" << endl;
//    stream >> parameter;
//    tradingCompany.id_ = tradingCompany.get<uint>(parameter, FIELD_ID);
//    stream >> parameter;
//    tradingCompany.position_ = tradingCompany.get<string>(parameter, FIELD_POSITION);
//    stream >> parameter;
//    tradingCompany.surname_ = tradingCompany.get<string>(parameter, FIELD_SURNAME);
//    stream >> parameter;
//    tradingCompany.name_ = tradingCompany.get<string>(parameter, FIELD_NAME);
//    stream >> parameter;
//    tradingCompany.patronymic_ = tradingCompany.get<string>(parameter, FIELD_PATRONYMIC);
//    stream >> parameter;
//    tradingCompany.sex_ = tradingCompany.get<string>(parameter, FIELD_SEX);
//    stream >> parameter;
//    tradingCompany.dateOfBirth_ = tradingCompany.get<string>(parameter, FIELD_DATE_OF_BIRTH);
//    stream >> parameter;
//    tradingCompany.passport_ = tradingCompany.get<unsigned long long>(parameter, FIELD_PASSPORT);
//    stream >> parameter;
//    tradingCompany.phone_ = tradingCompany.get<unsigned long long>(parameter, FIELD_PHONE);
//    stream >> parameter;
//    tradingCompany.email_ = tradingCompany.get<string>(parameter, FIELD_EMAIL);
//    stream >> parameter;
//    tradingCompany.dateOfHiring_ = tradingCompany.get<string>(parameter, FIELD_DATE_OF_HIRING);
//    stream >> parameter;
//    tradingCompany.workingHours_ = tradingCompany.get<string>(parameter, FIELD_WORKING_HOURS);
//    stream >> parameter;
//    tradingCompany.salary_ = tradingCompany.get<uint>(parameter, FIELD_SALARY);
//    stream >> parameter;
//    tradingCompany.password_ = tradingCompany.get<string>(parameter, FIELD_PASSWORD);
//    cout << "Конец загрузки данных сотрудника" << endl;
//    cout << "--------------------------------" << endl;
//    return stream;
//}
//trading_company &trading_company::operator = (const trading_company &trading_company, const directors &directors)
//{
//    vector <trading_company> trading_company_vector, *trading_company_pointer_vector, trading_company_for_pointer_to_vector;
//    trading_company_pointer_vector = &trading_company_for_pointer_to_vector;
//    trading_company_for_pointer_to_vector = directors_object.get_reading_data_from_file(directors_location);
//    vector<directors>* directors_vector = reinterpret_cast<vector<directors>* >(trading_company_pointer_vector);
//    return *this;
//}



