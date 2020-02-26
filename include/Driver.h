#ifndef Driver_h
#define Driver_h

#include "TradingCompany.h"

class Driver : public TradingCompany
{
public:
    Driver(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // Driver_h
