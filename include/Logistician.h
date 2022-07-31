#ifndef Logistician_h
#define Logistician_h

#include "Employee.h"

class Data;

class Logistician : public Employee
{
public:
    Logistician();
    const Logistician& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Logistician_h
