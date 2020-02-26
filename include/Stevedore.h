#ifndef Stevedore_h
#define Stevedore_h

#include "TradingCompany.h"

class Stevedore : public TradingCompany
{
public:
    Stevedore(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // Stevedore_h

