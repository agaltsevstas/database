#include "Director.h"
#include "Data.h"

Director::Director() : data_(&Data::instance()) {}

Director::~Director()
{
//    delete data_;
}

void Director::addNewEmployeeData()
{
    data_->newEmployeeData(this);
}

void Director::functional()
{
    std::string input;
    while (true)
    {
        std::cout << "Хотите изменить личные данные? - нажмите 1" << std::endl;
        std::cout << "Хотите вывести данные данные всех сотрудников? - нажмите 2" << std::endl;
        std::cout << "Хотите изменить чужие данные? - нажмите 3" << std::endl;
        std::cout << "Хотите добавить нового сотрудника? - нажмите 4" << std::endl;
        std::cout << "Хотите вывести лог файла? - нажмите 5" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
        try
        {
            std::cin >> input;
            utils::toLower(input);
            switch (utils::str(input.c_str()))
            {
                case utils::str("1") :
                    data_->changeData(this);
                    break;
                    
                case utils::str("2") :
                    data_->getAllOtherData();
                    break;
                    
                case utils::str("3") :
                    data_->changeOtherData(this);
                    break;
                    
                case utils::str("4") :
                    addNewEmployeeData();
                    break;
                    
                case utils::str("5") :
                    Logger::printLog(this);
                    break;
                    
                case utils::str("b") :
                    return;

                case utils::str("esc") :
                    EXIT(this);

                default:
                    throw input;
            }
        }
        catch (const std::string &exception)
        {
            Logger::error << "Введена >> " << exception << " - неверная команда!" << std::endl;
            std::cerr << "Вы ввели >> " << exception
                      << " - неверная команда! Попробуйте ввести заново: " << std::endl;
            functional();
        }
        catch(const std::exception &ex)
        {
            Logger::error << "Ошибка >> " << ex.what() << std::endl;
            std::cerr << "Ошибка >> " << ex.what() << std::endl;
        }
        catch(...)
        {
            Logger::error << "Неизвестная ошибка!" << std::endl;
            std::cerr << "Неизвестная ошибка!" << std::endl;
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



