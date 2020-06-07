#ifndef Driver_h
#define Driver_h

#include "TradingCompany.h"

class Data;

class Driver : public TradingCompany
{
public:
    Driver();
    const Driver& operator = (const TradingCompany &object);
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Driver_h
