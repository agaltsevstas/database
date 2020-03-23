#include "Data.h"
#include "Utils.h"

using namespace utils;

static string directorPath = "director.txt";
static string chiefAccountantPath = "chief_accountant.txt";
static string chiefLegalCounselPath = "chief_legal_counsel.txt";
static string headOfProcurementPath = "head_of_procurement.txt";
static string headOfWarehousePath = "head_of_warehouse.txt";
static string salesManagerPath = "sales_manager.txt";
static string cashierPath = "cashier.txt";
static string accountantPath = "accountant.txt";
static string logisticianPath = "logistician.txt";
static string lawyerPath = "lawyer.txt";
static string purchasingManagerPath = "purchasing_manager.txt";
static string stevedorePath = "stevedore.txt";
static string driverPath = "driver.txt";
static string dataPath = "data";

//void reading_data_from_file(string directors_location, fstream directors_file, directors directors_object, vector <directors> directors_vector)
//{
//    directors_file.open(directors_location, ios::in);
//    if (directors_file.is_open())
//    {
//        do
//        {
//            directors_file >> directors_object;
//            directors_vector.push_back(directors_object);
//            if (directors_file.eof()) break;
//        } while(!directors_file.eof());
//        directors_file.clear();
//        directors_file.close();
//    }
//}
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
    Director director;
    ChiefAccountant chiefAccountant;
    ChiefLegalCounsel chiefLegalCounsel;
    HeadOfProcurement headOfProcurement;
    HeadOfWarehouse headOfWarehouse;
    SalesManager salesManager;
    Cashier cashier;
    Accountant accountant;
    Logistician logistician;
    Lawyer lawyer;
    PurchasingManager purchasingManager;
    Stevedore stevedore;
    Driver driver;
    
    Data &data = Data::instance();
    data.readDirectory(dataPath);
    data.readingDataFromFile(director, dataPath + "/" + directorPath);

//    data.getReadingDataFromFile(chiefAccountant, dataPath + "/" + chiefAccountantPath);
//    data.getReadingDataFromFile(chiefLegalCounsel, dataPath + "/" + chiefLegalCounselPath);
//    data.getReadingDataFromFile(headOfProcurement, dataPath + "/" + headOfProcurementPath);
//    data.getReadingDataFromFile(headOfWarehouse, dataPath + "/" + headOfWarehousePath);
//    data.getReadingDataFromFile(salesManager, dataPath + "/" + salesManagerPath);
//    data.getReadingDataFromFile(cashier, dataPath + "/" + cashierPath);
//    data.getReadingDataFromFile(accountant, dataPath + "/" + accountantPath);
//    data.getReadingDataFromFile(logistician, dataPath + "/" + logisticianPath);
//    data.getReadingDataFromFile(lawyer, dataPath + "/" + lawyerPath);
//    data.getReadingDataFromFile(purchasingManager, dataPath + "/" + purchasingManagerPath);
//    data.getReadingDataFromFile(stevedore, dataPath + "/" + stevedorePath);
//    data.getReadingDataFromFile(driver, dataPath + "/" + driverPath);
    data.setPassword();

    return 0;
}

