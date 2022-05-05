#ifndef SalesManager_h
#define SalesManager_h

#include "TradingCompany.h"

class Data;

class SalesManager : public TradingCompany
{
public:
    SalesManager();
    const SalesManager& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // SalesManager_h
