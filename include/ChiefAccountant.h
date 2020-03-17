#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "TradingCompany.h"

class Data;

class ChiefAccountant : public TradingCompany
{
public:
    ChiefAccountant();
    ~ChiefAccountant();
    void functional() override;
    
private:
    Data* data_ = nullptr;
};
#endif // ChiefAccoutant_h
