#ifndef Lawyer_h
#define Lawyer_h

#include "TradingCompany.h"

class Data;

class Lawyer : public TradingCompany
{
public:
    Lawyer();
    const Lawyer& operator = (const TradingCompany &object);
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Lawyer_h
