#ifndef Loader_h
#define Loader_h

#include "Employee.h"

class Data;

class Loader : public Employee
{
public:
    Loader();
    const Loader& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // Loader_h

