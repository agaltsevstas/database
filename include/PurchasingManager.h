#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "TradingCompany.h"

class PurchasingManager : public TradingCompany
{
public:
    PurchasingManager(): TradingCompany() {}
    void functional() override;
};

#endif // PurchasingManager_h
