#ifndef Director_h
#define Director_h

#include "TradingCompany.h"

class Data;

class Director : public TradingCompany
{
public:
    Director();
    ~Director();
    void addNewEmployeeData();
    
    void functional() override;
    
private:    
    Data* data_ = nullptr;
    void checkData();
    void changePersonalData();
    void setPremium(int premium);
    void setFine(int fine);
};
#endif // Director_h
