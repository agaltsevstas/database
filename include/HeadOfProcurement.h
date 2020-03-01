#ifndef HeadOfProcurement_h
#define HeadOfProcurement_h

#include "TradingCompany.h"

class HeadOfProcurement : public TradingCompany
{
public:
    HeadOfProcurement(): TradingCompany() {}
    void functional() override;
};

#endif // HeadOfProcurement_h
