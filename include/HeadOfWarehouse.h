#ifndef HeadOfWarehouse_h
#define HeadOfWarehouse_h

#include "TradingCompany.h"

class HeadOfWarehouse : public TradingCompany
{
public:
    HeadOfWarehouse(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // HeadOfWarehouse_h
