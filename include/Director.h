#ifndef Director_h
#define Director_h

#include "Data.h"

class Director : public TradingCompany
{
public:
    Director() : TradingCompany()
    {}
    Director(int number,
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
    
    static void functionalDirector(Director &director);
    static void getAllOtherData();
    static void addNewEmployeeData();
    template <class T>
    static void setOtherData(T &object);
    
private:
    void setPremium(int);
    void setFine(int);
//    void changeOtherData;
};
#endif // Director_h
