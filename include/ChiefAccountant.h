#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "TradingCompany.h"

class ChiefAccountant : public TradingCompany
{
public:
    ChiefAccountant(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};
#endif // ChiefAccoutant_h
