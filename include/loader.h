#ifndef Loader_h
#define Loader_h

#include "TradingCompany.h"

class Data;

class Loader : public TradingCompany
{
public:
    Loader();
    const Loader& operator = (const TradingCompany &object);
    void functional() override;
    
private:
    Data* data_ = nullptr;
};

#endif // Loader_h

