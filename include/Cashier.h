#ifndef Cashier_h
#define Cashier_h

#include "TradingCompany.h"

class Cashier : public TradingCompany
{
public:
    Cashier(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // Cashier_h
