#ifndef Stevedore_h
#define Stevedore_h

#include "TradingCompany.h"

class Stevedore : public TradingCompany
{
public:
    Stevedore(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // Stevedore_h

