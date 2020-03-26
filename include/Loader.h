#ifndef Stevedore_h
#define Stevedore_h

#include "TradingCompany.h"

class Data;

class Loader : public TradingCompany
{
public:
    Loader();
    ~Loader();
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Stevedore_h

