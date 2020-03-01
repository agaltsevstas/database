#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "TradingCompany.h"

class ChiefAccountant : public TradingCompany
{
public:
    ChiefAccountant(): TradingCompany() {}
    void functional() override;
};
#endif // ChiefAccoutant_h
