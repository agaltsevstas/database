#ifndef Accountant_h
#define Accountant_h

#include "TradingCompany.h"

class Accountant : public TradingCompany
{
public:
    Accountant(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // Accountant_h
