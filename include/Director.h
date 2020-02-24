#ifndef Director_h
#define Director_h

#include "Data.h"

class Director : public TradingCompany
{
public:
    Director() : TradingCompany() {}
    
//    void functional() override;
    void functional();
    
private:
    void setPremium(int);
    void setFine(int);
};
#endif // Director_h
