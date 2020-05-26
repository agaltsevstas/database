#include <iostream>
#include <boost/program_options.hpp>

#include "Data.h"

int main(int argc, char *argv[])
{
    std::srand(static_cast<uint>(time(0)));
    setlocale(LC_ALL,"ru_RU.UTF-8");
    Logger::createInstance();
    std::string directory = "data/"; // Путь к модулям
    if (argc > 1)
    {
        std::string parameter;
        boost::program_options::options_description desc("Требуемые опции");
        desc.add_options() 
                ("help,h", "Помощь")
                ("directory,d", boost::program_options::value<std::string>(&parameter), "Путь к модулям");
        try
        {
            boost::program_options::variables_map vm;
            store(parse_command_line(argc, argv, desc), vm);
            notify(vm);

            if (vm.count("help"))
            {
                std::cout << desc << std::endl;
                return 0;
            }

            if (vm.count("directory"))
            {
                directory = vm["directory"].as<std::string>();
                std::cout << "Выбран путь к модулям >> " << directory << std::endl;
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
    replace(directory.begin(), directory.end(), '\\', '/');
    if (*directory.rbegin() != '/')
    {
        directory += "/";
    }
    Data &data = Data::instance();
    data.loadDatabase(directory);
    data.inputPassword();
    Logger::deleteInstance();

    return 0;
}

