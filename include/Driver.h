#ifndef Driver_h
#define Driver_h

#include "TradingCompany.h"

class Driver : public TradingCompany
{
public:
    Driver(): TradingCompany() {}
    void functional() override;
};

#endif // Driver_h
