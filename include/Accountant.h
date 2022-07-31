#ifndef Accountant_h
#define Accountant_h

#include "Employee.h"

class Data;

class Accountant : public Employee
{
public:
    Accountant();
    const Accountant& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
    
    void ChangePersonalData();
};

#endif // Accountant_h
