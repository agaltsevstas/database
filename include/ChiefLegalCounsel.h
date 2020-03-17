#ifndef ChiefLegalCouncel_h
#define ChiefLegalCouncel_h

#include "TradingCompany.h"

class Data;

class ChiefLegalCounsel : public TradingCompany
{
public:
    ChiefLegalCounsel();
    ~ChiefLegalCounsel();
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // ChiefLegalCouncel_h
