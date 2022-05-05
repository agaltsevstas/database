#include "PurchasingManager.h"
#include "Data.h"

PurchasingManager::PurchasingManager() : _data(&Data::Instance()) {}

const PurchasingManager& PurchasingManager::operator = (const TradingCompany &object)
{
    TradingCompany::operator=(object);
    return *this;
}

void PurchasingManager::Functional()
{
    Logger::info << "******************** Личный кабинет ********************" << std::endl;
    while (true)
    {
        std::cout << std::endl;
        std::cout << "******************** Личный кабинет ********************" << std::endl;
        std::cout << "Хотите вывести личные данные? - нажмите 1" << std::endl;
        std::cout << "Хотите изменить личные данные? - нажмите 2" << std::endl;
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
