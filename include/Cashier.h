#ifndef Cashier_h
#define Cashier_h

#include "TradingCompany.h"

class Data;

class Cashier : public TradingCompany
{
public:
    Cashier();
    const Cashier& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Cashier_h
