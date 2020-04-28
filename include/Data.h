#ifndef Data_h
#define Data_h

#include <iostream>

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
#include "Utils.h"

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

const std::list<std::string> positions
{
    "Бухгалтер",
    "Водитель",
    "Главный_бухгалтер",
    "Главный_юрист-консультант",
    "Грузчик",
    "Директор",
    "Логист",
    "Менеджер_по_закупкам",
    "Менеджер_по_продажам",
    "Кассир",
    "Начальник_отдела_закупок",
    "Начальник_склада",
    "Юрист"
};

const std::list<std::string> warnings
{
    "Ваш id не удовлетворяет требованиям!\n",
    "Ваша должность не удовлетворяет требованиям!\n",
    "Ваша фамилия не удовлетворяет требованиям!\n",
    "Ваше имя не удовлетворяет требованиям!\n",
    "Ваше отчество не удовлетворяет требованиям!\n",
    "Ваш пол не удовлетворяет требованиям!\n",
    "Ваша дата рождения не удовлетворяет требованиям!\n",
    "Ваш паспорт не удовлетворяет требованиям!\n",
    "Ваш телефон не удовлетворяет требованиям!\n",
    "Ваша почта не удовлетворяет требованиям!\n",
    "Ваша дата принятия на работу не удовлетворяет требованиям!\n",
    "Ваши часы работы не удовлетворяет требованиям!\n",
    "Ваша зарплата не удовлетворяет требованиям!\n",
    "Ваш пароль не удовлетворяет требованиям!\n"
};

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
    
private:
    
    template <class C>
    struct Parameter
    {
        Field field;
        std::function<uint(TradingCompany&)> getUintParameter = nullptr;
        std::function<uint64_t(TradingCompany&)> getUint64Parameter = nullptr;
        std::function<std::string(TradingCompany&)> getStringParameter = nullptr;
        std::function<void()> checkParameter = nullptr;
        std::function<void()> changeStatusParameter = nullptr;
        C *object = nullptr;
        bool isMatchCheck = false;
    };
    
public:
    
    static Data &instance()
    {
        static Data data;
        return data;
    }
    
    void loadDatabase(const std::string &directoryPath);

    void inputPassword();
        
    template<typename T, class C> void checkParameter(std::function<T(TradingCompany&)> getParameter,
                                                      std::function<void()> checkParameter,
                                                      C *object, const bool isMatchCheck = false)
    {
        if (isMatchCheck)
        {
            const auto parameter = getParameter(*object);
            const std::string value = utils::convertToString(parameter);
            if (value.empty())
            {
                checkParameter();
                checkData(object);
            }
            for (auto it = std::begin(tradingCompanyObjects_); it != std::end(tradingCompanyObjects_);)
            {
                if (getParameter(*(*it)) == getParameter(*object) && (&(*(*it)) != object))
                {
                    checkParameter();
                    checkData(object);
                    it = tradingCompanyObjects_.begin();
                }
                else
                {
                    ++it;
                }
            }
        }
        else
        {
            checkParameter();
        }
    }
    
    friend void Director::addNewEmployeeData();
    friend void HRManager::addNewEmployeeData();
    
private:
    ObjectFactory<std::string, TradingCompany> objectFactory_;
    std::vector<std::shared_ptr<TradingCompany>> tradingCompanyObjects_;
    
    Data() {}
    Data(const Data&) = delete;
    Data& operator=(Data&) = delete;
    template<class C> void checkParameter(Parameter<C> &parameter);
    template<class C> Parameter<C> selectParameter(const Field &field, C *object, const std::string &message = {});
    void checkParameters(TradingCompany *object);
    void checkData(TradingCompany *object);
    template<class C> void checkPassword(C &object);
    void getAllOtherData() const;
    template<class C> void setOtherData(C &object);
    void newEmployeeData(const TradingCompany *object);
    template<class C> void pushBack(C &object);
};

#endif // Data_h

