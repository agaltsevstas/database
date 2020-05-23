#include "Lawyer.h"
#include "Data.h"

Lawyer::Lawyer() : data_(&Data::instance()) {}

Lawyer::~Lawyer()
{
//    delete data_;
}

const Lawyer& Lawyer::operator = (const TradingCompany &object)
{
    TradingCompany::operator=(object);
    return *this;
}

void Lawyer::functional()
{
    while (true)
    {
        std::cout << "Хотите вывести личные данные? - нажмите 1" << std::endl;
        std::cout << "Хотите изменить личные данные? - нажмите 2" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B(англ.) или Н(рус.): " << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC или ВЫХОД: " << std::endl;
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
                    
                case utils::str("b") :
                    return;
                    
                case utils::str("н") :
                    return;

                case utils::str("esc") :
                    EXIT(this);
                    
                case utils::str("выход") :
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
            continue;
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
