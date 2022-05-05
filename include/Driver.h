#ifndef Driver_h
#define Driver_h

#include "TradingCompany.h"

class Data;

class Driver : public TradingCompany
{
public:
    Driver();
    const Driver& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Driver_h
