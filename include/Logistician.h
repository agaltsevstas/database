#ifndef Logistician_h
#define Logistician_h

#include "TradingCompany.h"

class Data;

class Logistician : public TradingCompany
{
public:
    Logistician();
    ~Logistician();
    const Logistician& operator = (const TradingCompany &object);
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Logistician_h
