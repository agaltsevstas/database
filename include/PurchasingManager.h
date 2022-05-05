#ifndef PurchasingManager_h
#define PurchasingManager_h

#include "TradingCompany.h"

class Data;

class PurchasingManager : public TradingCompany
{
public:
    PurchasingManager();
    const PurchasingManager& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // PurchasingManager_h
