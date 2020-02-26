#ifndef HeadOfWarehouse_h
#define HeadOfWarehouse_h

#include "TradingCompany.h"

class HeadOfWarehouse : public TradingCompany
{
public:
    HeadOfWarehouse(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // HeadOfWarehouse_h
