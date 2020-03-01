#ifndef Cashier_h
#define Cashier_h

#include "TradingCompany.h"

class Cashier : public TradingCompany
{
public:
    Cashier(): TradingCompany() {}
    void functional() override;
};

#endif // Cashier_h
