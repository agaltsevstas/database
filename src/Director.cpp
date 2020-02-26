#include "Director.h"
#include "Utils.h"

using namespace utils;

void Director::functional()
{
    Data &data = Data::getInstance();
    string input;
    while (true)
    {
        displayUser();
        cout << "Хотите изменить личные данные? - нажмите 1" << endl;
        cout << "Хотите вывести данные данные всех сотрудников? - нажмите 2" << endl;
        cout << "Хотите изменить чужие данные? - нажмите 3" << endl;
        cout << "Хотите добавить нового сотрудника? - нажмите 4" << endl;
        cout << "Хотите вернуться назад? - введите B: " << endl;
        cout << "Хотите выйти из программы? - введите ESC: " << endl;
        try
        {
            cin >> input;
            toLower(input);
            switch (str(input.c_str()))
            {
                case str("1") :
                    data.changePersonalData(this);
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

void Director::setPremium(int premium)
{
    salary_ += premium;
}
void Director::setFine(int fine)
{
    salary_ -= fine;
}



