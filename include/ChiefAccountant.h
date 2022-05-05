#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "TradingCompany.h"

class Data;

class ChiefAccountant : public TradingCompany
{
public:
    ChiefAccountant();
    const ChiefAccountant& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};
#endif // ChiefAccoutant_h
