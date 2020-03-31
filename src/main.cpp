#include <iostream>
#include <boost/program_options.hpp>

#include "Data.h"
#include "Logger.h"
#include "Utils.h"

using namespace std;
using namespace boost::program_options;
using namespace utils;

//void writing_data_in_file()
//{
//    vector <directors>::iterator iter;
//    directors_file.open(directors_location, ios::out);
//    if (directors_file.is_open())
//    {
//        for(iter = directors_vector.begin(); iter != directors_vector.end(); iter++)
//        {
//            directors_file << *iter;
//            cout << *iter << endl;
//        }
//        directors_file.clear();
//        directors_file.close();
//    }
//}

int main(int argc, char *argv[])
{
    string directory = "data/"; // Путь к модулям
    if (argc > 1)
    {
        string parameter;
        options_description desc("Требуемые опции");
        desc.add_options()
                ("help,h", "Помощь")
                ("directory,d", value<string>(&parameter), "Путь к модулям");
        try
        {
            variables_map vm;
            store(parse_command_line(argc, argv, desc), vm);
            notify(vm);

            if (vm.count("help"))
            {
                cout << desc << endl;
                return 0;
            }

            if (vm.count("directory"))
            {
                directory = vm["directory"].as<string>();
                cout << "Выбран путь к модулям >> " << directory << endl;
            }
            else
            {
                throw string(argv[1]);
            }
        }
        catch(const string &exception)
        {
            cerr << "Неверный параметр >> " << exception << endl;
        }
        catch(const exception &ex)
        {
            cerr << "Неверный параметр >> " << ex.what() << endl;
        }
        catch(...)
        {
            cerr << "Неизвестная ошибка!" << endl;
        }
    }
    replace(directory.begin(), directory.end(), '\\', '/');
    if (*directory.rbegin() != '/')
    {
        directory += "/";
    }
    setlocale(LC_ALL,"ru_RU.UTF-8");
    Logger::createInstance();
    Data &data = Data::instance();
    data.loadDatabase(directory);
    data.inputPassword();

    return 0;
}

