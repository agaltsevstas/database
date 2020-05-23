#ifndef Data_h
#define Data_h

#include <iostream>

#include "ObjectFactory.h"
#include "TradingCompany.h"
#include "Director.h"
#include "HRManager.h"

enum Mode
{
    TXT = 1,
    XML
};

const std::map<std::string, uint> idPositions =
{
    {"Бухгалтер", 800},
    {"Водитель", 1300},
    {"Главный_бухгалтер", 200},
    {"Главный_юрист-консультант", 300},
    {"Грузчик", 1200},
    {"Директор", 100},
    {"Логист", 900},
    {"Менеджер_по_закупкам", 1100},
    {"Менеджер_по_персоналу", 1400},
    {"Менеджер_по_продажам", 600},
    {"Кассир", 700},
    {"Начальник_отдела_закупок", 400},
    {"Начальник_склада", 500},
    {"Юрист", 1000}
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
    static Data &instance();
    void loadDatabase(const std::string &directoryPath);
    void inputPassword();
    void printPersonalData(TradingCompany *object);
    void changeData(TradingCompany *object, TradingCompany *otherObject = nullptr);
    
    friend void Director::addNewEmployeeData();
    friend void HRManager::addNewEmployeeData();
    
private:
    Mode mode_ = TXT;
    std::string directoryPath_;
    std::list<std::string> filePaths_;
    ObjectFactory<std::string, TradingCompany> objectFactory_;
    std::vector<std::shared_ptr<TradingCompany>> tradingCompanyObjects_;
    
    Data() {}
    ~Data();
    Data(const Data&) = delete;
    Data& operator=(Data&) = delete;
    void readingTxtFile();
    void readingXmlFile();
    void checkData(TradingCompany *object);
    template<class Class> void checkParameter(Parameter<Class> &parameter);
    template<class Class> Parameter<Class> selectParameter(const Field &field, Class *object, const std::string &message = {});
    template<class C> void checkParameters(C *object, const bool isWarning = false);
    bool find(const std::string &str, const std::string &parameter) const;
    TradingCompany *findParameter(const std::string &parameter);
    void changeOtherData(TradingCompany *object);
    void getAllOtherData() const;
    template<class C> void pushBack(C &object);
    template<class C> void deleteObject(C *object);
    void newEmployeeData(const TradingCompany *object);
    void setModeOutputData(const TradingCompany *object);
    void writeToTxtFile();
    void writeToXmlFile();
};

#endif // Data_h

