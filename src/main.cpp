#include <iostream>
#include <boost/program_options.hpp>

#include "Data.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    std::srand(static_cast<uint>(time(0))); // Инициализация генератора случайных чисел rand
    setlocale(LC_ALL,"ru_RU.UTF-8"); // Инициализация русских символов
    Logger::Instance();
    std::string directory = "data/"; // Каталог с базой данных по умолчанию
    if (argc > 1)
    {
        std::string parameter;
        // Описание допустимых аргументов командной строки, пример:
        // --directory=data/
        boost::program_options::options_description options_description("Требуемые опции");
        options_description.add_options()
                ("help,h", "Помощь")
                ("directory,d", boost::program_options::value<std::string>(&parameter), "Путь к базе данных");
        try
        {
            boost::program_options::variables_map variables_map; // Словарь аргументов командной строки
            store(parse_command_line(argc, argv, options_description), variables_map); // Сохранение аргументов в словарь
            notify(variables_map); // Объединение аргументов в словаре

            // Вывод справочной информации
            if (variables_map.count("help"))
            {
                std::cout << options_description << std::endl;
                return 0;
            }

            // Считывание пути к каталогу
            if (variables_map.count("directory"))
            {
                directory = variables_map["directory"].as<std::string>();
                std::cout << "Выбран путь к базе данных >> " << directory << std::endl;
            }
            else
            {
                throw std::string(argv[1]);
            }
        }
        catch(const std::string &exception)
        {
            Logger::error << "Неверный параметр >> " << exception << std::endl;
        }
        catch(const std::exception &ex)
        {
            Logger::error << "Неверный параметр >> " << ex.what() << std::endl;
        }
        catch(...)
        {
            Logger::error << "Неизвестная ошибка!" << std::endl;
        }
    }
    replace(directory.begin(), directory.end(), '\\', '/'); // Изменение в пути к каталогу косой черты в другую сторону
    // Добавление в конце косой черты
    if (*directory.rbegin() != '/')
    {
        directory += "/";
    }
    
    try
    {
        DataProxy::LoadDatabase(directory);
        DataProxy::AccountLogin();
    }
    catch (const std::exception &ex)
    {
        Logger::error << "Ошибка >> " << ex.what() << std::endl;
        std::cout << "Ошибка >> " << ex.what() << std::endl;
    }
    catch (...)
    {
        Logger::error << "Неизвестная ошибка!" << std::endl;
        std::cerr << "Неизвестная ошибка!" << std::endl;
        exit(0);
    }

    return 0;
}

