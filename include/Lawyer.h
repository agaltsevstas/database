#ifndef Lawyer_h
#define Lawyer_h

#include "TradingCompany.h"

class Data;

class Lawyer : public TradingCompany
{
public:
    Lawyer();
    const Lawyer& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Lawyer_h
