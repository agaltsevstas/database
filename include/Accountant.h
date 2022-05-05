#ifndef Accountant_h
#define Accountant_h

#include "TradingCompany.h"

class Data;

class Accountant : public TradingCompany
{
public:
    Accountant();
    const Accountant& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* data_ = nullptr;
    
    void ChangePersonalData();
};

#endif // Accountant_h
