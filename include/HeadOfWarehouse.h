#ifndef HeadOfWarehouse_h
#define HeadOfWarehouse_h

#include "Employee.h"

class Data;

class HeadOfWarehouse : public Employee
{
public:
    HeadOfWarehouse();
    const HeadOfWarehouse& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};

#endif // HeadOfWarehouse_h
