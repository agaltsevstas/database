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
    function<void()>checkParameter_ = nullptr;
//    void(*checkParameter_)() = nullptr;
    template<typename T> void checkParameter(function<T()> parameter, function<void()> checkParameter);
    void setPremium(int premium);
    void setFine(int fine);
};
#endif // Director_h
