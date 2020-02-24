#ifndef Driver_h
#define Driver_h

#include "TradingCompany.h"

class Driver : public TradingCompany
{
public:
    Driver(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // Driver_h
