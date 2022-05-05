#ifndef ChiefLegalCouncel_h
#define ChiefLegalCouncel_h

#include "TradingCompany.h"

class Data;

class ChiefLegalCounsel : public TradingCompany
{
public:
    ChiefLegalCounsel();
    const ChiefLegalCounsel& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // ChiefLegalCouncel_h
