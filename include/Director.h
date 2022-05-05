#ifndef Director_h
#define Director_h

#include "TradingCompany.h"

class Data;

class Director : public TradingCompany
{
public:
    Director();
    const Director& operator = (const TradingCompany &object);
    void AddNewEmployeeData();
    void Functional() override;
    
private:    
    Data* _data = nullptr;
    
    void SetPremium(int premium);
    void SetFine(int fine);
};
#endif // Director_h
