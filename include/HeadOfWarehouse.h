#ifndef HeadOfWarehouse_h
#define HeadOfWarehouse_h

#include "TradingCompany.h"

class Data;

class HeadOfWarehouse : public TradingCompany
{
public:
    HeadOfWarehouse();
    const HeadOfWarehouse& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // HeadOfWarehouse_h
