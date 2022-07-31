#ifndef ChiefAccoutant_h
#define ChiefAccoutant_h

#include "Employee.h"

class Data;

class ChiefAccountant : public Employee
{
public:
    ChiefAccountant();
    const ChiefAccountant& operator = (const Employee &object);
    void Functional() override;
    
private:
    Data* _data = nullptr;
};
#endif // ChiefAccoutant_h
