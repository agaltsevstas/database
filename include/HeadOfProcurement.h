#ifndef HeadOfProcurement_h
#define HeadOfProcurement_h

#include "TradingCompany.h"

class HeadOfProcurement : public TradingCompany
{
public:
    HeadOfProcurement(): TradingCompany() {}
    void setPremium(int);
    void setFine(int);
};

#endif // HeadOfProcurement_h
