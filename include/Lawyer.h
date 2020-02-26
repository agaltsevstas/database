#ifndef Lawyer_h
#define Lawyer_h

#include "TradingCompany.h"

class Lawyer : public TradingCompany
{
public:
    Lawyer(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // Lawyer_h
