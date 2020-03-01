#ifndef Logistician_h
#define Logistician_h

#include "TradingCompany.h"

class Logistician : public TradingCompany
{
public:
    Logistician(): TradingCompany() {}
    void functional() override;
};

#endif // Logistician_h
