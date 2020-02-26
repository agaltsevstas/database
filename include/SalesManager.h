#ifndef SalesManager_h
#define SalesManager_h

#include "TradingCompany.h"

class SalesManager : public TradingCompany
{
public:
    SalesManager(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // SalesManager_h
