#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "TradingCompany.h"

class Data;

class PurchasingManager : public TradingCompany
{
public:
    PurchasingManager();
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // PurchasingManager_h
