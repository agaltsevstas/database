#include "Director.h"
#include "Data.h"

Director::Director() : _data(&Data::Instance()) {}

const Director& Director::operator = (const Employee &object)
{
    Employee::operator=(object);
    return *this;
}

void Director::AddNewEmployeeData()
{
    _data->NewEmployeeData(this);
}

void Director::Functional()
{
    Logger::info << "******************** Личный кабинет ********************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "******************** Личный кабинет ********************" << std::endl;
        std::cout << "Хотите вывести личные данные? - нажмите 1" << std::endl;
        std::cout << "Хотите изменить личные данные? - нажмите 2" << std::endl;
        std::cout << "Хотите вывести данные всех сотрудников? - нажмите 3" << std::endl;
        std::cout << "Хотите найти данные сотрудника? - нажмите 4" << std::endl;
        std::cout << "Хотите изменить данные сотрудника? - нажмите 5" << std::endl;
        std::cout << "Хотите добавить нового сотрудника? - нажмите 6" << std::endl;
        std::cout << "Хотите удалить сотрудника? - нажмите 7" << std::endl;
        std::cout << "Хотите изменить режим вывода данных? - нажмите 8" << std::endl;
        std::cout << "Хотите вывести лог файла? - нажмите 9" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            Utils::tolower(input);
            switch (Utils::Hash(input.c_str()))
            {
                case Utils::Hash("1") :
                    _data->PrintPersonalData(this);
                    break;
                    
                case Utils::Hash("2") :
                    _data->ChangeData(this);
                    break;
                    
                case Utils::Hash("3") :
                    _data->GetAllOtherData();
                    break;
                    
                case Utils::Hash("4") :
                    _data->Find(this);
                    break;
                    
                case Utils::Hash("5") :
                    _data->ChangeOtherData(this);
                    break;
                    
                case Utils::Hash("6") :
                    _data->NewEmployeeData(this);
                    break;
                    
                case Utils::Hash("7") :
                    _data->DeleteEmployeeData(this);
                    break;
                    
                case Utils::Hash("8") :
                    _data->SetModeOutputData(this);
                    break;
                    
                case Utils::Hash("9") :
                    Logger::PrintLog(this);
                    break;
                    
                case Utils::Hash("b") :
                case Utils::Hash("н") :
                    return;

                case Utils::Hash("esc") :
                case Utils::Hash("выход") :
                    EXIT(this);

                default:
                    throw input;
            }
        }
        catch (const std::string &exception)
        {
            Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
            std::cerr << "Вы ввели >> " << exception << " - неверная команда!" << std::endl;
        }
    }
}



