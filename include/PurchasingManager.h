#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "TradingCompany.h"

class PurchasingManager : public TradingCompany
{
public:
    PurchasingManager(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // PurchasingManager_h
