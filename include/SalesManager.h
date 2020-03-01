#ifndef SalesManager_h
#define SalesManager_h

#include "TradingCompany.h"

class SalesManager : public TradingCompany
{
public:
    SalesManager(): TradingCompany() {}
    void functional() override;
};

#endif // SalesManager_h
