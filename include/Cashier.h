#ifndef Cashier_h
#define Cashier_h

#include "TradingCompany.h"

class Data;

class Cashier : public TradingCompany
{
public:
    Cashier();
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Cashier_h
