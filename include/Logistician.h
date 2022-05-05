#ifndef Logistician_h
#define Logistician_h

#include "TradingCompany.h"

class Data;

class Logistician : public TradingCompany
{
public:
    Logistician();
    const Logistician& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Logistician_h
