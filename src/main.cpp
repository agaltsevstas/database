#include "TradingCompany.h"
#include "Director.h"
#include "ChiefAccountant.h"
#include "ChiefLegalCounsel.h"
#include "HeadOfProcurement.h"
#include "HeadOfWarehouse.h"
#include "SalesManager.h"
#include "Cashier.h"
#include "Accountant.h"
#include "Logistician.h"
#include "Lawyer.h"
#include "PurchasingManager.h"
#include "Stevedore.h"
#include "Driver.h"
#include "Utils.h"

using namespace utils;

static string directorPath = "director.txt";
static string chiefAccountantPath = "chief_accountant.txt";
static string chiefLegalCounselPath = "chief_legal_counsel.txt";
static string headOfProcurementPath = "head_of_procurement.txt";
static string headOfWarehousePath = "head_of_warehouse.txt";
static string salesManagerPath = "sales_manager.txt";
static string cashierPath = "cashier.txt";
static string accountantPath = "accountant.txt";
static string logisticianPath = "logistician.txt";
static string lawyerPath = "lawyer.txt";
static string purchasingManagerPath = "purchasing_manager.txt";
static string stevedorePath = "stevedore.txt";
static string driverPath = "driver.txt";
static string dataPath = "data";

typedef union
{
    class Director;
    class ChiefAccountant;
    class ChiefLegalCounsel;
    class HeadOfProcurement;
    class HeadOfWarehouse;
    class SalesManager;
    class Cashier;
    class Accountant;
    class Logistician;
    class Lawyer;
    class PurchasingManager;
    class Stevedore;
    class Driver;
} RetType;


//void reading_data_from_file(string directors_location, fstream directors_file, directors directors_object, vector <directors> directors_vector)
//{
//    directors_file.open(directors_location, ios::in);
//    if (directors_file.is_open())
//    {
//        do
//        {
//            directors_file >> directors_object;
//            directors_vector.push_back(directors_object);
//            if (directors_file.eof()) break;
//        } while(!directors_file.eof());
//        directors_file.clear();
//        directors_file.close();
//    }
//}
//void writing_data_in_file()
//{
//    vector <directors>::iterator iter;
//    directors_file.open(directors_location, ios::out);
//    if (directors_file.is_open())
//    {
//        for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//        {
//            directors_file << *iter;
//            cout << *iter << endl;
//        }
//        directors_file.clear();
//        directors_file.close();
//    }
//}

