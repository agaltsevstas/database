#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "TradingCompany.h"

class PurchasingManager : public TradingCompany
{
public:
    PurchasingManager(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // PurchasingManager_h
