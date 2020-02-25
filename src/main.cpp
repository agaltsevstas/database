#include "TradingCompany.h"
#include "Director.h"
#include "ChiefAccountant.h"
#include "ChiefLegalCounsel.h"
#include "HeadOfProcurement.h"
#include "HeadOfWarehouse.h"
#include "SalesManager.h"
#include "Cashier.h"
#include "Accountant.h"
#include "Logistician.h"
#include "Lawyer.h"
#include "PurchasingManager.h"
#include "Stevedore.h"
#include "Driver.h"
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

typedef union
{
    class Director;
    class ChiefAccountant;
    class ChiefLegalCounsel;
    class HeadOfProcurement;
    class HeadOfWarehouse;
    class SalesManager;
    class Cashier;
    class Accountant;
    class Logistician;
    class Lawyer;
    class PurchasingManager;
    class Stevedore;
    class Driver;
} RetType;


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
    string path = dataPath + "/" + directorPath;
    
    Data &data = Data::getInstance();
    data.getReadingDataFromFile(director, path);
    data.checkData();
//    data.getReadingDataFromFile(director, dataPath + "/" + directorPath);
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
    
    shared_ptr<Director> directorPtr;
    shared_ptr<ChiefAccountant> chiefAccountantPtr;
    shared_ptr<ChiefLegalCounsel> chiefLegalCounselPtr;
    shared_ptr<HeadOfProcurement> headOfProcurementPtr;
    shared_ptr<HeadOfWarehouse> headOfWarehousePtr;
    shared_ptr<SalesManager> salesManagerPtr;
    shared_ptr<Cashier> cashierPtr;
    shared_ptr<Accountant> accountantPtr;
    shared_ptr<Logistician> logisticianPtr;
    shared_ptr<PurchasingManager> purchasingManagerPtr;
    shared_ptr<Stevedore> stevedorePtr;
    shared_ptr<Lawyer> lawyerPtr;
    shared_ptr<Driver> driverPtr;
    
    string input;
    unsigned int input_int = 0;
//    vector<trading_company*> List; // если нет родительского класса vector<void*> List;
//    List.push_back(new directors);
//    trading_company *p = List[0];
//    directors *t1 = nullptr;
//    t1 = dynamic_cast<directors*>(p));
    cout << ("Введите пароль для получения доступа к базе данных или закончите выполнение программы, введите ESC: ") << endl;
    cin >> input;
    while (true)
    {
        try
        {
            RetType retType;
            for (const auto &tradingCompany: data.getObject())
            {
                if (input == tradingCompany->getPassword())
                {
                    if ((directorPtr = dynamic_pointer_cast<Director>(tradingCompany)))
                    {
                        directorPtr->functional();
                    }
                    if ((chiefAccountantPtr = dynamic_pointer_cast<ChiefAccountant>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*chief_accountant_pointer);
                    }
                    if ((chiefLegalCounselPtr = dynamic_pointer_cast<ChiefLegalCounsel>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*chief_legal_counsel_pointer);
                    }
                    if ((headOfProcurementPtr = dynamic_pointer_cast<HeadOfProcurement>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*head_of_procurement_pointer);
                    }
                    if ((headOfWarehousePtr = dynamic_pointer_cast<HeadOfWarehouse>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*head_of_warehouses_pointer);
                    }
                    if ((salesManagerPtr = dynamic_pointer_cast<SalesManager>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*sales_managers_pointer);
                    }
                    if ((cashierPtr = dynamic_pointer_cast<Cashier>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*cashier_pointer);
                    }
                    if ((accountantPtr = dynamic_pointer_cast<Accountant>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*accountants_pointer);
                    }
                    if ((logisticianPtr = dynamic_pointer_cast<Logistician>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*logisticians_pointer);
                    }
                    if ((lawyerPtr = dynamic_pointer_cast<Lawyer>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*lawyer_pointer);
                    }
                    if ((purchasingManagerPtr = dynamic_pointer_cast<PurchasingManager>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*purchasing_managers_pointer);
                    }
                    if ((stevedorePtr = dynamic_pointer_cast<Stevedore>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*stevedores_pointer);
                    }
                    if ((driverPtr = dynamic_pointer_cast<Driver>(tradingCompany)))
                    {
    //                    trading_company::change_personal_data(*drivers_pointer);
                    }
                }
            }
            toLower(input);
            if(input == "esc")
            {
                cout << "Вы вышли из программы!" << endl;
                exit(0);
            }
            else
                throw input;
        }
        catch (const string &ex)
        {
            cout << "Вы ввели: " << ex << " - неверный пароль! Попробуйте ввести заново или закончите выполнение программы, введя ESC: "<< endl;
            cin >> input;
        }
    }
    return 0;
}

