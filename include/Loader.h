#ifndef Loader_h
#define Loader_h

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

#endif // Loader_h

