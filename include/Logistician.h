#ifndef Logistician_h
#define Logistician_h

#include "TradingCompany.h"

class Logistician : public TradingCompany
{
public:
    Logistician(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // Logistician_h
