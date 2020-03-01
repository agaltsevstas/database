#ifndef Accountant_h
#define Accountant_h

#include "TradingCompany.h"

class Accountant : public TradingCompany
{
public:
    Accountant(): TradingCompany() {}
    void functional() override;
};

#endif // Accountant_h
