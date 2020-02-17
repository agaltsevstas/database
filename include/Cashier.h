#ifndef Cashier_h
#define Cashier_h

#include "TradingCompany.h"

class Cashier : public TradingCompany
{
public:
    Cashier(): TradingCompany()
    {}
    Cashier(int number,
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

#endif // Cashier_h
