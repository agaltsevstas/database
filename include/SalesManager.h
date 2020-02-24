#ifndef SalesManager_h
#define SalesManager_h

#include "TradingCompany.h"

class SalesManager : public TradingCompany
{
public:
    SalesManager(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // SalesManager_h