int main()      
{
    setlocale(LC_ALL,"ru_RU.UTF-8");
    Logger::createInstance();

    Director director;
    ChiefAccountant chiefAccountant;
    ChiefLegalCounsel chiefLegalCounsel;
    HeadOfProcurement headOfProcurement;
    HeadOfWarehouse headOfWarehouse;
    SalesManager salesManager;
    Cashier cashier;
    Accountant accountant;
    Logistician logistician;
    Lawyer lawyer;
    PurchasingManager purchasingManager;
    Stevedore stevedore;
    Driver driver;
    
    Data &data = Data::getInstance();
    data.getReadingDataFromFile(director, dataPath + "/" + directorPath);
    data.getReadingDataFromFile(chiefAccountant, dataPath + "/" + chiefAccountantPath);
    data.getReadingDataFromFile(chiefLegalCounsel, dataPath + "/" + chiefLegalCounselPath);
    data.getReadingDataFromFile(headOfProcurement, dataPath + "/" + headOfProcurementPath);
    data.getReadingDataFromFile(headOfWarehouse, dataPath + "/" + headOfWarehousePath);
    data.getReadingDataFromFile(salesManager, dataPath + "/" + salesManagerPath);
    data.getReadingDataFromFile(cashier, dataPath + "/" + cashierPath);
    data.getReadingDataFromFile(accountant, dataPath + "/" + accountantPath);
    data.getReadingDataFromFile(logistician, dataPath + "/" + logisticianPath);
    data.getReadingDataFromFile(lawyer, dataPath + "/" + lawyerPath);
    data.getReadingDataFromFile(purchasingManager, dataPath + "/" + purchasingManagerPath);
    data.getReadingDataFromFile(stevedore, dataPath + "/" + stevedorePath);
    data.getReadingDataFromFile(driver, dataPath + "/" + driverPath);
    
    shared_ptr<Director> directorPtr;
    shared_ptr<ChiefAccountant> chiefAccountantPtr;
    shared_ptr<ChiefLegalCounsel> chiefLegalCounselPtr;
    shared_ptr<HeadOfProcurement> headOfProcurementPtr;
    shared_ptr<HeadOfWarehouse> headOfWarehousePtr;
    shared_ptr<SalesManager> salesManagerPtr;
    shared_ptr<Cashier> cashierPtr;
    shared_ptr<Accountant> accountantPtr;
    shared_ptr<Logistician> logisticianPtr;
    shared_ptr<PurchasingManager> purchasingManagerPtr;
    shared_ptr<Stevedore> stevedorePtr;
    shared_ptr<Lawyer> lawyerPtr;
    shared_ptr<Driver> driverPtr;
    
    vector <shared_ptr<TradingCompany>>::iterator iter;
    Field input_fields;
    string input;
    unsigned int input_int = 0;
//    vector<trading_company*> List; // если нет родительского класса vector<void*> List;
//    List.push_back(new directors);
//    trading_company *p = List[0];
//    directors *t1 = nullptr;
//    t1 = dynamic_cast<directors*>(p));
    cout << ("Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: ") << endl;
    cin >> input;
    while (true)
    {
        try
        {
            for (const auto &tradingCompany: data.getObject())
            {
                if (input == tradingCompany->getPassword())
                {
                    if ((directorPtr = dynamic_pointer_cast<Director>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*directorPtr);

    //                    trading_company::change_personal_data(*directors_pointer);
                        Director::functionalDirector(*directorPtr);
                    }
                    if ((chiefAccountantPtr = dynamic_pointer_cast<ChiefAccountant>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*chiefAccountantPtr);
    //                    trading_company::change_personal_data(*chief_accountant_pointer);
                    }
                    if ((chiefLegalCounselPtr = dynamic_pointer_cast<ChiefLegalCounsel>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*chiefLegalCounselPtr);
    //                    trading_company::change_personal_data(*chief_legal_counsel_pointer);
                    }
                    if ((headOfProcurementPtr = dynamic_pointer_cast<HeadOfProcurement>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*headOfProcurementPtr);
    //                    trading_company::change_personal_data(*head_of_procurement_pointer);
                    }
                    if ((headOfWarehousePtr = dynamic_pointer_cast<HeadOfWarehouse>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*headOfWarehousePtr);
    //                    trading_company::change_personal_data(*head_of_warehouses_pointer);
                    }
                    if ((salesManagerPtr = dynamic_pointer_cast<SalesManager>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*salesManagerPtr);
    //                    trading_company::change_personal_data(*sales_managers_pointer);
                    }
                    if ((cashierPtr = dynamic_pointer_cast<Cashier>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*cashierPtr);
    //                    trading_company::change_personal_data(*cashier_pointer);
                    }
                    if ((accountantPtr = dynamic_pointer_cast<Accountant>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*accountantPtr);
    //                    trading_company::change_personal_data(*accountants_pointer);
                    }
                    if ((logisticianPtr = dynamic_pointer_cast<Logistician>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*logisticianPtr);
    //                    trading_company::change_personal_data(*logisticians_pointer);
                    }
                    if ((lawyerPtr = dynamic_pointer_cast<Lawyer>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*lawyerPtr);
    //                    trading_company::change_personal_data(*lawyer_pointer);
                    }
                    if ((purchasingManagerPtr = dynamic_pointer_cast<PurchasingManager>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*purchasingManagerPtr);
    //                    trading_company::change_personal_data(*purchasing_managers_pointer);
                    }
                    if ((stevedorePtr = dynamic_pointer_cast<Stevedore>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*stevedorePtr);
    //                    trading_company::change_personal_data(*stevedores_pointer);
                    }
                    if ((driverPtr = dynamic_pointer_cast<Driver>(tradingCompany)))
                    {
                        TradingCompany::displayUser(*driverPtr);
    //                    trading_company::change_personal_data(*drivers_pointer);
                    }
                    break;
                }
            }
            toLower(input);
            if(input == "esc")
            {
                cout << "Вы вышли из программы!" << endl;
                exit(0);
            }
            else
                throw input;
        }
        catch (const string &ex)
        {
            cout << "Вы ввели: " << ex << " - неверный пароль! Попробуйте ввести заново или закончите выполнение программы, введя ESC: "<< endl;
            cin >> input;
        }
    }
tryAgain_menu:
    cout << ("Хотите изменить данные?") << endl;
    cout << ("1 - Вывести значение на экран") << endl;
    cout << ("1 - Изменить личные данные") << endl;
    cout << ("2 - Добавить нового сотрудника") << endl;
    cout << ("3 - Изменить данные сотрудника") << endl;
    cout << ("4 - Выйти в главное меню") << endl;
    input_int = static_cast<Field>(input_fields);
    cin >> input_int;
    switch (input_int)
    {
        case FIELD_ID:
        {
//            cout << *abstract_object << endl;
            cout << "Хотите вернуться назад? - введите B: " << endl;
            cout << "Хотите выйти из программы? - введите ESC: " << endl;
            while(true)
            {
                try
                {
                    cin >> input;
                    if(input == "B" || input == "b")
                    {
                        goto tryAgain_menu;
                    }
                    else if(input == "ESC" || input == "esc")
                    {
                    }
                    else throw input;
                }
                catch(const string &ex)
                {
                    cout << "Вы ввели: " << ex << " - неверная команда! Попробуйте ввести заново: "<< endl;
                }
            }
        }
        case FIELD_POSITION:
        {
//            trading_company_object = trading_company_vector.at(index);
            for(iter = data.getObject().begin(); iter != data.getObject().end(); iter++)
                cout << *iter << endl;
            break;
        }
//        case surname:
//        {
//            cout << ("Введите ID сотрудника") << endl;
//            cin >> input_int;
//            directors_object.set_id(input_int);
//            cout << ("Введите должность сотрудника") << endl;
//            cin >> input_string;
//            directors_object.set_position(input_string);
//            cout << ("Введите фамилию сотрудника") << endl;
//            cin >> input_string;
//            directors_object.set_surname(input_string);
//            cout << ("Введите имя сотрудника") << endl;
//            cin >> input_string;
//            directors_object.set_name(input_string);
//            cout << ("Введите отчество сотрудника") << endl;
//            cin >> input_string;
//            directors_object.set_patronymic(input_string);
//            cout << ("Введите пол сотрудника (например, Муж)") << endl;
//            cin >> input_string;
//            directors_object.set_sex(input_string);
//            cout << ("Введите дату рождения сотрудника (например, 16.12.1995)") << endl;
//            cin >> input_string;
//            directors_object.set_date_of_birth(input_string);
//            cout << ("Введите номер паспорта сотрудника (например, 4516561974)") << endl;
//            cin >> input_int_numbers;
//            directors_object.set_pasport(input_int_numbers);
//            cout << ("Введите номер телефона сотрудника (например, 9032697963)") << endl;
//            cin >> input_int_numbers;
//            directors_object.set_phone(input_int_numbers);
//            cout << ("Введите дату принятия сотрудника (например 16.04.2018)") << endl;
//            cin >> input_string;
//            directors_object.set_date_of_hiring(input_string);
//            cout << ("Введите время работы сотрудника (например, 09:00-18:00)") << endl;
//            cin >> input_string;
//            directors_object.set_working_hours(input_string);
//            cout << ("Введите зарплату сотрудника (в рублях)") << endl;
//            cin >> input_int;
//            directors_object.set_salary(input_int);
//            cout << ("Введите пароль к доступу сотрудника") << endl;
//            cin >> input_string;
//            directors_object.set_password(input_string);
//            directors_vector.push_back(directors_object);
//            directors_vector.insert(directors_vector.begin(), directors_object);
//            directors_file << endl;
//            directors_file << directors_object;
//            break;
//        }
//        case name: {
//            cout << ("Введите номер сотрудника, чтобы изменить данные (смотри таблицу)") << endl;
//            for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//                cout << *iter << endl;
//            cout << endl;
//            cout << ("Введите номер сотрудника: ") << endl;
//            cin >> input_int;
//            cout << directors_vector.at(input_int) << endl;
//            cout << endl;
//            cout << ("Изменить ID сотрудника - нажмите 1") << endl;
//            cout << ("Изменить должность сотрудника - нажмите 2") << endl;
//            cout << ("Изменить фамилию сотрудника - нажмите 3") << endl;
//            cout << ("Изменить имя сотрудника - нажмите 4") << endl;
//            cout << ("Изменить отчество сотрудника - нажмите 5") << endl;
//            cout << ("Изменить пол сотрудника - нажите 6") << endl;
//            cout << ("Изменить дату рождения сотрудника - нажмите 7") << endl;
//            cout << ("Изменить номер паспорта сотрудника - нажмите 8") << endl;
//            cout << ("Изменить номер телефона сотрудника - нажмите 9") << endl;
//            cout << ("Изменить дату принятия сотрудника - нажмите 10") << endl;
//            cout << ("Изменить время работы сотрудника - нажмите 11") << endl;
//            cout << ("Изменить зарплату сотрудника - нажмите 12") << endl;
//            cout << ("Изменить пароль к доступу сотрудника - нажмите 13") << endl;
//            input_int_numbers = (trading_company_fields)input_trading_company_fields;
//            cin >> input_int_numbers;
//            switch(input_int_numbers) {
//                case field_id:
//                    cout << directors_vector[input_int].get_id() << endl;
//                    cin >> input_int;
//                    directors_object.set_id(input_int);
//                case field_position:
//                    cout << directors_vector[input_int].get_position() << endl;
//                    cin >> input_string;
//                    directors_object.set_position(input_string);
//                case field_surname:
//                    cout << directors_vector[input_int].get_surname() << endl;
//                    cin >> input_string;
//                    directors_object.set_surname(input_string);
//                case field_name:
//                    cout << directors_vector[input_int].get_name() << endl;
//                    cin >> input_string;
//                    directors_object.set_name(input_string);
//                case field_patronymic:
//                    cout << directors_vector[input_int].get_patronymic() << endl;
//                    cin >> input_string;
//                    directors_object.set_patronymic(input_string);
//                case field_sex:
//                    cout << directors_vector[input_int].get_sex() << endl;
//                    cin >> input_string;
//                    directors_object.set_sex(input_string);
//                case date_of_birth:
//                    cout << directors_vector[input_int].get_date_of_birth() << endl;
//                    cin >> input_string;
//                    directors_object.set_date_of_hiring(input_string);
//                case field_pasport:
//                    cout << directors_vector[input_int].get_pasport() << endl;
//                    cin >> input_int_numbers;
//                    directors_object.set_pasport(input_int_numbers);
//                case field_phone:
//                    cout << directors_vector[input_int].get_phone() << endl;
//                    cin >> input_int_numbers;
//                    directors_object.set_phone(input_int_numbers);
//                case field_date_of_hiring:
//                    cout << directors_vector[input_int].get_date_of_hiring() << endl;
//                    cin >> input_string;
//                    directors_object.set_date_of_hiring(input_string);
//                case field_working_hours:
//                    cout << directors_vector[input_int].get_working_hours() << endl;
//                    cin >> input_string;
//                    directors_object.set_working_hours(input_string);
//                case field_salary:
//                    cout << directors_vector[input_int].get_salary() << endl;
//                    cin >> input_int;
//                    directors_object.set_salary(input_int);
//                case field_password:
//                    cout << directors_vector[input_int].get_password() << endl;
//                    cin >> input_string;
//                    directors_object.set_password(input_string);
////                        writing_data_in_file();
//            }
//        }
        default:
            exit(0);
            break;
    }
    
    
//        trading_company_vector.clear();
//
//    vector <directors>::iterator iter;
//    trading_company_fileds input_trading_company_fileds;
//    string input_string;
//    unsigned int input_int = 0;
//    long long input_int_numbers = 0;
//    directors_file.open(directors_location, ios::in);
//    if (directors_file.is_open())
//    {
//        do
//        {
//            directors_file >> directors_object;
//            directors_vector.push_back(directors_object);
//            if (directors_file.eof()) break;
//        } while(!directors_file.eof());
//        directors_file.clear();
//        directors_file.close();
//        directors_file.open(directors_location, ios::app);
//        cout << ("Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: ") << endl;
//        cin >> input_string;
//    tryAgain_password:
//        if(input_string == "esc" || input_string == "ESC")
//            exit(0);
//        bool flag = false;
//        for (int index = 0; index != directors_vector.size(); index++)
//        {
//            if (input_string == directors_vector[index].get_password())
//            {
//                cout << "Вы зашли за " << directors_vector[index].get_password() << "'a. " << endl;
//                cout << "Приветствуем вас, " << directors_vector[index].get_surname() << " "
//                << directors_vector[index].get_name() << " "
//                << directors_vector[index].get_patronymic() << "!" << endl;
//                flag = true;
//                break;
//            }
//        }
//        if (flag == false)
//        {
//            cout << "Неправильный пароль! Введите заново или закончите выполнение программы, нажав ESC: ";
//            cin >> input_string;
//            goto tryAgain_password;
//        }
//    tryAgain_menu:
//        cout << ("Хотите изменить данные?") << endl;
//        cout << ("1 - Изменить личные данные") << endl;
//        cout << ("1 - Вывести значение на экран") << endl;
//        cout << ("2 - Добавить нового сотрудника") << endl;
//        cout << ("3 - Изменить данные сотрудника") << endl;
//        input_int = (trading_company_fileds)input_trading_company_fileds;
//        cin >> input_int;
//        switch (input_int)
//        {
//            case trading_company_fileds_position:
//            {
//                for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//                    cout << *iter << endl;
//                break;
//            }
//            case trading_company_fileds_surname:
//            {
//                cout << ("Введите ID сотрудника") << endl;
//                cin >> input_int;
//                directors_object.set_id(input_int);
//                cout << ("Введите должность сотрудника") << endl;
//                cin >> input_string;
//                directors_object.set_position(input_string);
//                cout << ("Введите фамилию сотрудника") << endl;
//                cin >> input_string;
//                directors_object.set_surname(input_string);
//                cout << ("Введите имя сотрудника") << endl;
//                cin >> input_string;
//                directors_object.set_name(input_string);
//                cout << ("Введите отчество сотрудника") << endl;
//                cin >> input_string;
//                directors_object.set_patronymic(input_string);
//                cout << ("Введите пол сотрудника (например, Муж)") << endl;
//                cin >> input_string;
//                directors_object.set_sex(input_string);
//                cout << ("Введите дату рождения сотрудника (например, 16.12.1995)") << endl;
//                cin >> input_string;
//                directors_object.set_date_of_birth(input_string);
//                cout << ("Введите номер паспорта сотрудника (например, 4516561974)") << endl;
//                cin >> input_int_numbers;
//                directors_object.set_pasport(input_int_numbers);
//                cout << ("Введите номер телефона сотрудника (например, 9032697963)") << endl;
//                cin >> input_int_numbers;
//                directors_object.set_phone(input_int_numbers);
//                cout << ("Введите дату принятия сотрудника (например 16.04.2018)") << endl;
//                cin >> input_string;
//                directors_object.set_date_of_hiring(input_string);
//                cout << ("Введите время работы сотрудника (например, 09:00-18:00)") << endl;
//                cin >> input_string;
//                directors_object.set_working_hours(input_string);
//                cout << ("Введите зарплату сотрудника (в рублях)") << endl;
//                cin >> input_int;
//                directors_object.set_salary(input_int);
//                cout << ("Введите пароль к доступу сотрудника") << endl;
//                cin >> input_string;
//                directors_object.set_password(input_string);
//                directors_vector.push_back(directors_object);
//                directors_vector.insert(directors_vector.begin(), directors_object);
//                directors_file << endl;
//                directors_file << directors_object;
//                break;
//            }
//            case trading_company_fileds_name: {
//                cout << ("Введите номер сотрудника, чтобы изменить данные (смотри таблицу)") << endl;
//                for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//                    cout << *iter << endl;
//                cout << endl;
//                cout << ("Введите номер сотрудника: ") << endl;
//                cin >> input_int;
//                cout << directors_vector.at(input_int) << endl;
//                cout << endl;
//                cout << ("Изменить ID сотрудника - нажмите 1") << endl;
//                cout << ("Изменить должность сотрудника - нажмите 2") << endl;
//                cout << ("Изменить фамилию сотрудника - нажмите 3") << endl;
//                cout << ("Изменить имя сотрудника - нажмите 4") << endl;
//                cout << ("Изменить отчество сотрудника - нажмите 5") << endl;
//                cout << ("Изменить пол сотрудника - нажите 6") << endl;
//                cout << ("Изменить дату рождения сотрудника - нажмите 7") << endl;
//                cout << ("Изменить номер паспорта сотрудника - нажмите 8") << endl;
//                cout << ("Изменить номер телефона сотрудника - нажмите 9") << endl;
//                cout << ("Изменить дату принятия сотрудника - нажмите 10") << endl;
//                cout << ("Изменить время работы сотрудника - нажмите 11") << endl;
//                cout << ("Изменить зарплату сотрудника - нажмите 12") << endl;
//                cout << ("Изменить пароль к доступу сотрудника - нажмите 13") << endl;
//                input_int_numbers = (trading_company_fileds)input_trading_company_fileds;
//                cin >> input_int_numbers;
//                switch(input_int_numbers) {
//                    case trading_company_fileds_id:
//                        cout << directors_vector[input_int].get_id() << endl;
//                        cin >> input_int;
//                        directors_object.set_id(input_int);
//                    case trading_company_fileds_position:
//                        cout << directors_vector[input_int].get_position() << endl;
//                        cin >> input_string;
//                        directors_object.set_position(input_string);
//                    case trading_company_fileds_surname:
//                        cout << directors_vector[input_int].get_surname() << endl;
//                        cin >> input_string;
//                        directors_object.set_surname(input_string);
//                    case trading_company_fileds_name:
//                        cout << directors_vector[input_int].get_name() << endl;
//                        cin >> input_string;
//                        directors_object.set_name(input_string);
//                    case trading_company_fileds_patronymic:
//                        cout << directors_vector[input_int].get_patronymic() << endl;
//                        cin >> input_string;
//                        directors_object.set_patronymic(input_string);
//                    case trading_company_fileds_sex:
//                        cout << directors_vector[input_int].get_sex() << endl;
//                        cin >> input_string;
//                        directors_object.set_sex(input_string);
//                    case trading_company_fileds_date_of_birth:
//                        cout << directors_vector[input_int].get_date_of_birth() << endl;
//                        cin >> input_string;
//                        directors_object.set_date_of_hiring(input_string);
//                    case trading_company_fileds_pasport:
//                        cout << directors_vector[input_int].get_pasport() << endl;
//                        cin >> input_int_numbers;
//                        directors_object.set_pasport(input_int_numbers);
//                    case trading_company_fileds_phone:
//                        cout << directors_vector[input_int].get_phone() << endl;
//                        cin >> input_int_numbers;
//                        directors_object.set_phone(input_int_numbers);
//                    case trading_company_fileds_date_of_hiring:
//                        cout << directors_vector[input_int].get_date_of_hiring() << endl;
//                        cin >> input_string;
//                        directors_object.set_date_of_hiring(input_string);
//                    case trading_company_fileds_working_hours:
//                        cout << directors_vector[input_int].get_working_hours() << endl;
//                        cin >> input_string;
//                        directors_object.set_working_hours(input_string);
//                    case trading_company_fileds_salary:
//                        cout << directors_vector[input_int].get_salary() << endl;
//                        cin >> input_int;
//                        directors_object.set_salary(input_int);
//                    case trading_company_fileds_password:
//                        cout << directors_vector[input_int].get_password() << endl;
//                        cin >> input_string;
//                        directors_object.set_password(input_string);
////                        writing_data_in_file();
//                }
//            }
//            default:
//                exit(0);
//                break;
//        }
//        directors_file.close();
//    }
//    else { puts("Файл не найден"); exit(0); }
    return 0;
}

