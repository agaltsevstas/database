#ifndef Stevedore_h
#define Stevedore_h

#include "TradingCompany.h"

class Data;

class Stevedore : public TradingCompany
{
public:
    Stevedore();
    ~Stevedore();
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Stevedore_h

