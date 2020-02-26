#ifndef HeadOfProcurement_h
#define HeadOfProcurement_h

#include "TradingCompany.h"

class HeadOfProcurement : public TradingCompany
{
public:
    HeadOfProcurement(): TradingCompany() {}
    void functional() override;

private:
    void setPremium(int premium);
    void setFine(int fine);
};

#endif // HeadOfProcurement_h
