#ifndef Driver_h
#define Driver_h

#include "Employee.h"

class Data;

class Driver : public Employee
{
public:
    Driver();
    const Driver& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Driver_h
