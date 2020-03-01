#ifndef HeadOfWarehouse_h
#define HeadOfWarehouse_h

#include "TradingCompany.h"

class HeadOfWarehouse : public TradingCompany
{
public:
    HeadOfWarehouse(): TradingCompany() {}
    void functional() override;
};

#endif // HeadOfWarehouse_h
