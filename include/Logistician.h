#ifndef Logistician_h
#define Logistician_h

#include "TradingCompany.h"

class Logistician : public TradingCompany
{
public:
    Logistician(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // Logistician_h
