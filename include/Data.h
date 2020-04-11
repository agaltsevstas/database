#ifndef Data_h
#define Data_h

#include "ObjectFactory.h"
#include "TradingCompany.h"
#include "Director.h"
#include "ChiefAccountant.h"
#include "ChiefLegalCounsel.h"
#include "HeadOfProcurement.h"
#include "HeadOfWarehouse.h"
#include "HRManager.h"
#include "SalesManager.h"
#include "Cashier.h"
#include "Accountant.h"
#include "Logistician.h"
#include "Lawyer.h"
#include "PurchasingManager.h"
#include "Loader.h"
#include "Driver.h"

class Director;
//class ChiefAccountant;
//class ChiefLegalCounsel;
//class HeadOfProcurement;
//class HeadOfWarehouse;
class HRManager;
//class SalesManager;
//class Cashier;
//class Accountant;
//class Logistician;
//class Lawyer;
//class PurchasingManager;
//class Loader;
//class Driver;

typedef union
{
    class Director;
    class ChiefAccountant;
    class ChiefLegalCounsel;
    class HeadOfProcurement;
    class HeadOfWarehouse;
    class HRManager;
    class SalesManager;
    class Cashier;
    class Accountant;
    class Logistician;
    class Lawyer;
    class PurchasingManager;
    class Loader;
    class Driver;
} RetType;

class Data
{
    friend class Director;
    
public:
    static Data &instance()
    {
        static Data data;
        return data;
    }
    
    void loadDatabase(const string &directoryPath);

    void inputPassword();
        
    template<typename T, class C> void checkParameter(const T &parameter,
                                                      function<T(TradingCompany&)> getParameter,
                                                      function<void()> checkParameter,
                                                      const C &object, bool isMatchCheck = false)
    {
        if (isMatchCheck)
        {
            for (auto it = tradingCompanyObjects_.begin(); it != tradingCompanyObjects_.end(); ++it)
            {
                if (getParameter(*(*it)) == parameter && (&(*(*it)) != &object))
                {
                    checkParameter();
                    it = tradingCompanyObjects_.begin();
                }
            }
        }
        checkParameter();
    }
//    template<class C> void changePersonalData(C *object)
//    {
//        object->changePersonalData();
//    }
    
    friend void Director::addNewEmployeeData();
    friend void HRManager::addNewEmployeeData();
    
private:
    ObjectFactory<string, TradingCompany> objectFactory_;
    vector<shared_ptr<TradingCompany>> tradingCompanyObjects_;
    
    Data() {}
    Data(const Data&) = delete;
    Data& operator=(Data&) = delete;
    template<class C> void checkData(C &object);
    template<class C> void checkPassword(C &object);
    void getAllOtherData() const;
    template<class C> void setOtherData(C &object);
    void newEmployeeData();
    template<class C> void pushBack(C &object);
};

#endif // Data_h

