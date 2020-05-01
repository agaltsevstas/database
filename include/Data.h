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
    "Главный_бухгалтер",
    "Главный_юрист-консультант",
    "Грузчик",
    "Директор",
    "Логист",
    "Менеджер_по_закупкам",
    "Менеджер_по_персоналу",
    "Менеджер_по_продажам",
    "Кассир",
    "Начальник_отдела_закупок",
    "Начальник_склада",
    "Юрист"
};

const std::vector<std::string> warnings
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
    
    template <class Class>
    struct Parameter
    {
        Field field;
        std::function<uint(TradingCompany&)> getUintParameter = nullptr;
        std::function<uint64_t(TradingCompany&)> getUint64Parameter = nullptr;
        std::function<std::string(TradingCompany&)> getStringParameter = nullptr;
        std::function<void()> checkParameter = nullptr;
        std::function<void()> changeStatusParameter = nullptr;
        Class *object = nullptr;
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
    void printPersonalData(TradingCompany *object);
    void changeData(TradingCompany *object, TradingCompany *otherObject = nullptr);
    
    friend void Director::addNewEmployeeData();
    friend void HRManager::addNewEmployeeData();
    
private:
    ObjectFactory<std::string, TradingCompany> objectFactory_;
    std::vector<std::shared_ptr<TradingCompany>> tradingCompanyObjects_;
    
    Data() {}
    Data(const Data&) = delete;
    Data& operator=(Data&) = delete;
    void checkData(TradingCompany *object);
    template<class Class> void checkParameter(Parameter<Class> &parameter);
    template<class Class> Parameter<Class> selectParameter(const Field &field, Class *object, const std::string &message = {});
    template<class C> void checkParameters(C *object, const bool isWarning = false);
    template<class C> void checkPassword(C &object);
    bool find(const std::string &str, const std::string &parameter) const;
    TradingCompany *findParameter(const std::string &parameter);
    void changeOtherData(TradingCompany *object);
    void getAllOtherData() const;
    template<class C> void pushBack(C &object);
    void newEmployeeData(const TradingCompany *object);
};

#endif // Data_h

