#ifndef Lawyer_h
#define Lawyer_h

#include "Employee.h"

class Data;

class Lawyer : public Employee
{
public:
    Lawyer();
    const Lawyer& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Lawyer_h
