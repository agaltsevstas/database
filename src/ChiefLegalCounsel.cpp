#include "ChiefLegalCounsel.h"
#include "Data.h"

ChiefLegalCounsel::ChiefLegalCounsel() : data_(&Data::instance()) {}

ChiefLegalCounsel::~ChiefLegalCounsel()
{
//    delete data_;
}

void ChiefLegalCounsel::functional()
{
    std::string input;
    while (true)
    {
        std::cout << "Хотите вывести личные данные? - нажмите 1" << std::endl;
        std::cout << "Хотите изменить личные данные? - нажмите 2" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
        try
        {
            std::cin >> input;
            utils::toLower(input);
            switch (utils::str(input.c_str()))
            {
                case utils::str("1") :
                    data_->printPersonalData(this);
                    break;
                    
                case utils::str("2") :
                    data_->changeData(this);
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
