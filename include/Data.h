#ifndef Data_h
#define Data_h

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

class Data
{
public:
    
    static Data &getInstance()
    {
        static Data data;
        return data;
    }

    template<typename T> void getReadingDataFromFile(T &object, const string &fileName)
    {
        ifstream file(fileName);

        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                Logger::info << " ---------- Считывание данных сотрудника ---------- " << endl;
                line >> object;
                checkData(object);
                tradingCompanyVector_.push_back(make_shared<T>(object));
                if (file.eof())
                    break;
            }
        }
        else
        {
            Logger::error << "Невозможно открыть файл >> " << fileName << endl;
        }
    }
        
    inline vector<shared_ptr<TradingCompany>> getObject() { return  tradingCompanyVector_; }
    template<typename T, class C> void checkParameter(T &parameter,
                                             function<T(TradingCompany&)> getParameter,
                                             function<void()> checkParameter, C object)
    {
        for (auto it = tradingCompanyVector_.begin(); it != tradingCompanyVector_.end(); ++it)
        {
            if (getParameter(*(*it)) == parameter && (&(*(*it)) != &(*object)))
            {
                checkParameter();
                it = tradingCompanyVector_.begin();
            }
        }
    }
    template<typename T> void changePersonalData(T *object)
    {
        object->changePersonalData();
    }
    
    friend class Director;
    
private:
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
    template<class T> void checkData(T &object)
    {
        for (const auto &tradingCompany: tradingCompanyVector_)
        {
            if (object.getId() == tradingCompany->getId())
            {
                object.changeStatusId();
            }
            if (object.getPassport() == tradingCompany->getPassport())
            {
                object.changeStatusPassport();
            }
            if (object.getPhone() == tradingCompany->getPhone())
            {
                object.changeStatusPhone();
            }
            if (object.getPassword() == tradingCompany->getPassword())
            {
                tradingCompany->changeStatusPassword(false);
                object.changeStatusPassword(true);
            }
            break;
        }
    }
    void getAllOtherData() const;
    void addNewEmployeeData();
    template<typename T> void setOtherData(T &object);
    template<typename T> void pushBack(T &object);
};

#endif // Data_h

