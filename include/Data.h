#ifndef Data_h
#define Data_h

#include "TradingCompany.h"

class Data
{
public:
    
    static Data &getInstance()
    {
        static Data data;
        return data;
    }

    template <typename T> void getReadingDataFromFile(T &object, const string &fileName)
    {
        ifstream file(fileName);

        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                Logger::info << " ---------- Считывание данных сотрудника ---------- " << endl;
                line >> object;
                ids_.push_back(object.getId());
                phones_.push_back(object.getPhone());
                passports_.push_back(object.getPassport());
                passwords_.push_back(object.getPassword());
                tradingCompanyVector_.push_back(make_shared<T>(object));
                if (file.eof())
                    break;
            }
        }
        else
        {
            Logger::warning << "Невозможно открыть файл >> " << fileName << endl;
        }
    }
    
    void checkData();
    inline vector<shared_ptr<TradingCompany>> getObject() { return  tradingCompanyVector_; }
    template <typename T> void changePersonalData(T *object)
    {
        object->changePersonalData();
    }
    void getAllOtherData() const;
    template <typename T> void pushBack(T &object);
    void addNewEmployeeData();
    template <typename T> void setOtherData(T &object);
    
private:
    vector<uint> ids_;
    vector<uint64_t> phones_;
    vector<uint64_t> passports_;
    vector<string> passwords_;
    vector<shared_ptr<TradingCompany>> tradingCompanyVector_;
    shared_ptr<Director> directorPtr_;
    shared_ptr<ChiefAccountant> chiefAccountantPtr_;
    shared_ptr<ChiefLegalCounsel> chiefLegalCounselPtr_;
    shared_ptr<HeadOfProcurement> headOfProcurementPtr_;
    shared_ptr<HeadOfWarehouse> headOfWarehousePtr_;
    shared_ptr<SalesManager> salesManagerPtr_;
    shared_ptr<Cashier> cashierPtr_;
    shared_ptr<Accountant> accountantPtr_;
    shared_ptr<Logistician> logisticianPtr_;
    shared_ptr<PurchasingManager> purchasingManagerPtr_;
    shared_ptr<Stevedore> stevedorePtr_;
    shared_ptr<Lawyer> lawyerPtr_;
    shared_ptr<Driver> driverPtr_;
    Data() {}
    Data(const Data&) = delete;
    Data& operator=(Data&) = delete;
};

#endif // Data_h

