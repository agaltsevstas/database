#ifndef HRManager_h
#define HRManager_h

#include "TradingCompany.h"

class Data;

class HRManager : public TradingCompany
{
public:
    HRManager();
    const HRManager& operator = (const TradingCompany &object);
    void AddNewEmployeeData();
    void Functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif /* HRManager_h */
