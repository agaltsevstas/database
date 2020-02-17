#ifndef Stevedore_h
#define Stevedore_h

#include "TradingCompany.h"

class Stevedore : public TradingCompany
{
public:
    Stevedore(): TradingCompany()
    {}
    Stevedore(int number,
              string position,
              string surname,
              string name,
              string patronymic,
              string sex,
              string dateOfBirth,
              unsigned long long passport,
              unsigned long long phone,
              string email,
              string dateOfHiring,
              string workingHours,
              uint salary,
              string password,
              string fileName) : TradingCompany(number,
                                                position,
                                                surname,
                                                name,
                                                patronymic,
                                                sex,
                                                dateOfBirth,
                                                passport,
                                                phone,
                                                email,
                                                dateOfHiring,
                                                workingHours,
                                                salary,
                                                password,
                                                fileName)
    {}
    void setPremium(int);
    void setFine(int);
};

#endif // Stevedore_h

