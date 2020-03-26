#include "Data.h"
#include "Logger.h"
#include "Utils.h"

using namespace utils;

static string dataPath = "data";

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

int main()      
{
    setlocale(LC_ALL,"ru_RU.UTF-8");
    Logger::createInstance();
    Data &data = Data::instance();
    data.loadВatabase(dataPath);
    data.inputPassword();

    return 0;
}

