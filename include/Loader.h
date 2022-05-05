#ifndef Loader_h
#define Loader_h

#include "TradingCompany.h"

class Data;

class Loader : public TradingCompany
{
public:
    Loader();
    const Loader& operator = (const TradingCompany &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Loader_h

