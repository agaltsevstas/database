#ifndef Accountant_h
#define Accountant_h

#include "TradingCompany.h"

class Accountant : public TradingCompany
{
public:
    Accountant(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // Accountant_h
