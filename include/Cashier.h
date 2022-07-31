#ifndef Cashier_h
#define Cashier_h

#include "Employee.h"

class Data;

class Cashier : public Employee
{
public:
    Cashier();
    const Cashier& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Cashier_h
