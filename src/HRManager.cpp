#include "HRManager.h"
#include "Data.h"

HRManager::HRManager() : data_(&Data::instance()) {}

const HRManager& HRManager::operator = (const TradingCompany &object)
{
    TradingCompany::operator=(object);
    return *this;
}

void HRManager::addNewEmployeeData()
{
    data_->newEmployeeData(this);
}

void HRManager::functional()
{
    Logger::info << "******************** Личный кабинет ********************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "******************** Личный кабинет ********************" << std::endl;
        std::cout << "Хотите вывести личные данные? - нажмите 1" << std::endl;
        std::cout << "Хотите изменить личные данные? - нажмите 2" << std::endl;
        std::cout << "Хотите добавить нового сотрудника? - нажмите 3" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.)" << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД" << std::endl;
        std::cout << "Ввод: ";
        try
        {
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            switch (utils::hash(input.c_str()))
            {
                case utils::hash("1") :
                    data_->printPersonalData(this);
                    break;
                    
                case utils::hash("2") :
                    data_->changeData(this);
                    break;
                    
                case utils::hash("3") :
                    addNewEmployeeData();
                    break;
                    
                case utils::hash("b") :
                case utils::hash("н") :
                    return;

                case utils::hash("esc") :
                case utils::hash("выход") :
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
