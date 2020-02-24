#include "Director.h"
#include "Utils.h"

using namespace utils;

void Director::setPremium(int premium)
{
    salary_ += premium;
}
void Director::setFine(int fine)
{
    salary_ -= fine;
}

//void writing_data_in_file()
//{
//    vector <directors>::iterator iter;
//    directors_file.open(directors_location, ios::out);
//    if (directors_file.is_open())
//    {
//        for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//        {
//            directors_file << *iter;
//            cout << *iter << endl;+

//        }
//        directors_file.clear();
//        directors_file.close();
//    }
//}

void Director::functionalDirector(Director &director)
{
    Data &data = Data::getInstance();
    cout << "Хотите изменить личные данные? - нажмите 1" << endl;
    cout << "Хотите вывести данные данные всех сотрудников? - нажмите 2" << endl;
    cout << "Хотите изменить чужие данные? - нажмите 3" << endl;
    cout << "Хотите добавить нового сотрудника? - нажмите 4" << endl;
    cout << "Хотите вернуться назад? - введите B: " << endl;
    cout << "Хотите выйти из программы? - введите ESC: " << endl;
    string input;
    while (true)
    {
        try
        {
            cin >> input;
            toLower(input);
            switch (str(input.c_str()))
            {
                case str("1") :
                    director.changePersonalData();
                    break;
                case str("2") :
                    data.getAllOtherData();
                    break;
                case str("3") :
                    data.addNewEmployeeData();
                    break;
                case str("4") :
                    data.addNewEmployeeData();
                    break;
                case str("b") :
                    return;
                case str("esc") :
                    cout << "Вы вышли из программы!" << endl;
                    exit(0);
                default: throw input;
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

//void Directors::changeOtherData()
//{
//
//}

//    directors directors_object;
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
//            bool flag = false;
//                for (int index = 0; index != directors_vector.size(); index++)
//                {
//                    if (input_string == directors_vector[index].get_password())
//                    {
//                        cout << "Вы зашли за " << directors_vector[index].get_password() << "'a. " << endl;
//                        cout << "Приветствуем вас, " << directors_vector[index].get_surname() << " "
//                                                     << directors_vector[index].get_name() << " "
//                                                     << directors_vector[index].get_patronymic() << "!" << endl;
//                        flag = true;
//                        break;
//                    }
//                }
//                if (flag == false)
//                {
//                    cout << "Неправильный пароль! Введите заново или закончите выполнение программы, нажав ESC: ";
//                    cin >> input_string;
//                    goto tryAgain_password;
//                }
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
//            for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//                cout << *iter << endl;
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
//                        writing_data_in_file();
//                }
//            }
//            default:
//            exit(0);
//            break;
//        }
//        directors_file.close();
//    }
//    else { puts("Файл не найден"); exit(0); }





