#ifndef Lawyer_h
#define Lawyer_h

#include "TradingCompany.h"

class Lawyer : public TradingCompany
{
public:
    Lawyer(): TradingCompany() {}
    void functional() override;
};

#endif // Lawyer_h
