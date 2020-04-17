#ifndef Accountant_h
#define Accountant_h

#include "TradingCompany.h"

class Data;

class Accountant : public TradingCompany
{
public:
    Accountant();
    ~Accountant();
    void functional() override;
    
private:
    Data* data_ = nullptr;
    
    void checkData();
    void changePersonalData();
};

#endif // Accountant_h
