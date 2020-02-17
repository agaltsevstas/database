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

class Data
{
public:
    
    static Data &getInstance()
    {
        static Data data;
        return data;
    }
    
    vector<shared_ptr<TradingCompany>> tradingCompanyVector_;
    
    template <class T> void getReadingDataFromFile(T &object, const string &fileName)
    {
        ifstream file(fileName);
        
        string line;
        if (file.is_open())
        {
            while (getline(file, line))
            {
                Logger::info << " ---------- Считывание данных сотрудника ---------- " << endl;
                line >> object;
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
    
    template <class T> void pushBack(T &object)
    {
        uint maxId = 0;
        shared_ptr<T> pointer;
        vector<shared_ptr<TradingCompany>>::iterator it;
        
        for (it = tradingCompanyVector_.begin(); it != tradingCompanyVector_.end(); ++it)
        {
            if ((pointer = dynamic_pointer_cast<T>(*it)) && (*it)->getId() > maxId)
            {
                maxId = (*it)->getId();
            }
            else
            {
                break;
            }
        }
        
//        object.setId(to_string(++maxId));
        tradingCompanyVector_.insert(it, make_shared<T>(object));
    }
    
private:
    
    int intValue = 0;
    string stringValue;
    
    Data() {}
    Data(const Data&) = delete;
    Data& operator=(Data&) = delete;
};

#endif // Data_h

