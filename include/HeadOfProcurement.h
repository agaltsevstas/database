#ifndef HeadOfProcurement_h
#define HeadOfProcurement_h

#include "TradingCompany.h"

class Data;

class HeadOfProcurement : public TradingCompany
{
public:
    HeadOfProcurement();
    ~HeadOfProcurement();
    const HeadOfProcurement& operator = (const TradingCompany &object);
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // HeadOfProcurement_h
