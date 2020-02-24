#ifndef Cashier_h
#define Cashier_h

#include "TradingCompany.h"

class Cashier : public TradingCompany
{
public:
    Cashier(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // Cashier_h
