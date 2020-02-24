#ifndef Lawyer_h
#define Lawyer_h

#include "TradingCompany.h"

class Lawyer : public TradingCompany
{
public:
    Lawyer(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // Lawyer_h
