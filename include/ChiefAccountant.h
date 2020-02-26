#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "TradingCompany.h"

class ChiefAccountant : public TradingCompany
{
public:
    ChiefAccountant(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};
#endif // ChiefAccoutant_h
