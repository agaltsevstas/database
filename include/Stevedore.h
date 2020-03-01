#ifndef Stevedore_h
#define Stevedore_h

#include "TradingCompany.h"

class Stevedore : public TradingCompany
{
public:
    Stevedore(): TradingCompany() {}
    void functional() override;
};

#endif // Stevedore_h

