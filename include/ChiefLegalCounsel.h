#ifndef ChiefLegalCouncel_h
#define ChiefLegalCouncel_h

#include "TradingCompany.h"

class ChiefLegalCounsel : public TradingCompany
{
public:
    ChiefLegalCounsel(): TradingCompany() {}
    void functional() override;
};

#endif // ChiefLegalCouncel_h
