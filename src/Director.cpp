#include "Director.h"
#include "Data.h"

Director::Director() : data_(&Data::instance()) {}

Director::~Director()
{
//    delete data_;
}

void Director::changePersonalData()
{
    std::string input;
    while (true)
    {
        std::cout << "Изменить свой ID - нажмите 1" << std::endl;
        std::cout << "Изменить свою должность - нажмите 2" << std::endl;
        std::cout << "Изменить свою фамилию - нажмите 3" << std::endl;
        std::cout << "Изменить своё имя - нажмите 4" << std::endl;
        std::cout << "Изменить своё отчество - нажмите 5" << std::endl;
        std::cout << "Изменить свой пол - нажите 6" << std::endl;
        std::cout << "Изменить свою дату рождения - нажмите 7" << std::endl;
        std::cout << "Изменить свой номер паспорта - нажмите 8" << std::endl;
        std::cout << "Изменить свой номер телефона - нажмите 9" << std::endl;
        std::cout << "Изменить свою почту - нажмите 10" << std::endl;
        std::cout << "Изменить свою дату принятия на работу - нажмите 11" << std::endl;
        std::cout << "Изменить свои часы работы - нажмите 12" << std::endl;
        std::cout << "Изменить свою зарплату - нажмите 13" << std::endl;
        std::cout << "Изменить свой пароль к доступу - нажмите 14" << std::endl;
        std::cout << "Хотите вернуться назад? - введите B: " << std::endl;
        std::cout << "Хотите выйти из программы? - введите ESC: " << std::endl;
        try
        {
            std::cin >> input;
            utils::toLower(input);
            switch (utils::str(input.c_str()))
            {
                case utils::str("1") :
                    changeStatusId(true);
                    data_->checkParameter(std::function<uint(TradingCompany&)>{&TradingCompany::getId},
                                          bind(&TradingCompany::checkId, this, ""), this, true);
                    break;
                    
                case utils::str("2") :
                {
                    std::cout << "При изменении своей должности вы теряете свои полномочия" << std::endl;
                    std::cout << "Введите yes - для продолжения, no - для отмены" << std::endl;
                    std::cout << "Ввод: " << std::endl;
                    std::string input;
                    std::cin >> input;
                    utils::toLower(input);
                    if (input == "yes")
                    {
                        std::cout << "Выберите одну из предложенных должности: " << std::endl;
                        copy(positions.begin(), positions.end(), std::ostream_iterator<std::string>(std::cout, " "));
                        changeStatusPosition();
                        data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getPosition},
                                              bind(&TradingCompany::checkPosition, this, ""), this);
                    }
                    else if (input == "no")
                    {
                        changePersonalData();
                    }
                    break;
                }
                    
                case utils::str("3") :
                    changeStatusSurname();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getSurname},
                                          bind(&TradingCompany::checkSurname, this, ""), this);
                    break;
                    
                case utils::str("4") :
                    changeStatusName();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getName},
                                          bind(&TradingCompany::checkName, this, ""), this);
                    break;
                    
                case utils::str("5") :
                    changeStatusPatronymic();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getPatronymic},
                                          bind(&TradingCompany::checkPatronymic, this, "!\n"), this);
                    break;
                    
                case utils::str("6") :
                    changeStatusSex();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getSex},
                                          bind(&TradingCompany::checkSex, this, ""), this);
                    break;
                    
                case utils::str("7") :
                    changeStatusDateOfBirth();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfBirth},
                                          bind(&TradingCompany::checkDateOfBirth, this, ""), this);
                    break;
                    
                case utils::str("8") :
                    changeStatusPassport(true);
                    data_->checkParameter(std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                                          bind(&TradingCompany::checkPassport, this, ""), this, true);
                    break;
                    
                case utils::str("9") :
                    changeStatusPhone(true);
                    data_->checkParameter(std::function<uint64_t(TradingCompany&)>{&TradingCompany::getPassport},
                                          bind(&TradingCompany::checkPassport, this, ""), this, true);
                    break;
                    
                case utils::str("10") :
                    changeStatusEmail(true);
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getEmail},
                                          bind(&TradingCompany::checkEmail, this, ""), this, true);
                    break;
                    
                case utils::str("11") :
                    changeStatusDateOfHiring();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getDateOfHiring},
                                          bind(&TradingCompany::checkDateOfHiring, this, ""), this);
                    break;
                    
                case utils::str("12") :
                    changeStatusWorkingHours();
                    break;
                    
                case utils::str("13") :
                    changeStatusSalary();
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getWorkingHours},
                                          bind(&TradingCompany::checkWorkingHours, this, "Ваши часы работы не удовлетворяет требованиям!\n"), this);
                    break;
                    
                case utils::str("14") :
                    changeStatusPassword(true);
                    data_->checkParameter(std::function<std::string(TradingCompany&)>{&TradingCompany::getPassword},
                                          bind(&TradingCompany::checkPassword, this, ""), this, true);
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
            changePersonalData();
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

void Director::addNewEmployeeData()
{
    data_->newEmployeeData(this);
}

void Director::functional()
{
    displayUser();
    
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
                    changePersonalData();
                    break;
                    
                case utils::str("2") :
                    data_->getAllOtherData();
                    break;
                    
                case utils::str("3") :
                    addNewEmployeeData();
                    break;
                    
                case utils::str("4") :
                    addNewEmployeeData();
                    break;
                    
                case utils::str("5") :
                    Logger::info << " ********** Вход в Logger ********** " << std::endl;
                    Logger::printLog(this);
                    Logger::info << " ********** Выход из Logger ********** " << std::endl;
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
            changePersonalData();
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



