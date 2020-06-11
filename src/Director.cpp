#include "Director.h"
#include "Data.h"

Director::Director() : data_(&Data::instance()) {}

const Director& Director::operator = (const TradingCompany &object)
{
    TradingCompany::operator=(object);
    return *this;
}

void Director::addNewEmployeeData()
{
    data_->newEmployeeData(this);
}

void Director::functional()
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
            utils::tolower(input);
            switch (utils::str(input.c_str()))
            {
                case utils::str("1") :
                    data_->printPersonalData(this);
                    break;
                    
                case utils::str("2") :
                    data_->changeData(this);
                    break;
                    
                case utils::str("3") :
                    data_->getAllOtherData();
                    break;
                    
                case utils::str("4") :
                    data_->find(this);
                    break;
                    
                case utils::str("5") :
                    data_->changeOtherData(this);
                    break;
                    
                case utils::str("6") :
                    data_->newEmployeeData(this);
                    break;
                    
                case utils::str("7") :
                    data_->deleteEmployeeData(this);
                    break;
                    
                case utils::str("8") :
                    data_->setModeOutputData(this);
                    break;
                    
                case utils::str("9") :
                    Logger::printLog(this);
                    break;
                    
                case utils::str("b") :
                case utils::str("н") :
                    return;

                case utils::str("esc") :
                case utils::str("выход") :
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



