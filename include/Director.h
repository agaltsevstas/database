#ifndef Director_h
#define Director_h

#include "Employee.h"

class Data;

class Director : public Employee
{
public:
    Director();
    const Director& operator = (const Employee &object);
    void AddNewEmployeeData();
    void Functional() override;
    
private:    
    Data* _data = nullptr;
    
    void SetPremium(int premium);
    void SetFine(int fine);
};
#endif // Director_h
