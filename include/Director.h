#ifndef Director_h
#define Director_h

#include "Data.h"

class Director : public TradingCompany
{
public:
    Director() : TradingCompany() {}
    void checkData();
    void changePersonalData();
    void functional() override;
    
private:
    void setPremium(int premium);
    void setFine(int fine);
};
#endif // Director_h
