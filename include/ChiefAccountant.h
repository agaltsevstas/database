#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "TradingCompany.h"

class Data;

class ChiefAccountant : public TradingCompany
{
public:
    ChiefAccountant();
    const ChiefAccountant& operator = (const TradingCompany &object);
    void functional() override;
    
private:
    Data* data_ = nullptr;
};
#endif // ChiefAccoutant_h
